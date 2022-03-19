// File Inventory.h
// Berisi definisi class Inventory

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#define MAX_SLOT 27
#include <iostream>
#include "Slot.h"

class Inventory {
private:
    SlotInventory* slots;   /* array of SlotInventory */
public:
    Inventory();                                        /* default constructor */
    Inventory(const Inventory& other);                  /* copy constructor */
    ~Inventory();                                       /* destructor */
    Inventory& operator=(const Inventory& other);       /* assignment operator overloading */
    SlotInventory* getSlots();                          /* get slots attribute (array of SlotInventory) */
    int findIndexEmpty();
    int countSlotEmpty();
    void addQuantityAtIndex(int index, int quantity);
    void setQuantityAtIndex(int index, int quantity);
    int getQuantityAtIndex(int index);
    int getItemIdAtIndex(int index);
    string getItemNameAtIndex(int index);
    Item* getPtrItemAtIndex(int index);
    string getSlotIdAtIndex(int index);
    void setPtrItemAtIndex(int index, Item* ptr);
    int findIndexItem(Item* ptr);
    int findIndexBySlotId(string id);
    int findPosForGIVE(string itemName);
    int findPosForMOVE(string itemName, string slotId);
    bool isSlotEmptyAtIndex(int index);
    void print();
};

#endif