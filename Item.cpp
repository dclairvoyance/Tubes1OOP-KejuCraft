// File Item.cpp
// Berisi implementasi kelas Item

#include <iostream>
#include "Item.h"

int Item::numOfItem = 0;

Item::Item() : id(numOfItem++) {
    this->name = "null";
    this->type = "null";
    this->quantity = 1;
}

Item::Item(string name, string type, int quantity) : id(numOfItem++) {
    this->name = name;
    this->type = type;
    this->quantity = quantity;
}

void Item::add() { // butuh exception pas penuh
    this->quantity++;
}

void Item::remove() { // butuh exception pas kosong
    this->quantity--;
}

void Item::print() {
    cout << "id: " << this->id << endl;
    cout << "name: " << this->name << endl;
    cout << "type: " << this->type << endl;
    cout << "quantity: " << this->quantity << endl;
}

NonTool::NonTool() : Item() {}

NonTool::NonTool(string name, string type, int quantity) : Item(name, type, quantity) {}

void NonTool::stack() {} // kayaknya masukin inventory.cpp

void NonTool::print() {
    Item::print();
}

Tool::Tool() : Tool("null", "null", 1, 10) {} // Pertama kali dapet, durability = 10

Tool::Tool(string name, string type, int quantity, int durability) : Item(name, type, quantity) {
    this->durability = durability;
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