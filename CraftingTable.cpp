// File CraftingTable.cpp
// Berisi implementasi class CraftingTable

#include <iostream>
#include "CraftingTable.h"

CraftingTable::CraftingTable() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            this->slots(i, j) = SlotInventory();
            string id = "C" + to_string(i*MAX_ROW + j);
            this->slots(i, j).setId(id);
        }
    }
}

CraftingTable::CraftingTable(const CraftingTable& other) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            
        }
    }
}

CraftingTable::~CraftingTable() {
    /* otomatis destruct */
}

CraftingTable& CraftingTable::operator=(const CraftingTable& other) {

}

int CraftingTable::getRow(int id) {
    return id/3;
}

int CraftingTable::getCol(int id) {
    return id%3;
}

SlotInventory CraftingTable::getSlot(int index) {
    return this->slots(getRow(index), getCol(index));
}

bool CraftingTable::isSlotEmpty(int index) {
    return getSlot(index).getQuantity() == 0;
}

bool CraftingTable::isSameItem(int index, Item* ptr) {
    return getSlot(index).getPointerItem() == ptr;
}

void CraftingTable::setPtrItem(int index, Item* ptr) {
    getSlot(index).setPointerItem(ptr);
}

void CraftingTable::addPtrItem(int index, int quantity) {
    /* decrease quantity of container */
    getSlot(index).getPointerItem()->addQuantity(-1 * quantity);
    /* increase quantity of crafting slot */
    getSlot(index).addQuantity(quantity);
}

void CraftingTable::discardPtrItem(int index, int quantity) {
    /* bisa jadi tidak mencukupi */
    getSlot(index).addQuantity(-1 * quantity);
    getSlot(index).getPointerItem()->addQuantity(quantity);
}

void CraftingTable::discardAllPtrItem(int index) { // atau diubah jadi quantity
    int quantityInSlot;
    quantityInSlot = getSlot(index).getQuantity();
    discardPtrItem(index, quantityInSlot);
}

void CraftingTable::decPtrItem(int index, int quantity) {
    getSlot(index).addQuantity(-1 * quantity);
}

bool CraftingTable::checkCraft() {
    return ;
}

Item* CraftingTable::craft() {
    return ;
}

void CraftingTable::resetCraftingTable() {
    for (int i = 0; i < MAX_ROW*MAX_COL; i++) {
        discardAllPtrItem(i);
    }
}

void CraftingTable::print() {

}
/* opt: either put here or Slot.h */

int CraftingTable::findIndexBySlotId(string slotIdDest){
    for (int i = 0; i<MAX_ROW; i++){
        for (int j = 0; j<MAX_COL; j++){
            string idSlots = this->slots(i,j).getId();
            if (slotIdDest == idSlots){
                return (i*MAX_ROW + j);
            }
        }
    }
    return -1; 
}

int CraftingTable::getQuantityAtIndex(int index){
    return this->slots(getRow(index), getCol(index)).getPointerItem()->getQuantity();
}

string CraftingTable::getItemNameAtIndex(int index){
    return this->slots(getRow(index), getCol(index)).getPointerItem()->getName();
}

void CraftingTable::setQuantityAtIndex(int index, int quantity){
    this->slots(getRow(index), getCol(index)).getPointerItem()->setQuantity(quantity);
}

void CraftingTable::setPtrItemAtIndex(int index, Item* ptr){
    this->slots(getRow(index), getCol(index)).setPointerItem(ptr);
}

int CraftingTable::getItemIdAtIndex (int index){
    return this->slots(getRow(index), getCol(index)).getPointerItem()->getId();
}