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
    Matrix<Slot, MAX_ROW, MAX_COL> slots;  /* matrix of slot */
    // Slot slots[MAX_ROW][MAX_COL];
public:
    CraftingTable();                                        /* default constructor */
    ~CraftingTable();                                       /* destructor */
    int getRow(int id);                                     /* get row from id */
    int getCol(int id);                                     /* get col from id */
    Slot getSlot(int index);                                /* get slot[row][col] */                 
    bool isSlotEmpty(int index);                            /* (opt) true if slot at index is empty */
    bool isSameItem(int index, Item* ptr);                  /* (opt) true if slot contains same item as ptr */
    Item* getPtrItem(int index);
    void setPtrItem(int index, Item* ptr);                  /* (opt) set ptr item into slot[row][col] */
    void addPtrItem(int index, int quantity);
    void discardPtrItem(int index, int quantity);
    void discardAllPtrItem(int index);                      /* (opt) discard ptr item from slot[row][col] (used with GIVE) */
    void decPtrItem(int index, int quantity);               /* (opt) decrease ptr item (used in CRAFT) */
    bool checkCraft();                                      /* (main) check if combination is craftable */
    void resetCraftingTable();                              /* empty all slots of crafting table */                                           /* print info */
    string getSlotId(int row, int col);
    int getItemId(int row, int col);
    int countOccurence(string itemName, int index);
    int findIndex(string slotIdDest);
    int getQuantity(int index);
    int getQuantity(int row, int col);
    void setQuantity(int index, int quantity);
    void addQuantity(int index, int quantity);
    string getItemName(int index);
    string getItemName(int row, int col);
    int getItemId(int index);
    string getSlotId(int index);
    void print();
};

#endif