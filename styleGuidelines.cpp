#include "styleGuidelines.h"
#include <string>
#include <iostream>
using namespace std;

//this constructor is very similar to the one used in the beerInventory.cpp file
//As can be seen, a good portion of the potential functionality has not yet been implemented (members of the struct have been commented out)
//like the previous constructor, the tableSize can be easily changed in the header for scalability
//if all of the styles were implemented in the code (only Stout is as of Phase 2), then a hash table of size 200 would be more appropriate

styleGuidelines::styleGuidelines(){
    for(int i = 0; i < tableSize; i++){
        hashTable[i] = new style;
        //hashTable[i]->aroma = "give me Data";
        //hashTable[i]->appearence = "give me data";
        //hashTable[i]->flavor = "give me data";
        //hashTable[i]->mouthfeel = "give me data";
        //hashTable[i]->impresssion = "give me data";
        hashTable[i]->baseMalt = "init";
        hashTable[i]->specialtyMalt = "init";
        hashTable[i]->category = "init";
        hashTable[i]->subcategory = "init";
        hashTable[i]->commercialExamples = "init";
        hashTable[i]->next = NULL;
    }
}

int styleGuidelines::hashSum(std::string subcategory){  //x is the string to hash, s is the array size; taken from Lecture 29 notes
    int sum = 0;
    for(int i = 0; i < subcategory.length(); i++ ) //i = 1 to x.length
        sum = sum + subcategory[i];  //ascii value of ith character in the string
    sum = sum % tableSize;
    return sum;
}

//This is just like the insert style of before, but extra struct members have been added to accommodate more information
void styleGuidelines::insertStyle(std::string subcategory, std::string category, std::string baseMalt, std::string specialtyMalt, std::string commericalExamples){
    int index = hashSum(subcategory);
    if(hashTable[index]->subcategory == "init"){  // if nothing is at the index, place movie info in that index
        hashTable[index]->subcategory = subcategory;
        hashTable[index]->category = category;
        hashTable[index]->baseMalt = baseMalt;
        hashTable[index]->specialtyMalt = specialtyMalt;
        hashTable[index]->commercialExamples = commericalExamples;
    }
    else{
        style *x = hashTable[index];
        style *y = new style;
        y->subcategory = subcategory;
        y->category = category;
        y->baseMalt = baseMalt;
        y->specialtyMalt = specialtyMalt;
        y->next = NULL;
        if(x->next == NULL && subcategory < x->subcategory){
            style *temp = x;
            hashTable[index] = y;
            y->next = temp;
        }
        else{
            while(x->next != NULL){
                while(subcategory > x->next->subcategory){  //compares items to string to add alphabetically
                    x = x->next; //found the node to which the new movie will be added to after
                }
            }
            y->next = x->next; //set new node next pointer to 'previous''s node's next pointer
            x->next = y; //set previous nodes next pointer to new node
        }
    }
}
void styleGuidelines::styleSelect(){
    cout << "-----------------------------------" << endl;
    cout << " What style would you like to view?" << endl;
    cout << "1. Stout               " << endl;
    cout <<	"2. Main Menu" << endl;
}

//this method is used to display options to the user.
//The user is presented with an option to view styles (again, only stout has been implemented so far)
//once the style is chosen, the user is prompted to choose a subcategory. As testers for this class are unlikely to know all of the numerous
//subcategories, they are presented to the user.
//the user always has the option of exiting to the main menu. If the user enters an invalid selection, the program defaults to submenu
//current bugs:
//I was not able to get a an iterator to work on the part that displays a list of available substyles;
//as a result, the user must enter the entire name of the substyle, a disconnect from entering "1,2,3.." as is standard in this class


//Every part of the method expects a string. If a string is entered incorrectly or an unavailable option is entered, the user will be brought back
//to the start of the method.
//  while not inconvenient now (only one style to choose from), if there were 23 styles, this would be a major inconvenience.

//preconditions: that the hash table has data about styles. This will always be the case as the style table is built before the user can
//enter selections

//postconditions: N/A

