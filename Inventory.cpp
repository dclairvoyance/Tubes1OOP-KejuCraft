// File Inventory.cpp
// Berisi implementasi class Inventory

#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {
    this->slots = new Slot[MAX_SLOT];
    for (int i=0; i<MAX_SLOT; i++) {
        string id = "I" + to_string(i);
        this->slots[i].setId(id);
    }
}

Inventory::Inventory(const Inventory& other) {
    for (int i=0; i<MAX_SLOT; i++) {
        this->slots[i] = other.slots[i];
    }
}

Inventory::~Inventory() {
    delete[] this->slots;
}

Inventory& Inventory::operator=(const Inventory& other) {
    delete[] this->slots;
    for (int i=0; i<MAX_SLOT; i++) {
        this->slots[i] = other.slots[i];
    }
    return *this;
}

int Inventory::countSlotEmpty() {
    int count = 0;
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->slots[i].getPointerItem() == NULL) {
            count++;
        }
    }
    return count;
}

int Inventory::findIndexEmpty() {
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->slots[i].getPointerItem() == NULL) {
            return i;
        }
    }
    return -1;
}

int Inventory::findIndexItem(Item* ptr) {
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->slots[i].getPointerItem() == ptr && this->slots[i].getQuantity() < 64) {
            return i;
        }
    }
    return -1;
}

int Inventory::findIndexBySlotId(string id) {
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->slots[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

int Inventory::findPosForGIVE(string itemName) {
    int count = 0;
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->getPtrItemAtIndex(i) == NULL) {
            count++;
            return count;
        } else if (this->getItemNameAtIndex(i) == itemName) {
            count++;
        }
    }
    return -1;
}

int Inventory::findPosForMOVE(string itemName, string slotId) {
    int count = 0;
    int index = 0;
    while (this->slots[index].getId() != slotId) {
        if (this->getItemNameAtIndex(index) == itemName) {
            count++;
        }
        index++;
    }
    return count+1;
}

int Inventory::findPosAfterMOVE(string itemName, string slotIdSrc, string slotIdDest) {
    int count = 0;
    int index = 0;
    while (this->slots[index].getId() != slotIdDest) {
        if (this->getItemNameAtIndex(index) == itemName && this->getSlotIdAtIndex(index) != slotIdSrc) {
            count++;
        }
        index++;
    }
    return count+1;
}

int Inventory::getItemIdAtIndex(int index) {
    if (this->getPtrItemAtIndex(index) == NULL) {
        return 0;
    }
    return this->getPtrItemAtIndex(index)->getId();
}

int Inventory::getQuantityAtIndex(int index) {
    return this->slots[index].getQuantity();
}

string Inventory::getItemNameAtIndex(int index) {
    if (this->getPtrItemAtIndex(index) == NULL) {
        return "null";
    }
    return this->getPtrItemAtIndex(index)->getName();
}

Item* Inventory::getPtrItemAtIndex(int index) {
    return this->slots[index].getPointerItem();
}

string Inventory::getSlotIdAtIndex(int index) {
    return this->slots[index].getId();
}

void Inventory::addQuantityAtIndex(int index, int quantity) {
    this->slots[index].addQuantity(quantity);
}

void Inventory::setQuantityAtIndex(int index, int quantity) {
    this->slots[index].setQuantity(quantity);
}

void Inventory::setPtrItemAtIndex(int index, Item* ptr) {
    this->slots[index].setPointerItem(ptr);
}

bool Inventory::isSlotEmptyAtIndex(int index) {
    return this->slots[index].getPointerItem() == NULL;
}

Slot* Inventory::getSlots() {
    return this->slots;
}

void Inventory::print() {
    for (int i=0; i<MAX_SLOT; i++) {
        cout << "[" << this->slots[i].getId() << " ";
        if (this->getPtrItemAtIndex(i) != NULL) {
            cout << this->getItemIdAtIndex(i) << " ";
        } 
        cout << this->slots[i].getQuantity() << "] ";

        if (i%9 == 8) {
            cout << endl;
        } 
    }
}

int Inventory::countOccurence(string itemName){
    int count = 0;
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->getItemNameAtIndex(i) == itemName) {
            count++;
        }
    }
    return count;
}