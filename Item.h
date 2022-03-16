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
public:
    Item();
    Item(int id, string name, string type, int quantity);
    virtual ~Item();
    int getId();
    string getName();
    string getType();
    int getQuantity();
    virtual void print();
};

class NonTool : public Item {
private:
public:
    NonTool();
    NonTool(int id, string name, string type, int quantity);
    ~NonTool();
    void stack();
    void print();
};

class Tool : public Item {
private:
    int durability;
public:
    Tool();
    Tool(int id, string name, string type, int quantity, int durability);
    ~Tool();
    int getDurability();
    void use();
    void print();
};

#endif