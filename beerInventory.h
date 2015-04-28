#ifndef BEERINVENTORY_H_INCLUDED
#define BEERINVENTORY_H_INCLUDED

#include <string>

class beerInventory{
    public:
        //HashTable(int);
        beerInventory();
        struct ingredient{
            std::string name;
            int quantity;
            ingredient *next;
        };
        int hashSum(std::string ingredientName);
        void insertIngredient (std::string title, int quanitity);
        int ingredientInIndex(int index);
        void printInventory();
        void findIngredient(std::string title);
        void deleteIngredient(std::string title);
        virtual ~beerInventory();
    protected:
    private:
        static const int tableSize = 10;
        ingredient *hashTable[tableSize];
};


#endif // BEERINVENTORY_H_INCLUDED
