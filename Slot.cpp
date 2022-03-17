// File Slot.cpp
// Berisi implementasi class Slot

#include <iostream>
#include "Slot.h"

Slot::Slot() {
    this->id = "I0";
    this->item = NULL;
}

Slot::Slot(string id, Item* item) {
    this->id = id;
    this->item = item;
}

void Slot::setId(string id) {
    this->id = id;
}

string Slot::getId() {
    return this->id;
}

SlotInventory::SlotInventory() : Slot() {
    this->quantity = 0;
}

SlotInventory::SlotInventory(string id, Item* item, int quantity) : Slot(id, item) {
    item->addQuantity(quantity);
    this->quantity = quantity;
}

SlotInventory::~SlotInventory() {
    delete[] this->item;
}

SlotInventory& SlotInventory::operator=(const SlotInventory& other) {
    this->id = other.id;
    this->quantity = other.quantity;
    delete[] this->item;
    this->item = new Item;
    this->item = other.item;
    return *this;
}

void SlotInventory::setQuantity(int quantity) {
    this->quantity = quantity;
}

void SlotInventory::addItemTo(SlotInventory& other) {
    int total = this->quantity + other.quantity;
    other.quantity = total>64 ? 64 : total;
    this->quantity = total - other.quantity;
} // Memindahkan item ke slot lain