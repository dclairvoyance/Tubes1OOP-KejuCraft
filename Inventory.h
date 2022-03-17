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
    void setSlot(int index, SlotInventory Slot);
    void print();
};

#endif