// File CraftingTable.h
// Berisi definisi class CraftingTable

#ifndef _CRAFTING_TABLE_H_
#define _CRAFTING_TABLE_H_

#define MAX_ROW 3
#define MAX_COL 3
#include <iostream>
#include "Slot.h"

class CraftingTable {
private:
public:
    CraftingTable();
    CraftingTable(const CraftingTable& other);
    ~CraftingTable();
    CraftingTable& operator=(const CraftingTable& other);
    void print();
};

#endif