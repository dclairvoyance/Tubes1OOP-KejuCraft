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
    void addQuantity(int index, int quantity);          /* add slot quantity at certain index */
    void setQuantity(int index, int quantity);          /* set slot quantity at certain index */
    int getQuantity(int index);                         /* get slot quantity at certain index */
    int getItemId(int index);                           /* get itemId at certain index */
    string getItemName(int index);                      /* get itemName at certain index */
    Item* getPtrItem(int index);                        /* get ptrItem at certain index */
    void setPtrItem(int index, Item* ptr);              /* set ptrItem at certain index */
    string getSlotId(int index);                        /* get slotId at certain index */
    int findIndex(Item* ptr);                           /* find index of the first not-full slot and has certain ptrItem */ 
    int findIndex(string id);                           /* find index by certain slotId */ 
    int findPosForGIVE(string itemName);                /* find the first empty slot pos [1..n] by certain itemName */
    int findPosForMOVE(string itemName, string slotId); /* counting pos [1..n] from I0 until slotId who has same itemName */ 
    int findPosAfterMOVE(string itemName, string slotIdSrc, string slotIdDest); /* counting pos [1..n] for MOVE purposes */
    bool isSlotEmpty(int index);                        /* return true if slot is empty at index */
    int countOccurence(string itemName);                /* count occurence of certain itemName */
    void print();                                       /* printInfo */
};

#endif