// File Inventory.h
// Berisi definisi class Inventory

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#define MAX_ROW 3
#define MAX_COL 9
#include <iostream>
#include <map>
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
    // void setSlot(int index, SlotInventory slot);
    int countSlotEmpty();                               /* count empty slot in array */
    int findIndexEmpty();                               /* find index of first empty slot in array */
    int findIndexItem(Item* ptr);                       /* find index of first ptr in array */
    void setPtrItemAtIndex(int index, Item* ptr);       /* set ptr item into slots[index] */
    int getQuantityAtIndex(int index);                  /* get quantity of item in slots[index] */
    void addQuantityAtIndex(int index, int quantity);   /* add quantity of item in slots[index] */
    void print();                                       /* print info */
};

#endif