// File Inventory.h
// Berisi definisi class Inventory

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#define MAX_SLOT 27
#include <iostream>
#include "Slot.h"

class Inventory {
private:
    Slot* slots;   /* array of SlotInventory */
public:
    Inventory();                                        /* default constructor */
    Inventory(const Inventory& other);                  /* copy constructor */
    ~Inventory();                                       /* destructor */
    Inventory& operator=(const Inventory& other);       /* assignment operator overloading */
    Slot* getSlots();                                   /* get slots attribute (array of Slot) */
    int findIndexEmpty();                               /* find the first empty slot from Inventory */
    int countSlotEmpty();                               /* count empty slot */
    void addQuantityAtIndex(int index, int quantity);   /* add slot quantity at certain index */
    void setQuantityAtIndex(int index, int quantity);   /* set slot quantity at certain index */
    int getQuantityAtIndex(int index);                  /* get slot quantity at certain index */
    int getItemIdAtIndex(int index);                    /* get itemId at certain index */
    string getItemNameAtIndex(int index);               /* get itemName at certain index */
    Item* getPtrItemAtIndex(int index);                 /* get ptrItem at certain index */
    string getSlotIdAtIndex(int index);                 /* get slotId at certain index */
    void setPtrItemAtIndex(int index, Item* ptr);       /* set ptrItem at certain index */
    int findIndexItem(Item* ptr);                       /* find index of the first not-full slot and has certain ptrItem */ 
    int findIndexBySlotId(string id);                   /* find index by certain slotId */ 
    int findPosForGIVE(string itemName);                /* find the first empty slot pos [1..n] by certain itemName */
    int findPosForMOVE(string itemName, string slotId); /* counting pos [1..n] from I0 until slotId who has same itemName */ 
    int findPosAfterMOVE(string itemName, string slotIdSrc, string slotIdDest); /* counting pos [1..n] for MOVE purposes */
    bool isSlotEmptyAtIndex(int index);                 /* return true if slot is empty at index */
    void print();                                       /* printInfo */
    int countOccurence(string itemName);
};

#endif