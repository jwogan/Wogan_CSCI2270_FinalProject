  //Joseph Wogan
//CSCI 2270 Final Project
//Instructor: Rhonda Hoenigman
#include <iostream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "beerInventory.h"
#include <vector>
#include "styleGuidelines.h"
using namespace std;

//for this program to work, these two lines must be declared before main. If they are not, the program will not compile
beerInventory *inventory = new beerInventory();
styleGuidelines *guidelineTable = new styleGuidelines();

//menuSelect and menuDisplay are the means to which the user is able to view and select options for running the program.
void menuDisplay(){
    cout <<	"\n======Main Menu======" << endl;
    cout <<	"1. Insert Ingredient" << endl;
    cout <<	"2. Delete Ingredient" << endl;
    cout <<	"3. Find Ingredient" << endl;
    cout << "4. Print Supply" << endl;
    cout << "5. Print all subcategories that contain specific base malts"<<endl;
    cout << "6. Print all subcategories that contain specific specialty malts"<<endl;
    cout << "7. View Style Guidelines" <<endl;
    cout <<	"8. Quit" << endl;
}

vector <string> ingredientsAdded;
vector <string>::iterator ingredientsAddedIterator;

int checkIfAdded(string ingredient){
    for(int i = 0; i<ingredientsAdded.size();i++){
        if(ingredient == ingredientsAdded[i])
            return i;
    }
    return -1;
}

void iterate(int times){
    ingredientsAddedIterator = ingredientsAdded.begin();
    for(int i = 0;i<times;i++){
    ingredientsAddedIterator++;
    }
}

void menuSelect(){
    bool menuOpen = true;
    while(menuOpen == true){
    cin.clear();
    string input;
    cin >> input;
    if(input == "1"){//rent
        cout << "Enter type:"<<endl;;
        string name;
        cin.ignore();
        getline(cin,name);

        if(checkIfAdded(name) == -1){
            cout << "Enter amount (lbs):" << endl;

            // Makes sure the input is an integer
            cin.clear();
            string year;
            int quantity;
            getline(cin, year);
            istringstream iss(year);
            iss >> quantity;
            if (!iss.eof()) {
                cout << "Oops, that wasn't a valid quantity! Try again!" << endl;
            } else {
                inventory->insertIngredient(name, quantity);//BST->rentMovie(name);
                ingredientsAdded.push_back(name);
            }
        }
        else{
            cout<< "That ingredient has already been added. Try deleting it first." << endl;
        }
    }
    if(input == "2"){
        string name;
        cout << "Enter type:" << endl;
        cin.ignore();
        getline(cin, name);
        int deleteIngredient = checkIfAdded(name);
        cout<<"DI:"<<deleteIngredient<<endl;
        iterate(deleteIngredient);
        cout<<"Begin:"<<ingredientsAdded[deleteIngredient]<<endl;

        //cout<<"Item:"<<ingredientsAdded[deleteIngredient]<<endl;
        if(deleteIngredient != -1){
            ingredientsAdded.erase(ingredientsAddedIterator);
            inventory->deleteIngredient(name);
        }
        else{
            cout<<"That ingredient has not been added."<<endl;
        }
    }
    if(input == "3"){//delete the movie
        cout << "Enter type:" << endl;
        string name;
        cin.ignore();
        getline(cin,name);
        inventory->findIngredient(name);
    }
    if(input =="4"){//count the movie;
        inventory->printInventory();
    }
    if(input == "5"){
        cout << "Enter name of ingredient: "<<endl;
        string test;
        cin.ignore();
        getline(cin, test);
        guidelineTable->findbaseInStyle(test);
    }
    if(input == "6"){
        cout << "Enter name of ingredient: "<<endl;
        string test;
        cin.ignore();
        getline(cin, test);
        guidelineTable->findSpecialtyInStyle(test);
    }
    if(input == "7"){
        guidelineTable->styleSelect();
        guidelineTable->viewStyles();
    }
    if(input == "8"){//quit
        cout << "Goodbye!" << endl;
        menuOpen = false;
        break;
    }
    menuDisplay();
    }
}

