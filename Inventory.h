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
    SlotInventory* slot;
public:
    Inventory();
    Inventory(const Inventory& other);
    ~Inventory();
    Inventory& operator=(const Inventory& other);
    SlotInventory* getSlots();
    void setSlot(int index, SlotInventory Slot);
    int findIndexEmpty();
    int countSlotEmpty();
    void addQuantityAtIndex(int index, int quantity);
    void setQuantityAtIndex(int index, int quantity);
    int getQuantityAtIndex(int index);
    string getItemNameAtIndex(int index);
    Item* getPtrItemAtIndex(int index);
    void setPtrItemAtIndex(int index, Item* ptr);
    int findIndexItem(Item* ptr);
    int findIndexBySlotId(string id);
    bool isSlotEmptyAtIndex(int index);
    void print();
};

#endif