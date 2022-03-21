// File Slot.cpp
// Berisi implementasi class Slot

#include <iostream>
#include "Slot.h"

Slot::Slot() {
    this->id = "I0";
    this->ptrItem = NULL;
    this->quantity = 0;
}

Slot::Slot(string id, Item* ptr, int quantity) {
    this->id = id;
    this->ptrItem = ptr;
    this->quantity = quantity;
}

Slot::~Slot() {
    delete[] this->ptrItem;
}

void Slot::setId(string id) {
    this->id = id;
}

string Slot::getId() {
    return this->id;
}

void Slot::setPointerItem(Item* ptr) {
    this->ptrItem = ptr;
}

Item* Slot::getPointerItem() {
    return this->ptrItem;
}

void Slot::setQuantity(int quantity) {
    this->quantity = quantity;
}

int Slot::getQuantity() {
    return this->quantity;
}

void Slot::addQuantity(int quantity) {
    this->quantity += quantity;
}

void Slot::addItemTo(Slot& other) {
    int total = this->quantity + other.quantity;
    other.quantity = total>64 ? 64 : total;
    this->quantity = total - other.quantity;
}

Slot& Slot::operator=(const Slot& other) {
    this->id = other.id;
    this->quantity = other.quantity;
    delete[] this->ptrItem;
    this->ptrItem = new Item;
    this->ptrItem = other.ptrItem;
    return *this;
}