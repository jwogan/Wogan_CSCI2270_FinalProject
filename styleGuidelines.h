#ifndef STYLEGUIDELINES_H_INCLUDED
#define STYLEGUIDELINES_H_INCLUDED
#include <string>

class styleGuidelines{
public:
    styleGuidelines();
    int hashSum(std::string category);
    void insertStyle(std::string subcategory, std::string category, std::string baseMalt, std::string specialtyMalt, std::string commercialExamples);
    void styleSelect();
    void attributeSelect();
    void viewStyles();
    void findbaseInStyle(std::string name);
    void findSpecialtyInStyle(std::string name);

    struct style{
        //std::string aroma = "give me Data";
        //std::string appearence = "give me data";
        //std::string flavor = "give me data";
        //std::string hmouthfeel = "give me data";
        //std::string impresssion = "give me data";
        std::string category;
        std::string subcategory;
        std::string baseMalt;
        std::string specialtyMalt;
        std::string commercialExamples;
        style *next;
    };
protected:
private:
        static const int tableSize = 10;
        style *hashTable[tableSize];
};

#endif // STYLEGUIDELINES_H_INCLUDED
