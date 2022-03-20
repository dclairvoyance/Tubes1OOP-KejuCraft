// File Item.h
// Menyimpan definisi class Item

#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>
#include <vector>
using namespace std;

class Item {
protected:
    const int id;       /* ID of item from item.txt */
    string name;        /* name of item from item.txt */
    string type;        /* type of item from item.txt */
    int quantity;       /* total items owned by player */
public:
    Item();                                                 /* default constructor */
    Item(int id, string name, string type, int quantity);   /* user-defined constructor */ 
    virtual ~Item();                                        /* destructor */
    int getId();                                            /* get id attribute of item */
    string getName();                                       /* get name attribute of item */
    string getType();                                       /* get type attribute of item */
    int getQuantity();                                      /* get quantity attribute of item */
    void setQuantity(int quantity);
    void addQuantity(int quantity);                         /* add quantity of item owned by player */
    virtual void print(); 
    Item& operator=(const Item& other);                                  /* print info */
};

class NonTool : public Item {
private:
public:
    NonTool();                                                  /* default constructor */
    NonTool(int id, string name, string type, int quantity);    /* user-defined constructor */
    virtual ~NonTool();                                         /* destructor */
    void print();                                               /* print info */
};

class Tool : public Item {
private:
    vector<int> arrDurability;     /* durability of item */
public:
    Tool();                                                                 /* default constructor */
    Tool(int id, string name, string type, int quantity);   /* user-defined constructor */
    virtual ~Tool();                                                        /* destructor */
    int getDurabilityAtPos(int pos);                                                    /* get durability attribute of tool */
    void insertDurabilityAtPos(int pos, int durability);
    void decrementDurabilityAtPos(int pos);
    void removeDurabilityAtPos(int pos);
    void useAtPos(int pos);
    void printDurabilities();                                                             /* use nontool (decrease durability) */
    void print();                                                           /* print info */
};

#endif