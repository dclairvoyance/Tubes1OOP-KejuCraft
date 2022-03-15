// File Item.h
// Menyimpan definisi class Item

#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>
using namespace std;

class Item {
protected:
    const int id;
    string name;
    string type;
    int quantity;
    static int numOfItem;
public:
    Item();
    Item(string name, string type, int quantity);
    void add();
    void remove();
    virtual void print();
};

class NonTool : public Item {
private:
public:
    NonTool();
    NonTool(string name, string type, int quantity);
    void stack();
    void print();
};

class Tool : public Item {
private:
    int durability;
public:
    Tool();
    Tool(string name, string type, int quantity, int durability);
    void use();
    void print();
};

#endif