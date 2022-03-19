#include <iostream>
#include "CraftingRecipe.h"
using namespace std;

CraftingRecipe::CraftingRecipe(){
    this->row = 3;
    this->col = 3;
    this->resep = new Item* [this->row];
    for (int i = 0; i<this->row; i++){
        resep[i] = new Item[this->col];
    }
    this->output = Item();
    this->quantity = 0;
}

CraftingRecipe::CraftingRecipe(int row, int col, Item** resep, Item output, int quantity){
    this->row = row;
    this->col = col;
    
    this->resep = new Item* [row];
    for (int i = 0; i<row; i++){
        this->resep[i] = new Item[col];
    }

    for (int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            this->resep[i][j] = resep[i][j];
        }
    }
    
    
    this->output = output;
    this->quantity = quantity;
}

CraftingRecipe::CraftingRecipe(const CraftingRecipe& other){
    this->row = other.row;
    this->col = other.col;
    for (int i = 0; i<row; i++){
        this->resep[i] = new Item[col];
    }

    for (int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            this->resep[i][j] = other.resep[i][j];
        }
    }

    this->output = other.output;
    this->quantity = other.quantity;
}

CraftingRecipe& CraftingRecipe::operator=(const CraftingRecipe& other){
    this->row = other.row;
    this->col = other.col;
    
    for (int i = 0; i<row; i++){
        this->resep[i] = new Item[col];
    }

    for (int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            this->resep[i][j] = other.resep[i][j];
        }
    }
    
    this->output = other.output;
    this->quantity = other.quantity;
    return *this;
}

CraftingRecipe :: ~CraftingRecipe(){
    delete[] this->resep;
}

void CraftingRecipe::print(){
    cout << "Row: " << this->row << endl;
    cout << "Col: " << this->col << endl;
    for (int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            cout << resep[i][j].getName() << " ";
        }
        cout << endl;
    }
    cout << "Hasil: " << this->output.getName() << endl;
    cout << "Jumlah: "<< this->quantity << endl;
}