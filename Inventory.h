// File Inventory.h
// Berisi definisi class Inventory

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#define MAX_ROW 3
#define MAX_COL 9
#include <iostream>
#include "Slot.h"

class Inventory {
private:
public:
    Inventory();
    Inventory(const Inventory& other);
    ~Inventory();
    Inventory& operator=(const Inventory& other);
    void print();
};

#endif