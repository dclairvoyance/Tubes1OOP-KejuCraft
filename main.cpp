#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <string>
#include "Item.h"
#include "Inventory.h"
#include "Slot.h"
#include "CraftingRecipe.h"
#include "CraftingTable.h"
using namespace std;

void printBetter(int index) {
    if (index/10 == 0) {
        cout << " ";
    }
}

int main() {
    // BAGIAN I: Membaca Item
    // Me-construct container untuk tool dan nontool
    map<string, Tool> toolContainer;
    map<string, NonTool> nonToolContainer;

    // Me-construct Inventory dan CraftingTable pemain
    Inventory playerInventory;

    // Crafting table
    CraftingTable tableInventory;

    // Mengeset ke path config
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    // Membaca file item config
    ifstream itemConfigFile(itemConfigPath);
    string intext;

    // Membuat iterator
    map<string, Tool>::iterator itrTool;
    map<string, NonTool>::iterator itrNonTool;
    
    // Memisahkan item tool dan nontool dan meletakkan dalam container masing-masing
    while (getline(itemConfigFile, intext)) {
        stringstream ss(intext);
        string name, type, isTool;
        int id;
        ss >> id >> name >> type >> isTool;
        if (isTool == "TOOL") {
            Tool item(id, name, type, 0); // Durability awal = 10
            toolContainer.insert(pair<string, Tool> (item.getName(), item));
        } else {
            NonTool item(id, name, type, 0);
            nonToolContainer.insert(pair<string, NonTool> (item.getName(), item));
        }
    }

    // Menyelesaikan pembacaan file item config
    itemConfigFile.close();
    cout << "EOF reached.." << endl;

    // BAGIAN II: Membaca Recipe
    // Menghitung banyak recipe
    int recipeCount = 0;
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        recipeCount++;
    }

    // Me-construct CraftingRecipe sebanyak recipeCount
    CraftingRecipe* recipeContainer = new CraftingRecipe[recipeCount];
    int recipeLocation = 0;

    // Mengisi setiap CraftingRecipe
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        string recipeConfigPath = entry.path().string();
        // cout << recipeConfigPath << endl;
        ifstream recipeConfigFile(recipeConfigPath);
        bool isDone = false;
        while (isDone == false){
            // Membaca baris pertama (ROW COL)
            getline(recipeConfigFile, intext);
            stringstream ss(intext);
            int row, col, quantity;
            string itemCraft;
            string itemName;
            Item itemNameResult;
            ss >> row >> col;
            
            // Menyiapkan container untuk string
            string** resep = new string* [row];
            for (int i = 0; i<row; i++){
                resep[i] = new string[col];
            }

            // Membaca dan meletakkan resep crafting dalam container string
            for (int i = 0; i<row; i++){
                getline(recipeConfigFile, intext);
                stringstream ss2(intext);
                for (int j = 0; j<col; j++){
                    ss2 >> itemCraft;
                    resep[i][j] = itemCraft;
                }
            }

            // Membaca baris terakhir (hasil crafting)
            getline(recipeConfigFile, intext);
            stringstream ss3(intext);
            ss3 >> itemName;
            ss3 >> quantity;

            // Mencari nama dari itemName nonTool untuk diletakkan dalam atribut CraftingRecipe
            for (itrNonTool = nonToolContainer.begin(); itrNonTool!=nonToolContainer.end(); itrNonTool++){
                if (itrNonTool->first == itemName){
                    itemNameResult = itrNonTool->second;
                }
            }

            // Mencari nama dari itemName Tool untuk diletakkan dalam atribut CraftingRecipe
            for (itrTool = toolContainer.begin(); itrTool!=toolContainer.end(); itrTool++){
                if (itrTool->first == itemName){
                    itemNameResult = itrTool->second;
                }
            }

            // Meletakkan recipe dalam CraftingRecipe
            CraftingRecipe finalrecipe(row,col,resep,itemNameResult,quantity);
            recipeContainer[recipeLocation] = finalrecipe;
            recipeLocation++;
            isDone = true;
            
        }
    }

    // BAGIAN III: Meng-handle Command
    string command;
    while (cin >> command) {
        // Command SHOW
        if (command == "SHOW") {
            // print craftingTable
            for (int i=0; i<MAX_ROW; i++) {
                cout << "                                    ";
                for (int j=0; j<MAX_COL; j++) {
                    cout << "[" << tableInventory.getSlotId(i, j) << " ";
                    printBetter(i*MAX_COL+j);
                    if (!tableInventory.isSlotEmpty(i*MAX_ROW+j)) {
                        // slot tidak kosong
                        printBetter(tableInventory.getItemId(i, j));
                        cout << tableInventory.getItemId(i, j) << " ";
                        string itemName = tableInventory.getItemName(i, j);
                        string slotId = tableInventory.getSlotId(i, j);
                        itrTool = toolContainer.find(itemName);
                        itrNonTool = nonToolContainer.find(itemName);
                        if (itrTool != toolContainer.end()) { // Jika tool, cetak durability
                            int pos = playerInventory.countOccurence(itemName) + tableInventory.countOccurence(itemName, i*MAX_ROW+j) + 1;
                            printBetter(itrTool->second.getDurabilityAtPos(pos));
                            cout << itrTool->second.getDurabilityAtPos(pos);
                        } else { // Jika nontool, cetak quantity
                            printBetter(tableInventory.getQuantity(i, j));
                            cout << tableInventory.getQuantity(i, j);
                        }
                    } else { 
                        // slot kosong
                        cout << " 0 ";
                        printBetter(tableInventory.getQuantity(i, j));
                        cout << tableInventory.getQuantity(i, j);
                    }
                    cout << "] ";
                }
                cout << endl;
            }

            // print inventory
            for (int i=0; i<MAX_SLOT; i++) {
                cout << "[";
                cout << playerInventory.getSlotId(i) << " ";
                printBetter(i);
                // ada item pada slot
                if (playerInventory.getPtrItem(i) != NULL) {
                    printBetter(playerInventory.getItemId(i));
                    cout << playerInventory.getItemId(i) << " ";
                    string itemName = playerInventory.getItemName(i);
                    string slotId = playerInventory.getSlotId(i);
                    int pos = playerInventory.findPosForMOVE(itemName, slotId);
                    itrTool = toolContainer.find(itemName);
                    itrNonTool = nonToolContainer.find(itemName);
                    if (itrTool != toolContainer.end()) { // Jika tool, cetak durability
                        printBetter(itrTool->second.getDurabilityAtPos(pos));
                        cout << itrTool->second.getDurabilityAtPos(pos);
                    } else { // Jika nontool, cetak quantity
                        printBetter(playerInventory.getQuantity(i));
                        cout << playerInventory.getQuantity(i);
                    }
                } 
                // tidak ada item pada slot
                else {
                    printBetter(playerInventory.getItemId(i));
                    cout << playerInventory.getItemId(i) << " ";
                    printBetter(playerInventory.getQuantity(i));
                    cout << playerInventory.getQuantity(i);
                }
                cout << "] ";

                if (i%9 == 8) {
                    cout << endl;
                }
            }
        } 
        // Command GIVE
        else if (command == "GIVE") {
            string itemName;
            int itemQty;
            cin >> itemName >> itemQty;
            itrTool = toolContainer.find(itemName);
            itrNonTool = nonToolContainer.find(itemName);
            if (itrTool != toolContainer.end()) { // Jika tipe item Tool
                int index = playerInventory.findIndexEmpty();
                int pos = playerInventory.findPosForGIVE(itemName);
                while (itemQty > 0 && index != -1) {
                    itemQty--;
                    playerInventory.addQuantity(index, 1); // Menambah quantity di slot
                    playerInventory.setPtrItem(index, &itrTool->second); // Menunjuk ke alamat item di container
                    itrTool->second.insertDurabilityAtPos(pos, 10); // Durability awal = 10 sekaligus menambah quantity;
                    index = playerInventory.findIndexEmpty();
                }
                // Jika tidak ada slot kosong tersisa 
                if (itemQty > 0) {
                    cout << "Inventory penuh!" << endl;
                }
            } else if (itrNonTool != nonToolContainer.end()) { // Jika tipe item NonTool
                // Temukan semua slot yang berisi item ini
                int index = playerInventory.findIndex(&itrNonTool->second);
                while (itemQty > 0 && index != -1) {
                    int remainingQty = MAX_CAP - playerInventory.getQuantity(index);
                    if (remainingQty >= itemQty) {
                        playerInventory.addQuantity(index, itemQty);
                        itrNonTool->second.addQuantity(itemQty);
                        itemQty = 0;
                    } else {
                        playerInventory.addQuantity(index, remainingQty);
                        itrNonTool->second.addQuantity(remainingQty);
                        itemQty -= remainingQty;
                        index = playerInventory.findIndex(&itrNonTool->second);
                    }
                } // itemQty == 0 atau sudah tidak ada yang bisa ditumpuk
                // Jika masih ada slot kosong
                index = playerInventory.findIndexEmpty();
                while (itemQty > 0 && index != -1) {
                    int QtyToBeAdded;
                    if (itemQty > MAX_CAP) {
                        QtyToBeAdded = MAX_CAP;
                        itemQty -= MAX_CAP;
                    } else {
                        QtyToBeAdded = itemQty;
                        itemQty = 0;
                    }
                    playerInventory.addQuantity(index, QtyToBeAdded);
                    playerInventory.setPtrItem(index, &itrNonTool->second);
                    itrNonTool->second.addQuantity(QtyToBeAdded);
                    index = playerInventory.findIndexEmpty();
                }
                // Jika sudah tidak ada slot kosong
                if (itemQty > 0) {
                    cout << "Inventory penuh!" << endl;
                }
            } else { // Jika tidak ditemukan diantara keduanya
                cout << "Tidak ditemukan nama tersebut sehingga tidak dapat menambahkan item ke inventory" << endl;
            }
        } 
        // Command DISCARD
        else if (command == "DISCARD") {
            string inventorySlotId;
            int itemQty;
            cin >> inventorySlotId >> itemQty;
            int index = playerInventory.findIndex(inventorySlotId);
            string itemName = playerInventory.getItemName(index);
            itrTool = toolContainer.find(itemName);
            itrNonTool = nonToolContainer.find(itemName);
            if (playerInventory.getQuantity(index) < itemQty) {
                cout << "Item tidak mencukupi" << endl;
            } else { // Jika item cukup untuk dihapus
                // Mengurangi quantity di container
                if (itrTool != toolContainer.end()) {
                    int pos = playerInventory.findPosForMOVE(itemName, inventorySlotId);
                    itrTool->second.removeDurabilityAtPos(pos); // Menghapus durability sekaligus mengurangi quantity
                } else {
                    itrNonTool->second.addQuantity(-itemQty);
                }
                // Mengurangi item di slot
                playerInventory.addQuantity(index, -itemQty);
                if (playerInventory.getQuantity(index) == 0) { // Jika habis, hapus pointer item
                    playerInventory.setPtrItem(index, NULL);
                }
            }
        } 
        // Command MOVE
        else if (command == "MOVE") {
            string slotIdSrc;
            int itemQty;
            string slotIdDest;
            cin >> slotIdSrc >> itemQty >> slotIdDest;
            if (slotIdSrc[0] == 'I') { // Jika sumbernya dari slotInventory
                if (slotIdDest[0] == 'I') { // Jika tujuannya ke slotInventory
                    int indexSrc = playerInventory.findIndex(slotIdSrc);
                    int indexDest = playerInventory.findIndex(slotIdDest);
                    if (playerInventory.isSlotEmpty(indexSrc)) {
                        cout << "Slot sumber kosong!" << endl;
                    } else {
                        string itemName = playerInventory.getItemName(indexSrc);
                        itrTool = toolContainer.find(itemName);
                        itrNonTool = nonToolContainer.find(itemName);
                        if (itrTool != toolContainer.end()) {
                            if (playerInventory.isSlotEmpty(indexDest)) {
                                int posBeforeMove = playerInventory.findPosForMOVE(itemName, slotIdSrc);
                                int posAfterMove = playerInventory.findPosAfterMOVE(itemName, slotIdSrc, slotIdDest);
                                int durability = itrTool->second.getDurabilityAtPos(posBeforeMove);
                                itrTool->second.removeDurabilityAtPos(posBeforeMove);
                                itrTool->second.insertDurabilityAtPos(posAfterMove, durability);
                                playerInventory.setQuantity(indexDest, playerInventory.getQuantity(indexSrc));
                                playerInventory.setPtrItem(indexDest, playerInventory.getPtrItem(indexSrc));
                                playerInventory.setQuantity(indexSrc, 0);
                                playerInventory.setPtrItem(indexSrc, NULL);
                            } else {
                                cout << "Item Tool tidak dapat ditumpuk!" << endl;
                            }
                        } else {
                            if (playerInventory.isSlotEmpty(indexDest)) {
                                playerInventory.setQuantity(indexDest, playerInventory.getQuantity(indexSrc));
                                playerInventory.setPtrItem(indexDest, playerInventory.getPtrItem(indexSrc));
                                playerInventory.setQuantity(indexSrc, 0);
                                playerInventory.setPtrItem(indexSrc, NULL);
                            } else {
                                if (playerInventory.getItemName(indexDest) == itemName) {
                                    int itemQtySrc = playerInventory.getQuantity(indexSrc);
                                    int itemQtyDest = playerInventory.getQuantity(indexDest);
                                    int totalQtyDest = (itemQtySrc+itemQtyDest) > MAX_CAP ? MAX_CAP : itemQtySrc+itemQtyDest;
                                    int totalQtySrc = (itemQtySrc+itemQtyDest) > MAX_CAP ? itemQtySrc+itemQtyDest-MAX_CAP : 0;
                                    playerInventory.setQuantity(indexDest, totalQtyDest);
                                    playerInventory.setQuantity(indexSrc, totalQtySrc);
                                    if (playerInventory.getQuantity(indexSrc) == 0) { // Jika kosong setelah pemindahan
                                        playerInventory.setPtrItem(indexSrc, NULL);
                                    }
                                } else {
                                    cout << "Item berbeda tidak dapat ditumpuk!" << endl;
                                }
                            }
                        }
                    }
                } else if (slotIdDest[0] == 'C') { // Jika tujuannya ke slotCrafting
                    int indexSrc = playerInventory.findIndex(slotIdSrc);
                    while (itemQty > 0) {
                        if (playerInventory.isSlotEmpty(indexSrc)) {
                            cout << "Slot sumber kosong!" << endl;
                        } else {
                            int indexDest = tableInventory.findIndex(slotIdDest);
                            int itemQtyDest = tableInventory.getQuantity(indexDest);
                            if (itemQtyDest == 0) { // Jika ingin dipindahkan ke slot kosong
                                string itemNameSrc = playerInventory.getItemName(indexSrc);
                                itrTool = toolContainer.find(itemNameSrc);
                                itrNonTool = nonToolContainer.find(itemNameSrc);
                                if (itrTool != toolContainer.end()) {
                                    int posBeforeMove = playerInventory.findPosForMOVE(itemNameSrc, slotIdSrc);
                                    int posAfterMove = tableInventory.countOccurence(itemNameSrc, indexDest) + playerInventory.countOccurence(itemNameSrc);
                                    int durability = itrTool->second.getDurabilityAtPos(posBeforeMove);
                                    itrTool->second.removeDurabilityAtPos(posBeforeMove);
                                    itrTool->second.insertDurabilityAtPos(posAfterMove, durability);
                                }
                                tableInventory.addQuantity(indexDest, 1);
                                tableInventory.setPtrItem(indexDest, playerInventory.getPtrItem(indexSrc));
                                playerInventory.addQuantity(indexSrc, -1);
                                if (playerInventory.getQuantity(indexSrc) == 0) {
                                    playerInventory.setPtrItem(indexSrc, NULL);
                                }
                            } else {
                                string itemNameDest = tableInventory.getItemName(indexDest);
                                itrTool = toolContainer.find(itemNameDest);
                                itrNonTool = nonToolContainer.find(itemNameDest);
                                if (itrTool != toolContainer.end()) { // Jika item Tool yang akan ditumpuk
                                    cout << "Item Tool tidak dapat ditumpuk!" << endl;
                                } else { // Jika item NonTool yang akan ditumpuk
                                    if (playerInventory.getItemId(indexSrc) != tableInventory.getItemId(indexDest)) { // Jika item berbeda
                                        cout << "Item berbeda tidak dapat ditumpuk!" << endl;
                                    } else {
                                        tableInventory.addQuantity(indexDest, 1);
                                        playerInventory.addQuantity(indexSrc, -1);
                                        if (playerInventory.getQuantity(indexSrc) == 0) { // Jika kosong setelah pemindahan
                                            playerInventory.setPtrItem(indexSrc, NULL);
                                        }
                                    }
                                }
                            }
                        }
                        itemQty--;
                        if (itemQty > 0) {
                            cin >> slotIdDest;
                        }
                    }
                } else {
                    cout << "Id slot tidak valid!" << endl;
                }
            } else if (slotIdSrc[0] == 'C') { // Jika sumbernya dari slotCrafting
                if (slotIdDest[0] == 'I') {
                    int indexSrc = tableInventory.findIndex(slotIdSrc);
                    int indexDest = playerInventory.findIndex(slotIdDest);
                    if (tableInventory.isSlotEmpty(indexSrc)) { // Jika sumbernya kosong
                        cout << "Slot sumber kosong!" << endl;
                    } else {
                        string itemName = tableInventory.getItemName(indexSrc);
                        itrTool = toolContainer.find(itemName);
                        itrNonTool = nonToolContainer.find(itemName);
                        if (itrTool != toolContainer.end()) { // Jika yang dipindahkan adalah item Tool
                            if (playerInventory.isSlotEmpty(indexDest)) {
                                int posBeforeMove = tableInventory.countOccurence(itemName, indexSrc) + playerInventory.countOccurence(itemName) + 1;
                                int posAfterMove = playerInventory.findPosForMOVE(itemName, slotIdDest);
                                int durability = itrTool->second.getDurabilityAtPos(posBeforeMove);
                                itrTool->second.removeDurabilityAtPos(posBeforeMove);
                                itrTool->second.insertDurabilityAtPos(posAfterMove, durability);
                                playerInventory.addQuantity(indexDest, 1);
                                playerInventory.setPtrItem(indexDest, tableInventory.getPtrItem(indexSrc));
                                tableInventory.addQuantity(indexSrc, -1);
                                tableInventory.setPtrItem(indexSrc, NULL);
                            } else {
                                cout << "Item Tool tidak dapat ditumpuk!" << endl;
                            }
                        } else { // Jika yang dipindahkan adalah item NonTool
                            if (playerInventory.isSlotEmpty(indexDest)) {
                                playerInventory.setQuantity(indexDest, tableInventory.getQuantity(indexSrc));
                                playerInventory.setPtrItem(indexDest, tableInventory.getPtrItem(indexSrc));
                                tableInventory.setQuantity(indexSrc, 0);
                                tableInventory.setPtrItem(indexSrc, NULL);
                            } else {
                                if (playerInventory.getItemName(indexDest) == itemName) {
                                    int totalQtyDest = playerInventory.getQuantity(indexDest) + tableInventory.getQuantity(indexSrc) > MAX_CAP ?
                                    MAX_CAP : playerInventory.getQuantity(indexDest) + tableInventory.getQuantity(indexSrc);
                                    int totalQtySrc = playerInventory.getQuantity(indexDest) + tableInventory.getQuantity(indexSrc) > MAX_CAP ?
                                    playerInventory.getQuantity(indexDest) + tableInventory.getQuantity(indexSrc)-MAX_CAP : 0;
                                    playerInventory.setQuantity(indexDest, totalQtyDest);
                                    tableInventory.setQuantity(indexSrc, totalQtySrc);
                                    if (totalQtySrc == 0) {
                                        tableInventory.setPtrItem(indexSrc, NULL);
                                    }
                                } else {
                                    cout << "Item berbeda tidak dapat ditumpuk!" << endl;
                                }
                            }
                        }
                    }
                } else {
                    cout << "Id slot tidak valid!" << endl;
                }
            } else {
                cout << "Id slot tidak valid!" << endl;
            }
        } 
        // Command USE
        else if (command == "USE") {
            string inventorySlotId;
            cin >> inventorySlotId;
            int index = playerInventory.findIndex(inventorySlotId);
            if (index == -1) {
                cout << "Id slot tidak valid!" << endl;
            } else if (playerInventory.getPtrItem(index) == NULL) {
                cout << "Tidak ada item di slot!" << endl;
            } else {
                string itemName = playerInventory.getItemName(index);
                itrTool = toolContainer.find(itemName);
                itrNonTool = nonToolContainer.find(itemName);
                if (itrTool != toolContainer.end()) {
                    int pos = playerInventory.findPosForMOVE(itemName, inventorySlotId);
                    itrTool->second.decrementDurabilityAtPos(pos);
                    if (itrTool->second.getDurabilityAtPos(pos) == 0) { // Jika durability habis
                        itrTool->second.removeDurabilityAtPos(pos);
                        playerInventory.addQuantity(index, -1); // kurangi quantity di slot
                        playerInventory.setPtrItem(index, NULL);
                    }
                } else {
                    cout << "Item NonTool tidak dapat digunakan!" << endl;
                }
            }
        } 
        // Command EXPORT
        else if (command == "EXPORT") {
            string filePath, itemName, outText;
            int idItem, quantity, durability;
            cin >> filePath;
            ofstream itemConfigFileOut(filePath);
            for (int i=0; i<MAX_SLOT; i++) {
                // Perlu dipisah Tool dan NonTool
                // Tool yang dicatat durability, NonTool yang dicatat quantity
                itemName = playerInventory.getItemName(i);
                idItem = playerInventory.getItemId(i);
                itrTool = toolContainer.find(itemName);
                itrNonTool = nonToolContainer.find(itemName);
                if (itrTool != toolContainer.end()) {
                    string slotId = playerInventory.getSlotId(i);
                    int pos = playerInventory.findPosForMOVE(itemName, slotId);
                    durability = itrTool->second.getDurabilityAtPos(pos);
                    outText = to_string(idItem) + ':' + to_string(durability);
                } else {
                    quantity = playerInventory.getQuantity(i);
                    outText = to_string(idItem) + ':' + to_string(quantity);
                }
                itemConfigFileOut << outText;
                if (i != MAX_SLOT-1) {
                    itemConfigFileOut << endl;
                }
            }
        } 
        // Command CRAFT
        else if (command == "CRAFT") {
            Item*** tableContent = new Item** [MAX_ROW];
            int isCrafted = 0;
            for (int i = 0; i<MAX_ROW; i++){
                tableContent[i] = new Item* [MAX_COL];
            }

            for (int i = 0; i<MAX_ROW; i++){
                for (int j = 0; j<MAX_COL; j++){
                    Item* slotContent = tableInventory.getPtrItem(i*MAX_ROW+j);
                    tableContent[i][j] = slotContent;
                }
            }

            int maxWidth = 0; // menentukan lebar maksimum di crafting table
            for (int j = 0; j<MAX_COL; j++){
                int tableWidth = 0;
                for (int i = 0; i<MAX_ROW; i++){
                    if (tableContent[i][j] != NULL){
                        tableWidth = 1;
                    }
                }
                if (tableWidth == 1){
                    maxWidth++;
                }
            }

            int maxHeight = 0; // menentukan tinggi maksimum di crafting table
            for (int i = 0; i<MAX_ROW; i++){
                int tableHeight = 0;
                for (int j = 0; j<MAX_COL; j++){
                    if (tableContent[i][j] != NULL){
                        tableHeight = 1;
                    }
                }
                if (tableHeight == 1){
                    maxHeight++;
                }
            }

            int isFoundTool = 0;
            for (int i = 0; i<MAX_ROW; i++){
                for (int j = 0; j<MAX_COL; j++){
                    if (tableContent[i][j] != NULL){
                        itrTool = toolContainer.find(tableContent[i][j]->getName());
                        if (itrTool != toolContainer.end()){
                            isFoundTool = 1;
                        }
                    }
                }
            }

            if (isFoundTool == 0){
                for (int i = 0; i<recipeCount; i++){
                    if (maxWidth == recipeContainer[i].getCol() && maxHeight == recipeContainer[i].getRow()){
                        string** tableResep = new string* [recipeContainer[i].getRow()];
                        for (int j = 0; j<recipeContainer[i].getRow(); j++){
                            tableResep[j] = new string[recipeContainer[i].getCol()];
                            for (int k = 0; k<recipeContainer[i].getCol(); k++){
                                tableResep[j][k] = recipeContainer[i].getResep(j,k);
                            }
                        }
                        
                        for (int j = 0; j<MAX_ROW-(recipeContainer[i].getRow())+1; j++){
                            for (int k = 0; k<MAX_COL-(recipeContainer[i].getCol())+1; k++){
                                int isSame = 1;
                                for (int m = 0; m<recipeContainer[i].getRow(); m++){
                                    for (int n = 0; n<recipeContainer[i].getCol(); n++){
                                        if (tableContent[j+m][k+n] == NULL){
                                            if (tableResep[m][n] != "-"){
                                                isSame = 0;
                                            }
                                        } else if (tableResep[m][n] != tableContent[j+m][k+n]->getName() && tableResep[m][n] != tableContent[j+m][k+n]->getType()){
                                            isSame = 0;
                                        }
                                    }
                                }

                                if (isSame == 1){
                                    isCrafted = 1;
                                    for (int x = 0; x<MAX_ROW; x++){
                                        for (int y = 0; y<MAX_COL; y++){
                                            if (tableInventory.getPtrItem(x*MAX_ROW+y) != NULL){
                                                tableInventory.getPtrItem(x*MAX_ROW+y)->addQuantity(-1);
                                            
                                                int slotAmount = tableInventory.getQuantity(x*MAX_ROW + y);
                                                
                                                tableInventory.setQuantity(x*MAX_ROW+y,slotAmount-1);
                                                if (slotAmount - 1 == 0){
                                                    tableInventory.setPtrItem(x*MAX_ROW+y, NULL);
                                                }
                                            }
                                        }
                                    }

                                    string itemName = recipeContainer[i].getOutput().getName();
                                    int itemQty = recipeContainer[i].getQuantity();
                                    itrTool = toolContainer.find(itemName);
                                    itrNonTool = nonToolContainer.find(itemName);

                                    if (itrTool != toolContainer.end()) { // Jika tipe item Tool
                                        int index = playerInventory.findIndexEmpty();
                                        int pos = playerInventory.findPosForGIVE(itemName);
                                        while (itemQty > 0 && index != -1) {
                                            itemQty--;
                                            playerInventory.addQuantity(index, 1); // Menambah quantity di slot
                                            playerInventory.setPtrItem(index, &itrTool->second); // Menunjuk ke alamat item di container
                                            itrTool->second.addQuantity(1); // Menambah quantity item di container
                                            itrTool->second.insertDurabilityAtPos(pos, 10); // Durability awal = 10;
                                            index = playerInventory.findIndexEmpty();
                                        }
                                        if (itemQty > 0) {
                                            cout << "Inventory penuh!" << endl;
                                        }
                                    } else if ( itrNonTool != nonToolContainer.end() ) { // Jika tipe item NonTool
                                        // Temukan semua slot yang berisi item ini
                                        int index = playerInventory.findIndex(&itrNonTool->second);
                                        while (itemQty > 0 && index != -1) {
                                            int remainingQty = MAX_CAP - playerInventory.getQuantity(index);
                                            if (remainingQty >= itemQty) {
                                                playerInventory.addQuantity(index, itemQty);
                                                itrNonTool->second.addQuantity(itemQty);
                                                itemQty = 0;
                                            } else {
                                                playerInventory.addQuantity(index, remainingQty);
                                                itrNonTool->second.addQuantity(remainingQty);
                                                itemQty -= remainingQty;
                                                index = playerInventory.findIndex(&itrNonTool->second);
                                            }
                                        } // itemQty == 0 atau sudah tidak ada yang bisa ditumpuk
                                        // Jika masih ada slot kosong
                                        index = playerInventory.findIndexEmpty();
                                        while (itemQty > 0 && index != -1) {
                                            int QtyToBeAdded;
                                            if (itemQty > MAX_CAP) {
                                                QtyToBeAdded = MAX_CAP;
                                                itemQty -= MAX_CAP;
                                            } else {
                                                QtyToBeAdded = itemQty;
                                                itemQty = 0;
                                            }
                                            playerInventory.addQuantity(index, QtyToBeAdded);
                                            playerInventory.setPtrItem(index, &itrNonTool->second);
                                            itrNonTool->second.addQuantity(QtyToBeAdded);
                                            index = playerInventory.findIndexEmpty();
                                        }
                                        // Jika sudah tidak ada slot kosong
                                        if (itemQty > 0) {
                                            cout << "Inventory penuh!" << endl;
                                        }
                                    }
                                    i = recipeCount;
                                    j = MAX_ROW-recipeContainer[i].getRow()+1;
                                    k = MAX_COL-recipeContainer[i].getCol()+1;
                                }
                            }
                        }
                    }
                }
            } else {
                for(itrTool = toolContainer.begin(); itrTool != toolContainer.end(); itrTool++){
                    int countTool = 0;
                    int totalDurability = 0;
                    for (int i = 0; i<MAX_ROW; i++){
                        for (int j = 0; j<MAX_COL; j++){
                            if (tableContent[i][j] != NULL){
                                if (tableInventory.getPtrItem(i*MAX_ROW+j)->getName() == itrTool->first){
                                    countTool++;
                                } else if (tableInventory.getPtrItem(i*MAX_ROW+j)->getName() != itrTool->first){
                                    countTool = -1;
                                    break;
                                }
                                
                            }
                        }
                    }
                    if (countTool == 2){
                        isCrafted = 1;
                        for (int i = 0; i<MAX_ROW; i++){
                            for (int j = 0; j<MAX_COL; j++){
                                if (tableContent[i][j] != NULL){
                                    if (tableInventory.getPtrItem(i*MAX_ROW+j)->getName() == itrTool->first){
                                        int posBeforeMove = tableInventory.countOccurence(itrTool->first, i*MAX_ROW+j) + playerInventory.countOccurence(itrTool->first) + 1;
                                        int durability = itrTool->second.getDurabilityAtPos(posBeforeMove);
                                        totalDurability += durability;
                                        tableInventory.addQuantity(i*MAX_ROW+j, -1);
                                        tableInventory.setPtrItem(i*MAX_ROW+j, NULL);
                                        itrTool->second.removeDurabilityAtPos(posBeforeMove);
                                    }
                                }
                            }
                        }
                        if (totalDurability > 10){
                            totalDurability = 10;
                        }
                        int index = playerInventory.findIndexEmpty();
                        int pos = playerInventory.findPosForGIVE(itrTool->first);
                        int itemQtyCraft = 1;
                        while (itemQtyCraft > 0 && index != -1) {
                            itemQtyCraft--;
                            playerInventory.addQuantity(index, 1); // Menambah quantity di slot
                            playerInventory.setPtrItem(index, &itrTool->second); // Menunjuk ke alamat item di container
                            itrTool->second.insertDurabilityAtPos(pos, totalDurability); // Durability awal = totalDurability sekaligus menambah quantity;
                            index = playerInventory.findIndexEmpty();
                        }
                        // Jika tidak ada slot kosong tersisa 
                        if (itemQtyCraft > 0) {
                            cout << "Inventory penuh!" << endl;
                        }
                        break;
                    }
                }
            }
            if (isCrafted == 1){
                cout << "item crafted" << endl;
            } else {
                cout << "no item can be crafted" << endl;
            }
        }
        else if (command == "EXIT") {
            char exit;
            cout << "To exit and export, type 'Y'" << endl;;
            cout << "To exit without export, ";
            cin >> exit;
        }
        else if (command == "HELP") {
            cout << "EXIT: " << endl;
            // TODO
        }
        // invalid command 
        else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
