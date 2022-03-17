// File Slot.h
// Berisi definisi class Slot

#ifndef _SLOT_H_
#define _SLOT_H_

#define MAX_CAP 64
#include <iostream>
#include "Item.h"

class Slot {
protected:
    string id;
    Item* ptrItem;
public:
    Slot();
    Slot(string id, Item* item);
    void setId(string id);
    Item* getPointerItem();
    void setPointerItem(Item* ptr);
    string getId();
};

class SlotInventory : public Slot {
private:
    int quantity;
public:
    SlotInventory();
    SlotInventory(string id, Item* item, int quantity);
    ~SlotInventory();
    SlotInventory& operator=(const SlotInventory& other);
    int getQuantity();
    void setQuantity(int quantity);
    void addQuantity(int quantity);
    void addItemTo(SlotInventory& other); // Memindahkan item ke slot lain
};

class SlotCrafting : public Slot {
private:
public:
    SlotCrafting();
    void put(); // Menaruh item pada suatu slot
};

#endif