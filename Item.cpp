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

Item& Item::operator=(const Item& other){
    this->name = other.name;
    this->type = other.type;
    this->quantity = other.quantity;
    return *this;
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
    vector<int> arr;
    this->arrDurability = arr;
} // Pertama kali dapet, durability = 10

Tool::Tool(int id, string name, string type, int quantity) : Item(id, name, type, quantity) {
    vector<int> arr;
    arr.assign(quantity, 10);
    this->arrDurability = arr;
}

Tool::~Tool() {}

int Tool::getDurabilityAtPos(int pos) {
    return this->arrDurability[pos-1];
}

void Tool::useAtPos(int pos) { // butuh exception pas durability 0
    this->arrDurability[pos-1]--;
    if (this->arrDurability[pos-1] == 0) {
        this->arrDurability.erase(this->arrDurability.begin()+pos-1);
        this->quantity--;
    }
}

void Tool::removeDurabilityAtPos(int pos) {
    this->quantity--;
    this->arrDurability.erase(this->arrDurability.begin()+pos-1);
}

void Tool::insertDurabilityAtPos(int pos, int durability) {
    this->quantity++;
    this->arrDurability.emplace(this->arrDurability.begin()+pos-1, durability);
}

void Tool::decrementDurabilityAtPos(int pos) {
    this->arrDurability[pos-1]--;
}

void Tool::printDurabilities() {
    cout << "[ ";
    for (int i=0; i<this->quantity; i++) {
        cout << this->arrDurability[i] << " ";
    }
    cout << "]" << endl;
}

void Tool::print() {
    Item::print();
    cout << "durability: ";
    this->printDurabilities();
}