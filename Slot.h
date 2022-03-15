// File Slot.h
// Berisi definisi class Slot

#ifndef _SLOT_H_
#define _SLOT_H_

#define MAX_CAP 64
#include <iostream>
#include "Item.h"

template <class T>
class Slot {
protected:
    int id;
    T item;
public:
    Slot() {
        this->id = 0;
    }
};

template <class T>
class SlotInventory : public Slot<T> {
private:
    int quantity;
public:
    SlotInventory() : Slot() {
        this->quantity = 0;
    }
    SlotInventory(int id, int quantity) {
        this->id = id;
        this->quantity = quantity;
    }
    void addItemTo(SlotInventory& other) {
        int total = this->quantity + other.quantity;
        other.quantity = total>64 ? 64 : total;
        this->quantity = total - other.quantity;
    } // Menambahkan item ke slot
};

template <class T>
class SlotCrafting : public Slot<T> {
private:
public:
    SlotCrafting();
    void put(); // Menaruh item pada suatu slot
};

#endif