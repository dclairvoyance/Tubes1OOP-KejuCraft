// File Slot.cpp
// Berisi implementasi class Slot

#include <iostream>
#include "Slot.h"

Slot::Slot() {
    this->id = "I0";
    this->ptrItem = NULL;
}

Slot::Slot(string id, Item* ptr) {
    this->id = id;
    this->ptrItem = ptr;
}

void Slot::setId(string id) {
    this->id = id;
}

string Slot::getId() {
    return this->id;
}

Item* Slot::getPointerItem() {
    return this->ptrItem;
}

void Slot::setPointerItem(Item* ptr) {
    this->ptrItem = ptr;
}

SlotInventory::SlotInventory() : Slot() {
    this->quantity = 0;
}

SlotInventory::SlotInventory(string id, Item* item, int quantity) : Slot(id, item) {
    item->addQuantity(quantity);
    this->quantity = quantity;
}

SlotInventory::~SlotInventory() {
    delete[] this->ptrItem;
}

SlotInventory& SlotInventory::operator=(const SlotInventory& other) {
    this->id = other.id;
    this->quantity = other.quantity;
    delete[] this->ptrItem;
    this->ptrItem = new Item;
    this->ptrItem = other.ptrItem;
    return *this;
}

int SlotInventory::getQuantity() {
    return this->quantity;
}

void SlotInventory::setQuantity(int quantity) {
    this->quantity = quantity;
}

void SlotInventory::addQuantity(int quantity) {
    this->quantity += quantity;
}

void SlotInventory::addItemTo(SlotInventory& other) {
    int total = this->quantity + other.quantity;
    other.quantity = total>64 ? 64 : total;
    this->quantity = total - other.quantity;
} // Memindahkan item ke slot lain