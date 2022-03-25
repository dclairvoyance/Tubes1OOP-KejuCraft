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
            this->slots(i, j) = Slot();
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

bool CraftingTable::isSlotEmpty(int index) {
    return this->slots(getRow(index), getCol(index)).getPointerItem() == NULL;
}

bool CraftingTable::isSameItem(int index, Item* ptr) {
    return this->slots(getRow(index), getCol(index)).getPointerItem() == ptr;
}

void CraftingTable::setPtrItem(int index, Item* ptr) {
    this->slots(getRow(index), getCol(index)).setPointerItem(ptr);
}

void CraftingTable::addPtrItem(int index, int quantity) {
    /* decrease quantity of container */
    this->slots(getRow(index), getCol(index)).getPointerItem()->addQuantity(-1 * quantity);
    /* increase quantity of crafting slot */
    this->slots(getRow(index), getCol(index)).addQuantity(quantity);
}

void CraftingTable::discardPtrItem(int index, int quantity) {
    /* bisa jadi tidak mencukupi */
    this->slots(getRow(index), getCol(index)).addQuantity(-1 * quantity);
    this->slots(getRow(index), getCol(index)).getPointerItem()->addQuantity(quantity);
}

void CraftingTable::discardAllPtrItem(int index) { // atau diubah jadi quantity
    int quantityInSlot;
    quantityInSlot = this->slots(getRow(index), getCol(index)).getQuantity();
    discardPtrItem(index, quantityInSlot);
}

void CraftingTable::decPtrItem(int index, int quantity) {
    this->slots(getRow(index), getCol(index)).addQuantity(-1 * quantity);
}

void CraftingTable::resetCraftingTable() {
    for (int i = 0; i < MAX_ROW*MAX_COL; i++) {
        discardAllPtrItem(i);
    }
}

string CraftingTable::getSlotId(int row, int col) {
    return this->slots(row, col).getId();
}

int CraftingTable::getItemId(int row, int col) {
    return this->slots(row, col).getPointerItem()->getId();
}

string CraftingTable::getItemName(int row, int col) {
    return this->slots(row, col).getPointerItem()->getName();
}

int CraftingTable::getQuantity(int row, int col) {
    return this->slots(row, col).getQuantity();
}

int CraftingTable::countOccurence(string itemName, int indexDest) {
    int count = 0;
    for (int i=0; i<indexDest; i++) {
        if (this->getItemName(i) == itemName) {
            count++;
        }
    }
    return count;
}

int CraftingTable::findIndex(string slotIdDest){
    if (stoi(slotIdDest.substr(1)) < 0 || stoi(slotIdDest.substr(1)) >= MAX_ROW*MAX_COL) {
        return -1;
    }
    return stoi(slotIdDest.substr(1)); 
}

int CraftingTable::getQuantity(int index){
    return this->slots(getRow(index), getCol(index)).getQuantity();
}

string CraftingTable::getItemName(int index){
    if (this->slots(getRow(index), getCol(index)).getPointerItem() == NULL) {
        return "null";
    }
    return this->slots(getRow(index), getCol(index)).getPointerItem()->getName();
}

void CraftingTable::setQuantity(int index, int quantity){
    this->slots(getRow(index), getCol(index)).setQuantity(quantity);
}

void CraftingTable::addQuantity(int index, int quantity){
    this->slots(getRow(index), getCol(index)).addQuantity(quantity);
}

int CraftingTable::getItemId(int index){
    return this->slots(getRow(index), getCol(index)).getPointerItem()->getId();
}

string CraftingTable::getSlotId(int index){
    return this->slots(getRow(index), getCol(index)).getId();
}

Item* CraftingTable::getPtrItem(int index) {
    return this->slots(getRow(index), getCol(index)).getPointerItem();
}