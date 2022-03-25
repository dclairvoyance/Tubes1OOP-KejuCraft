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

int Inventory::findIndex(Item* ptr) {
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->slots[i].getPointerItem() == ptr && this->slots[i].getQuantity() < 64) {
            return i;
        }
    }
    return -1;
}

int Inventory::findIndex(string id) {
    if (stoi(id.substr(1)) < 0 || stoi(id.substr(1)) >= MAX_SLOT) {
        return -1;
    }
    return stoi(id.substr(1));
}

int Inventory::findPosForGIVE(string itemName) {
    int count = 0;
    for (int i=0; i<MAX_SLOT; i++) {
        if (this->getPtrItem(i) == NULL) {
            count++;
            return count;
        } else if (this->getItemName(i) == itemName) {
            count++;
        }
    }
    return -1;
}

int Inventory::findPosForMOVE(string itemName, string slotId) {
    int count = 0;
    int index = 0;
    while (this->slots[index].getId() != slotId) {
        if (this->getItemName(index) == itemName) {
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
        if (this->getItemName(index) == itemName && this->getSlotId(index) != slotIdSrc) {
            count++;
        }
        index++;
    }
    return count+1;
}

int Inventory::getItemId(int index) {
    if (this->getPtrItem(index) == NULL) {
        return 0;
    }
    return this->getPtrItem(index)->getId();
}

int Inventory::getQuantity(int index) {
    return this->slots[index].getQuantity();
}

string Inventory::getItemName(int index) {
    if (this->getPtrItem(index) == NULL) {
        return "null";
    }
    return this->getPtrItem(index)->getName();
}

Item* Inventory::getPtrItem(int index) {
    return this->slots[index].getPointerItem();
}

string Inventory::getSlotId(int index) {
    return this->slots[index].getId();
}

void Inventory::addQuantity(int index, int quantity) {
    this->slots[index].addQuantity(quantity);
}

void Inventory::setQuantity(int index, int quantity) {
    this->slots[index].setQuantity(quantity);
}

void Inventory::setPtrItem(int index, Item* ptr) {
    this->slots[index].setPointerItem(ptr);
}

bool Inventory::isSlotEmpty(int index) {
    return this->slots[index].getPointerItem() == NULL;
}

Slot* Inventory::getSlots() {
    return this->slots;
}

void Inventory::print() {
    for (int i=0; i<MAX_SLOT; i++) {
        cout << "[" << this->slots[i].getId() << " ";
        if (this->getPtrItem(i) != NULL) {
            cout << this->getItemId(i) << " ";
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
        if (this->getItemName(i) == itemName) {
            count++;
        }
    }
    return count;
}