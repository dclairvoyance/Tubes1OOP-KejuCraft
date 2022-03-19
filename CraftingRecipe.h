// File CraftingTable.h
// Berisi definisi class CraftingTable

#ifndef _CRAFTING_RECIPE_H_
#define _CRAFTING_RECIPE_H_

#define MAX_ROW 3
#define MAX_COL 3
#include <iostream>
#include "Slot.h"
#include "Item.h"

class CraftingRecipe {
private:
    int row;
    int col;
    Item** resep;
    Item output;
    int quantity;
        /* matrix of slot */
public:
    CraftingRecipe();
    CraftingRecipe(int row, int col, Item** resep, Item output, int quantity);                                        /* default constructor */
    CraftingRecipe(const CraftingRecipe& other);              /* copy constructor */
    ~CraftingRecipe();                                       /* destructor */
    CraftingRecipe& operator=(const CraftingRecipe& other);   /* assignment operator overloading */
    void print();
};

#endif