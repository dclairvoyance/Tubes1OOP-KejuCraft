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
    SlotInventory slots[MAX_ROW][MAX_COL];      /* matrix of slot */
public:
    CraftingTable();                                        /* default constructor */
    CraftingTable(const CraftingTable& other);              /* copy constructor */
    ~CraftingTable();                                       /* destructor */
    CraftingTable& operator=(const CraftingTable& other);   /* assignment operator overloading */
    int getRow(int id);                                     /* get row from id */
    int getCol(int id);                                     /* get col from id */
    SlotInventory getSlot(int row, int col);                /* get slot[row][col] */
    bool isSlotEmpty(int row, int col);                     /* (opt) true if slot at index is empty */
    bool isSameItem(int row, int col, Item* ptr);           /* (opt) true if slot contains same item as ptr */
    void setPtrItem(int row, int col, Item* ptr);           /* (opt) set ptr item into slot[row][col] */
    void discardPtrItem(int row, int col);                  /* (opt) discard ptr item from slot[row][col] (used with GIVE) */
    void decPtrItem(int row, int col);                      /* (opt) decrease ptr item (used in CRAFT) */
    bool checkCraft();                                      /* (main) check if combination is craftable */
    Item* craft();                                          /* (main) craft to crafted item */
    void resetCraftingTable();                              /* empty all slots of crafting table */
    void print();                                           /* print info */
    /* opt: either put here or Slot.h */
};

#endif