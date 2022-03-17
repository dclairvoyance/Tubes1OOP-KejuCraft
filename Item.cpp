// File Item.cpp
// Berisi implementasi kelas Item

#include <iostream>
#include "Item.h"

Item::Item() : id(0) {
    this->name = "null";
    this->type = "null";
    this->quantity = 0;
}

Item::Item(int id, string name, string type, int quantity) : id(id) {
    this->name = name;
    this->type = type;
    this->quantity = quantity;
}

Item::~Item() {}

int Item::getId() {
    return this->id;
}

string Item::getName() {
    return this->name;
}

string Item::getType() {
    return this->type;
}

int Item::getQuantity() {
    return this->quantity;
}

void Item::addQuantity(int quantity) {
    this->quantity += quantity;
}

void Item::print() {
    cout << "id: " << this->id << endl;
    cout << "name: " << this->name << endl;
    cout << "type: " << this->type << endl;
    cout << "quantity: " << this->quantity << endl;
}

NonTool::NonTool() : Item() {}

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, type, quantity) {}

void NonTool::print() {
    Item::print();
}

NonTool::~NonTool() {}

Tool::Tool() : Item() {
    this->durability = 10;
} // Pertama kali dapet, durability = 10

Tool::Tool(int id, string name, string type, int quantity, int durability) : Item(id, name, type, quantity) {
    this->durability = durability;
}

Tool::~Tool() {}

int Tool::getDurability() {
    return this->durability;
}

void Tool::use() { // butuh exception pas durability 0
    this->durability--;
    if (this->durability == 0) {
        this->quantity--;
    }
}

void Tool::print() {
    Item::print();
    cout << "durability: " << this->durability << endl;
}