#include "beerInventory.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>

using namespace std;

//The constructor simply initializes the hash table that stores the user's "inventory". As most users likely wouldn't have multiple dozens
//of ingredients, a small table, such as size 10, can be used.
beerInventory::beerInventory(){
    for(int i = 0; i < tableSize; i++){  // tableSize is set to be 10 in the beerInventory.h file. It can be easily changed there for simple scaling
        hashTable[i] = new ingredient;
        hashTable[i]->name = "init";
        hashTable[i]->next = NULL;
    }
}

beerInventory::~beerInventory()
{
}

//This hash function was the same one used in the lecture notes and Assignment 9. It sums the
//ASCII values of every letter, mods that sum by the hash table size, and places in correct index.

int beerInventory::hashSum(std::string ingredientName){  //x is the string to hash, s is the array size; taken from Lecture 29 notes
    int sum = 0;
    for(int i = 0; i < ingredientName.length(); i++ ) //i = 1 to x.length
        sum = sum + ingredientName[i];  //ascii value of ith character in the string
    sum = sum % tableSize;
    return sum;
}

//This method inserts a new item in the hash table. Indexes with more than one entry are stored alphabetically.
//There are a few cases to handle: situations where the entry should be placed in the front 'middle' or end of the list.
//the method expects a string and an integer, but entering two integers will not break the code, however, entering two strings will.
//The method will also break if the same string is entered in multiple times
//after calling the function, the ingredient should be placed in the hashtable.

void beerInventory::insertIngredient(std::string name, int quantity){
    int index = hashSum(name);
    if(hashTable[index]->name == "init"){  // if nothing is at the index, place movie info in that index
        hashTable[index]->name = name;
        hashTable[index]->quantity = quantity;
    }
    else{
        ingredient *x = hashTable[index];
        ingredient *y = new ingredient;
        y->name = name;
        y->quantity = quantity;
        y->next = NULL;
        if(x->next == NULL && name < x->name){ // case where there is one item in the hash table, new item should be first in list
            y->next = x;
            hashTable[index] = y;
            y->next->next = NULL;
        }
        else if(x->next != NULL && name < x->name){ //case where ingredient will be added to front of populated hash table
            y->next = x;
            hashTable[index] = y;
        }
        else if(x->next == NULL && name > x->name){
            x->next = y;
        }
        else{
            while(name > x->next->name){  //compares items to string to add alphabetically
                x = x->next; //found the node to which the new movie will be added to after
            }
            y->next = x->next; //set new node next pointer to 'previous''s node's next pointer
            x->next = y; //set previous nodes next pointer to new node
        }
    }
}

//this method is not necessary for this project. It simply returns what index a specific ingredient may be in
int beerInventory::ingredientInIndex(int index){
    int count = 0;
    if(hashTable[index]->name == "init"){
        return count;
    }
    else{
        count++;
        ingredient *x = hashTable[index];
        while(x->next != NULL){
            x = x->next;
            count++;
        }
    }
}

void beerInventory::printInventory(){
    for(int i = 0; i < tableSize; i++){
        ingredient *x = hashTable[i];
        if(x->name == "init"){
            cout << "-----------------"<<endl;
            cout << "index = "<< i << " is empty"<<endl;
        }
        else{
            cout << "-----------------"<<endl;
            cout << "index " << i << " contains: "<<endl;
            while(x != NULL){
                cout << x->name << " : "<<x->quantity<<endl;
                x = x->next;
            }
        }
    }
}

void beerInventory::findIngredient(std::string name)
{
    int index = hashSum(name); //gives us the index that the title would in if it is in table
    bool found = false;
    string ingredientTitle;
    int ingredientQuantity;
    ingredient *x  = hashTable[index];
    while(x != NULL)
    {
        if(x->name == name)
        {
            found = true;
            ingredientTitle = x->name;
            ingredientQuantity = x->quantity;
        }
        x = x->next;
    }
    if(found == true){
        cout << ingredientTitle<< " : " << ingredientQuantity<< "lbs" <<endl;
    }
    else
    {
        cout << "Ingredient not found" <<endl;
    }
}

void beerInventory::deleteIngredient(std::string name)
{
    int index = hashSum(name);
    ingredient *deleteX;
    ingredient *x;
    ingredient *y;

    if(hashTable[index]->name == "init")  //case where index is empty
    {
        cout  << "Ingredient not found" << endl;
    }
    else if(hashTable[index]->name == name && hashTable[index]->next == NULL)  //case where there is only one item in index,and it is the movie we are looking for
    {
        hashTable[index]->name = "init";
        hashTable[index]->quantity = 0;
        hashTable[index]->next = NULL; //already declared (wouldnt have entered else if black otherwise)
        cout << name << " Deleted" << endl;
    }
    else if(hashTable[index]->name ==name)  //case case where match is located and is first item in the bucket AND the index is populated
    {
        deleteX = hashTable[index]; //delete pointer now points to first item in correct index, should be movie we want to delete
        hashTable[index] = hashTable[index]->next;
        delete deleteX;
        cout << name << " Deleted" << endl;
    }
    else  //case where index is populated, not first movie
    {
        x = hashTable[index]->next; // points to second item in the correct index
        y = hashTable[index]; //points to first item in the correct index
        while(x != NULL && x->name != name)  //as long as we are pointing to a movie that is not the one to be deleted
        {
            y = x;
            x = x->next; //keep iterating through
        }
        if(x == NULL)  // viewed every movie in the index; didnt find movie to be deleted
        {
            cout << "Movie not found" << endl;
        }
        else
        {
            deleteX = x;
            x = x->next;
            y->next = x;
            delete deleteX;
            cout << name << " Deleted" << endl;
        }
    }
}