void styleGuidelines::viewStyles(){
    bool menuOpen = true;
    while(menuOpen == true){
    string input;
    cin >> input;
    if(input == "1"){ // select stout as item to view
        cout << "What section of Stout would you like to view? "<<endl;
        cout << "----------------------------------------------"<<endl;
        for(int i = 0; i < tableSize; i++){ //loop through the style hash table
            style *x = hashTable[i];
            while(x != NULL){
                if(x->category == "13. Stout") //if the entry has a category of stout, print out all subcategories
                    cout <<x->subcategory <<endl;
                    x = x->next;
            }
        }
        cout << "-----------------"<<endl;
        string selection;
        cin.ignore();
        getline(cin, selection);
        if(selection  == "Dry Stout"){
            cout << "What attribute would you like to view?"<<endl;
            cout << "---------------------------------------"<<endl;
            cout << "1. Base Malt"<<endl;
            cout << "2. Specialty Malt"<<endl;
            cout << "3. Commercial Examples"<<endl;
            cout << "-----------------"<<endl;
            string attributeSelection;
            getline(cin, attributeSelection);
            if(attributeSelection == "1"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Dry Stout")
                            cout << x->baseMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "2"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Dry Stout")
                            cout << x->specialtyMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "3"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Dry Stout")
                            cout << x->commercialExamples<<endl;
                            x = x->next;
                        }
                }
            }
            else{
                cout << "Not a proper selection"<<endl;
            }
        }
        else if(selection == "Sweet Stout"){
            cout << "What attribute would you like to view?"<<endl;
            cout << "---------------------------------------"<<endl;
            cout << "1. Base Malt"<<endl;
            cout << "2. Specialty Malt"<<endl;
            cout << "3. Commercial Examples"<<endl;
            string attributeSelection;
            getline(cin, attributeSelection);
            if(attributeSelection == "1"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Sweet Stout")
                            cout << x->baseMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "2"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Sweet Stout")
                            cout << x->specialtyMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "3"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Sweet Stout")
                            cout << x->commercialExamples<<endl;
                            x = x->next;
                        }
                }
            }

            else{
                cout << "Not a proper selection"<<endl;
            }
        }
        else if(selection == "Oatmeal Stout"){
            cout << "What attribute would you like to view?"<<endl;
            cout << "---------------------------------------"<<endl;
            cout << "1. Base Malt"<<endl;
            cout << "2. Specialty Malt"<<endl;
            cout << "3. Commercial Examples"<<endl;
            string attributeSelection;
            getline(cin, attributeSelection);
            if(attributeSelection == "1"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Oatmeal Stout")
                            cout << x->baseMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "2"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Oatmeal Stout")
                            cout << x->specialtyMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "3"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Oatmeal Stout")
                            cout << x->commercialExamples<<endl;
                            x = x->next;
                        }
                }
            }
            else{
                cout << "Not a proper selection"<<endl;
            }
        }
        else if(selection == "Foreign Extra Stout"){
            cout << "What attribute would you like to view?"<<endl;
            cout << "---------------------------------------"<<endl;
            cout << "1. Base Malt"<<endl;
            cout << "2. Specialty Malt"<<endl;
            cout << "3. Commercial Examples"<<endl;
            string attributeSelection;
            getline(cin, attributeSelection);
            if(attributeSelection == "1"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Foreign Extra Stout")
                            cout << x->baseMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "2"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Foreign Extra Stout")
                            cout << x->specialtyMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "3"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Foreign Extra Stout")
                            cout << x->commercialExamples<<endl;
                            x = x->next;
                        }
                }
            }
            else{
                cout << "Not a proper selection"<<endl;
            }
        }
        else if(selection == "American Stout"){
            cout << "What attribute would you like to view?"<<endl;
            cout << "---------------------------------------"<<endl;
            cout << "1. Base Malt"<<endl;
            cout << "2. Specialty Malt"<<endl;
            cout << "3. Commercial Examples"<<endl;
            string attributeSelection;
            getline(cin, attributeSelection);
            if(attributeSelection == "1"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "American Stout")
                            cout << x->baseMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "2"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "American Stout")
                            cout << x->specialtyMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "3"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "American Stout")
                            cout << x->commercialExamples<<endl;
                            x = x->next;
                        }
                }
            }
            else{
                cout << "Not a proper selection"<<endl;
            }
        }
        else if(selection == "Russian Imperial Stout"){
            cout << "What attribute would you like to view?"<<endl;
            cout << "---------------------------------------"<<endl;
            cout << "1. Base Malt"<<endl;
            cout << "2. Specialty Malt"<<endl;
            cout << "3. Commercial Examples"<<endl;
            string attributeSelection;
            getline(cin, attributeSelection);
            if(attributeSelection == "1"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Russian Imperial Stout")
                            cout << x->baseMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "2"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Russian Imperial Stout")
                            cout << x->specialtyMalt<<endl;
                            x = x->next;
                        }
                }
            }
            else if(attributeSelection == "3"){
                for(int i = 0; i < tableSize; i++){
                    style *x = hashTable[i];
                        while(x != NULL){
                            if(x->subcategory == "Russian Imperial Stout")
                            cout << x->commercialExamples<<endl;
                            x = x->next;
                        }
                }
            }
            else{
                cout << "Not a proper selection"<<endl;
            }
        }
        else{
            cout << "Not an available selection"<<endl;
        }
    }

    if(input == "2"){//quit
        menuOpen = false;
        break;
    }
    styleSelect();
    }
}


//findBaseInStyle ans findSpecialtyInStyle check to see if a grain/malt is in any of the entered styles.
//as the members of the struct Style are long strings, we use the std:string find function to determine if one string is the subset of another
//so, this function checks to see if "name" is a subset of 'baseMalt" or "specialtyMalt"
//ex: searching(name = ) "Pale", "ale", "Pale Malt" will print to the terminal every style that uses Pale Malt

//preconditions: both hash tables are built, the user has an idea of what to search for
//postconditions:N/A
void styleGuidelines::findbaseInStyle(std::string name){
    cout << "-----------------"<<endl;
    for(int i = 0; i < tableSize; i++){
        style *x = hashTable[i];
        while(x != NULL){
            if((x->baseMalt).find(name) != string::npos)
                cout << x->subcategory <<endl;
                x = x->next;
        }
    }
}

void styleGuidelines::findSpecialtyInStyle(std::string name){
    cout << "-----------------"<<endl;
    for(int i = 0; i < tableSize; i++){
        style *x = hashTable[i];
        while(x != NULL){
            if((x->specialtyMalt).find(name) != string::npos)
                cout << x->subcategory <<endl;
                x = x->next;
        }
    }
}


