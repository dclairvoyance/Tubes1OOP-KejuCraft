// File CraftingTable.cpp
// Berisi implementasi class CraftingTable

#include <iostream>
#include "CraftingTable.h"
#include "Inventory.h"
#include "Slot.h"
using namespace std;

CraftingTable::CraftingTable() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            this->slots(i, j) = SlotInventory();
            string id = "C" + to_string(i*MAX_ROW + j);
            this->slots(i, j).setId(id);
        }
    }
}

CraftingTable::~CraftingTable() {
    /* otomatis destruct */
}

int CraftingTable::getRow(int id){
    return id/3;
}

int CraftingTable::getCol(int id){
    return id%3;
}

Slot CraftingTable::getSlot(int index){
    return this->slots(getRow(index), getCol(index));
}

SlotInventory CraftingTable::getSlotInventory(int index){
    return this->slots(getRow(index), getCol(index));
}

bool CraftingTable::isSlotEmptyAtIndex(int index) {
    return this->getSlot(index).getPointerItem() == NULL;
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
    getSlotInventory(index).addQuantity(quantity);
}

void CraftingTable::discardPtrItem(int index, int quantity) {
    /* bisa jadi tidak mencukupi */
    getSlotInventory(index).addQuantity(-1 * quantity);
    getSlotInventory(index).getPointerItem()->addQuantity(quantity);
}

void CraftingTable::discardAllPtrItem(int index) { // atau diubah jadi quantity
    int quantityInSlot;
    quantityInSlot = getSlotInventory(index).getQuantity();
    discardPtrItem(index, quantityInSlot);
}

void CraftingTable::decPtrItem(int index, int quantity) {
    getSlotInventory(index).addQuantity(-1 * quantity);
}

/*
bool CraftingTable::checkCraft() {
    return ;
}

Item* CraftingTable::craft() {
    return ;
}
*/

void CraftingTable::resetCraftingTable() {
    for (int i = 0; i < MAX_ROW*MAX_COL; i++) {
        discardAllPtrItem(i);
    }
}

/*
void CraftingTable::print() {

}
*/

/* opt: either put here or Slot.h */

string CraftingTable::getSlotIdByCoord(int row, int col) {
    return this->slots(row, col).getId();
}

int CraftingTable::getItemIdByCoord(int row, int col) {
    return this->slots(row, col).getPointerItem()->getId();
}

string CraftingTable::getItemNameByCoord(int row, int col) {
    return this->slots(row, col).getPointerItem()->getName();
}

int CraftingTable::getQuantityByCoord(int row, int col) {
    return this->slots(row, col).getQuantity();
}

int CraftingTable::countOccurence(string itemName, int indexDest) {
    int count = 0;
    for (int i=0; i<indexDest; i++) {
        if (this->getItemNameAtIndex(i) == itemName) {
            count++;
        }
    }
    return count;
}

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
    return this->slots(getRow(index), getCol(index)).getQuantity();
}

string CraftingTable::getItemNameAtIndex(int index){
    if (this->getSlot(index).getPointerItem() == NULL) {
        return "null";
    }
    return this->getSlot(index).getPointerItem()->getName();
}

void CraftingTable::setQuantityAtIndex(int index, int quantity){
    this->slots(getRow(index), getCol(index)).setQuantity(quantity);
}

void CraftingTable::addQuantityAtIndex(int index, int quantity){
    this->slots(getRow(index), getCol(index)).addQuantity(quantity);
}

void CraftingTable::setPtrItemAtIndex(int index, Item* ptr){
    this->slots(getRow(index), getCol(index)).setPointerItem(ptr);
}

int CraftingTable::getItemIdAtIndex (int index){
    return this->slots(getRow(index), getCol(index)).getPointerItem()->getId();
}

string CraftingTable::getSlotIdAtIndex(int index){
    return this->slots(getRow(index), getCol(index)).getId();
}

Item* CraftingTable::getPtrItemAtIndex(int index) {
    return this->getSlot(index).getPointerItem();
}