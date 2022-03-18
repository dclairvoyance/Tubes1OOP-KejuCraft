// File Inventory.cpp
// Berisi implementasi class Inventory

#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {
    this->slots = new SlotInventory[27];
    for (int i=0; i<27; i++) {
        string id = "I" + to_string(i);
        this->slots[i].setId(id);
    }
}

Inventory::Inventory(const Inventory& other) {
    for (int i=0; i<27; i++) {
        this->slots[i] = other.slots[i];
    }
}

Inventory::~Inventory() {
    delete[] this->slots;
}

Inventory& Inventory::operator=(const Inventory& other) {
    delete[] this->slots;
    for (int i=0; i<27; i++) {
        this->slots[i] = other.slots[i];
    }
    return *this;
}

SlotInventory* Inventory::getSlots() {
    return this->slots;
}

int Inventory::countSlotEmpty() {
    int count = 0;
    for (int i=0; i<27; i++) {
        if (this->slots[i].getPointerItem() == NULL) {
            count++;
        }
    }
    return count;
}

int Inventory::findIndexEmpty() {
    for (int i=0; i<27; i++) {
        if (this->slots[i].getPointerItem() == NULL) {
            return i;
        }
    }
    return -1;
}

int Inventory::findIndexItem(Item* ptr) {
    for (int i=0; i<27; i++) {
        if (this->slots[i].getPointerItem() == ptr && this->slots[i].getQuantity() < 64) {
            return i;
        }
    }
    return -1;
}

void Inventory::setPtrItemAtIndex(int index, Item* ptr) {
    this->getSlots()[index].setPointerItem(ptr);
}

int Inventory::getQuantityAtIndex(int index) {
    return this->slots[index].getQuantity();
}

void Inventory::addQuantityAtIndex(int index, int quantity) {
    this->getSlots()[index].addQuantity(quantity);
}

void Inventory::print() {
    for (int i=0; i<27; i++) {
        cout << "[" << this->slots[i].getId() << " " << this->slots[i].getQuantity() << "] ";
        if (i%9 == 8) {
            cout << endl;
        } 
    }
}