//This sets up the initial data for the hash tables. Sample styles and inventories are entered.
void populate(){
    guidelineTable->insertStyle("Dry Stout", "13. Stout", "Pale Malt", "Roasted un-malted Barley", "Guinness Draught Stout (also canned), Murphys Stout, Beamish Stout, O’Haras Celtic Stout, Russian River O.V.L. Stout, Three Floyds Black SunStout, Dorothy Goodbody’s Wholesome Stout, Orkney Dragonhead Stout, Old Dominion Stout, Goose Island DublinStout, Brooklyn Dry Stout");
    guidelineTable->insertStyle("Sweet Stout", "13. Stout", "Pale Malt", "Roasted Barley, Black Malt,Chocolate Malt, Crystal Malt, and adjuncts such as maize ortreacle", "Mackeson's XXX Stout, Watney's Cream Stout, Farson’s Lacto Stout, St. Peter’s Cream Stout, Marston’s Oyster Stout, Sheaf Stout, Hitachino Nest Sweet Stout (Lacto), Samuel Adams Cream Stout, Left Hand Milk Stout, Widmer Snowplow Milk Stout");
    guidelineTable->insertStyle("Oatmeal Stout","13. Stout", "Pale Malt ", "Crystal, Dark Roasted Malt, Oatmeal", "Samuel Smith Oatmeal Stout, Young's Oatmeal Stout, McAuslan Oatmeal Stout, Maclay’s Oat MaltStout, Broughton Kinmount Willie Oatmeal Stout, Anderson Valley Barney Flats Oatmeal Stout, Tröegs Oatmeal Stout, New Holland The Poet, Goose Island Oatmeal Stout, Wolaver’s Oatmeal Stout");
    guidelineTable->insertStyle("Foreign Extra Stout", "13. Stout", "Pale Malt", "Dark Roasted Malt, Grains", "TROPICAL-TYPE: Lion Stout (Sri Lanka),Dragon Stout (Jamaica), ABC Stout (Singapore), Royal Extra “The Lion Stout” (Trinidad), Jamaica Stout (Jamaica), EXPORT-TYPE: Freeminer Deep Shaft Stout, Guinness Foreign Extra Stout (bottled, not sold in the US), Ridgeway of Oxfordshire Foreign Extra Stout, Coopers Best Extra Stout, Elysian Dragonstooth Stout");
    guidelineTable->insertStyle("American Stout", "13. Stout", "American Base Malt", "Dark Malt, Roasted Malt, Caramel/Crystal Malt", "Rogue Shakespeare Stout, Deschutes Obsidian Stout, Sierra Nevada Stout, North Coast Old No. 38,Bar Harbor Cadillac Mountain Stout, Avery Out of Bounds Stout, Lost Coast 8 Ball Stout, Mad River Steelhead Extra Stout");
    guidelineTable->insertStyle("Russian Imperial Stout", "13. Stout", "Pale Malt", "Roasted Malt, Roasted Grain", "Three Floyd’s Dark Lord, Bell’s Expedition Stout, North Coast Old Rasputin Imperial Stout, StoneImperial Stout, Samuel Smith Imperial Stout, Scotch Irish Tsarina Katarina Imperial Stout, Thirsty Dog Siberian Night, Deschutes The Abyss, Great Divide Yeti, Southampton Russian Imperial Stout, Rogue Imperial Stout, Bear Republic Big Bear Black Stout, Great Lakes Blackout Stout, Avery The Czar,Founders Imperial Stout, Victory Storm King, Brooklyn Black Chocolate Stout");
    inventory->insertIngredient("Pale Malt", 50);
    inventory->insertIngredient("Crystal 20L",3 );
    inventory->insertIngredient("Crystal 40L", 1);
    inventory->insertIngredient("Crystal 60L", 0);
    inventory->insertIngredient("Oatmeal", 3);
    inventory->insertIngredient("Dark Malt", 0);
    inventory->insertIngredient("American Base Malt", 0);
    inventory->insertIngredient("Chocolate Malt", .5);
    inventory->insertIngredient("Black Malt",0);
}

int main()
{
    //populate();
    menuDisplay();
    menuSelect();
    return 0;
}
