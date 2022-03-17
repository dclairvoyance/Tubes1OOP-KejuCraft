// File Inventory.cpp
// Berisi implementasi class Inventory

#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {
    this->slot = new SlotInventory[27];
    for (int i=0; i<27; i++) {
        string id = "I" + to_string(i);
        this->slot[i].setId(id);
    }
}

Inventory::~Inventory() {
    delete[] this->slot;
}

Inventory::Inventory(const Inventory& other) {
    for (int i=0; i<27; i++) {
        this->slot[i] = other.slot[i];
    }
}

Inventory& Inventory::operator=(const Inventory& other) {
    delete[] this->slot;
    for (int i=0; i<27; i++) {
        this->slot[i] = other.slot[i];
    }
    return *this;
}

void Inventory::setSlot(int index, SlotInventory slot) {
    this->slot[index] = slot;
}

void Inventory::print() {
    for (int i=0; i<27; i++) {
        cout << "[" << this->slot[i].getId() << "] ";
        if (i%9 == 8) {
            cout << endl;
        } 
    }
}