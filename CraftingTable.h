// File CraftingTable.h
// Berisi definisi class CraftingTable

#ifndef _CRAFTING_TABLE_H_
#define _CRAFTING_TABLE_H_

#define MAX_ROW 3
#define MAX_COL 3
#include <iostream>
#include "Slot.h"
#include "Matrix.h"
#include "Inventory.h"
#include "Slot.h"

class CraftingTable {
private:
    Matrix<SlotInventory, MAX_ROW, MAX_COL> slots;  /* matrix of slot */
    // SlotInventory slots[MAX_ROW][MAX_COL];
public:
    CraftingTable();                                        /* default constructor */          /* copy constructor */
    ~CraftingTable();                                       /* destructor */   /* assignment operator overloading */
    int getRow(int id);                                     /* get row from id */
    int getCol(int id);                                     /* get col from id */
    Slot getSlot(int index);                                /* get slot[row][col] */
    SlotInventory getSlotInventory(int index);                      
    bool isSlotEmptyAtIndex(int index);                     /* (opt) true if slot at index is empty */
    bool isSameItem(int index, Item* ptr);                  /* (opt) true if slot contains same item as ptr */
    void setPtrItem(int index, Item* ptr);                  /* (opt) set ptr item into slot[row][col] */
    void addPtrItem(int index, int quantity);
    void discardPtrItem(int index, int quantity);
    void discardAllPtrItem(int index);                      /* (opt) discard ptr item from slot[row][col] (used with GIVE) */
    void decPtrItem(int index, int quantity);               /* (opt) decrease ptr item (used in CRAFT) */
    bool checkCraft();                                      /* (main) check if combination is craftable */
    Item* craft();                                          /* (main) craft to crafted item */
    void resetCraftingTable();                              /* empty all slots of crafting table */
    void print();                                           /* print info */
    /* opt: either put here or Slot.h */

    string getSlotIdByCoord(int row, int col);
    int getItemIdByCoord(int row, int col);
    string getItemNameByCoord(int row, int col);
    int getQuantityByCoord(int row, int col);
    int countOccurence(string itemName, int index);

    int findIndexBySlotId(string slotIdDest);
    int getQuantityAtIndex(int index);
    string getItemNameAtIndex(int index);
    void setQuantityAtIndex(int index, int quantity);
    void addQuantityAtIndex(int index, int quantity);
    void setPtrItemAtIndex(int index, Item* ptr);
    int getItemIdAtIndex(int index);
    string getSlotIdAtIndex(int index);
    Item* getPtrItemAtIndex(int index);
};

#endif