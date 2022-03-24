// File Slot.h
// Berisi definisi class Slot

#ifndef _SLOT_H_
#define _SLOT_H_

#define MAX_CAP 64
#include <iostream>
#include "Item.h"

class Slot {
protected:
    string id;      /* I0, I1, ... */
    Item* ptrItem;  /* pointer to Item */
    int quantity;   /* quantity of item in slot */
public:
    /* main */
    Slot();                                     /* default constructor */
    Slot(string id, Item* item, int quantity);  /* user-defined constructor */
    ~Slot();                                    /* destructor */
    Slot& operator=(const Slot& other);         /* assignment operator overloading */
    void setId(string id);                      /* set id attribute of slot */
    string getId();                             /* get id attribute of slot */
    void setPointerItem(Item* ptr);             /* set item pointed by slot */
    Item* getPointerItem();                     /* get item pointed by slot */
    void setQuantity(int quantity);             /* set quantity of item in slot */
    int getQuantity();                          /* get quantity of item in slot */
    void addQuantity(int quantity);             /* add quantity of item in slot (used in give) */
    void addItemTo(Slot& other);                /* move from *this* to other slot */
};

#endif