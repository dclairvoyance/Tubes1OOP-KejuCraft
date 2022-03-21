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
    /*
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    for (string line; getline(itemConfigFile, line);) {
      cout << line << endl;
      // do something
    }

    // read recipes
    for (const auto &entry :
        filesystem::directory_iterator(configPath + "/recipe")) {
      cout << entry.path() << endl;
      // read from file and do something
    }

    // sample interaction
    string command;
    while (cin >> command) {
      if (command == "EXPORT") {
        string outputPath;
        cin >> outputPath;
        ofstream outputFile(outputPath);

        // hardcode for first test case
        outputFile << "21:10" << endl;
        outputFile << "6:1" << endl;
        for (int i = 2; i < 27; i++) {
          outputFile << "0:0" << endl;
        }

        cout << "Exported" << endl;
      } else if (command == "CRAFT") {
        cout << "TODO" << endl;
      } else if (command == "GIVE") {
        string itemName;
        int itemQty;
        cin >> itemName >> itemQty;
        cout << "TODO" << endl;
      } else if (command == "MOVE") {
        string slotSrc;
        int slotQty;
        string slotDest;
        // need to handle multiple destinations
        cin >> slotSrc >> slotQty >> slotDest;
        cout << "TODO" << endl;
      } else {
        // todo
        cout << "Invalid command" << endl;
      }
    }
    */

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

    // Membaca file recipe
    // for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
    //     cout << entry.path() << endl;
    // }

    // Mencetak seluruh isi map
    // cout << "NonTools: " << endl;
    // for (itrNonTool = nonToolContainer.begin(); itrNonTool!=nonToolContainer.end(); itrNonTool++) {
    //     cout << itrNonTool->first << endl;
    //     itrNonTool->second.print();
    //     cout << endl;
    // }

    // cout << "Tools: " << endl;
    // for (itrTool = toolContainer.begin(); itrTool!=toolContainer.end(); itrTool++) {
    //     cout << itrTool->first << endl;
    //     itrTool->second.print();
    //     cout << endl;
    // }

    // for (int i = 0; i<recipeCount; i++){
    //     recipeContainer[i].print();
    // }


    // BAGIAN III: Meng-handle Command
    string command;
    while (cin >> command) {
        // Command SHOW
        if (command == "SHOW") {
            // print craftingTable
            for (int i=0; i<MAX_ROW; i++) {
                for (int j=0; j<MAX_COL; j++) {
                    cout << "[" << tableInventory.getSlotIdByCoord(i, j) << " ";
                    if (!tableInventory.isSlotEmpty(i, j)) {
                        cout << tableInventory.getItemIdByCoord(i, j) << " ";
                        string itemName = tableInventory.getItemNameByCoord(i, j);
                        string slotId = tableInventory.getSlotIdByCoord(i, j);
                        itrTool = toolContainer.find(itemName);
                        itrNonTool = nonToolContainer.find(itemName);
                        if (itrTool != toolContainer.end()) { // Jika tool, cetak durability
                            int pos = tableInventory.findPosForTool(playerInventory, i, j);
                            cout << itrTool->second.getDurabilityAtPos(pos);
                        } else { // Jika nontool, cetak quantity
                            cout << tableInventory.getQuantityByCoord(i, j);
                        }
                    } else {
                        cout << tableInventory.getQuantityByCoord(i, j);
                    }
                    cout << "] ";
                }
                cout << endl;
            }

            // print inventory
            for (int i=0; i<MAX_SLOT; i++) {
                cout << "[";
                cout << playerInventory.getSlotIdAtIndex(i) << " ";
                printBetter(i);
                // ada item pada slot
                if (playerInventory.getPtrItemAtIndex(i) != NULL) {
                    printBetter(playerInventory.getItemIdAtIndex(i));
                    cout << playerInventory.getItemIdAtIndex(i) << " ";
                    string itemName = playerInventory.getItemNameAtIndex(i);
                    string slotId = playerInventory.getSlotIdAtIndex(i);
                    int pos = playerInventory.findPosForMOVE(itemName, slotId);
                    itrTool = toolContainer.find(itemName);
                    itrNonTool = nonToolContainer.find(itemName);
                    if (itrTool != toolContainer.end()) { // Jika tool, cetak durability
                        printBetter(itrTool->second.getDurabilityAtPos(pos));
                        cout << itrTool->second.getDurabilityAtPos(pos);
                    } else { // Jika nontool, cetak quantity
                        printBetter(playerInventory.getQuantityAtIndex(i));
                        cout << playerInventory.getQuantityAtIndex(i);
                    }
                } 
                // tidak ada item pada slot
                else {
                    printBetter(playerInventory.getItemIdAtIndex(i));
                    cout << playerInventory.getItemIdAtIndex(i) << " ";
                    printBetter(playerInventory.getQuantityAtIndex(i));
                    cout << playerInventory.getQuantityAtIndex(i);
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
                    playerInventory.addQuantityAtIndex(index, 1); // Menambah quantity di slot
                    playerInventory.setPtrItemAtIndex(index, &itrTool->second); // Menunjuk ke alamat item di container
                    itrTool->second.addQuantity(1); // Menambah quantity item di container
                    itrTool->second.insertDurabilityAtPos(pos, 10); // Durability awal = 10;
                    index = playerInventory.findIndexEmpty();
                }
                // Jika tidak ada slot kosong tersisa 
                if (itemQty > 0) {
                    cout << "Inventory penuh!" << endl;
                }
            } else if ( itrNonTool != nonToolContainer.end() ) { // Jika tipe item NonTool
                // Temukan semua slot yang berisi item ini
                int index = playerInventory.findIndexItem(&itrNonTool->second);
                while (itemQty > 0 && index != -1) {
                    int remainingQty = MAX_CAP - playerInventory.getQuantityAtIndex(index);
                    if (remainingQty >= itemQty) {
                        playerInventory.addQuantityAtIndex(index, itemQty);
                        itrNonTool->second.addQuantity(itemQty);
                        itemQty = 0;
                    } else {
                        playerInventory.addQuantityAtIndex(index, remainingQty);
                        itrNonTool->second.addQuantity(remainingQty);
                        itemQty -= remainingQty;
                        index = playerInventory.findIndexItem(&itrNonTool->second);
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
                    playerInventory.addQuantityAtIndex(index, QtyToBeAdded);
                    playerInventory.setPtrItemAtIndex(index, &itrNonTool->second);
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
            int index = playerInventory.findIndexBySlotId(inventorySlotId);
            string itemName = playerInventory.getItemNameAtIndex(index);
            itrTool = toolContainer.find(itemName);
            itrNonTool = nonToolContainer.find(itemName);
            if (playerInventory.getQuantityAtIndex(index) < itemQty) {
                cout << "Item tidak mencukupi" << endl;
            } else { // Jika item cukup untuk dihapus
                // Mengurangi quantity di container
                if (itrTool != toolContainer.end()) {
                    itrTool->second.addQuantity(-itemQty);
                    int pos = playerInventory.findPosForMOVE(itemName, inventorySlotId);
                    itrTool->second.removeDurabilityAtPos(pos); // Menghapus durability
                } else {
                    itrNonTool->second.addQuantity(-itemQty);
                }
                // Mengurangi item di slot
                playerInventory.addQuantityAtIndex(index, -itemQty);
                if (playerInventory.getQuantityAtIndex(index) == 0) { // Jika habis, hapus pointer item
                    playerInventory.setPtrItemAtIndex(index, NULL);
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
                    int indexSrc = playerInventory.findIndexBySlotId(slotIdSrc);
                    int indexDest = playerInventory.findIndexBySlotId(slotIdDest);
                    itemQty = playerInventory.getQuantityAtIndex(indexSrc);
                    int itemQtyDest = playerInventory.getQuantityAtIndex(indexDest);
                    if (itemQtyDest == 0) { // Jika ingin dipindahkan ke slot kosong
                        string itemNameSrc = playerInventory.getItemNameAtIndex(indexSrc);
                        itrTool = toolContainer.find(itemNameSrc);
                        itrNonTool = nonToolContainer.find(itemNameSrc);
                        if (itrTool != toolContainer.end()) {
                            int posBeforeMove = playerInventory.findPosForMOVE(itemNameSrc, slotIdSrc);
                            int posAfterMove = playerInventory.findPosAfterMOVE(itemNameSrc, slotIdSrc, slotIdDest);
                            int durability = itrTool->second.getDurabilityAtPos(posBeforeMove);
                            itrTool->second.removeDurabilityAtPos(posBeforeMove);
                            itrTool->second.insertDurabilityAtPos(posAfterMove, durability);
                        }
                        playerInventory.setQuantityAtIndex(indexDest, itemQty);
                        playerInventory.setPtrItemAtIndex(indexDest, playerInventory.getPtrItemAtIndex(indexSrc));
                        playerInventory.setQuantityAtIndex(indexSrc, 0);
                        playerInventory.setPtrItemAtIndex(indexSrc, NULL);
                    } else {
                        string itemNameDest = playerInventory.getItemNameAtIndex(indexDest);
                        itrTool = toolContainer.find(itemNameDest);
                        itrNonTool = nonToolContainer.find(itemNameDest);
                        if (itrTool != toolContainer.end()) { // Jika item Tool yang akan ditumpuk
                            cout << "Item Tool tidak dapat ditumpuk!" << endl;
                        } else { // Jika item NonTool yang akan ditumpuk
                            if (playerInventory.getItemIdAtIndex(indexSrc) != playerInventory.getItemIdAtIndex(indexDest)) { // Jika item berbeda
                                cout << "Item berbeda tidak dapat ditumpuk!" << endl;
                            } else {
                                int totalQtyDest = (itemQty+itemQtyDest) > MAX_CAP ? MAX_CAP : itemQty+itemQtyDest;
                                int totalQtySrc = (itemQty+itemQtyDest) > MAX_CAP ? itemQty+itemQtyDest-MAX_CAP : 0;
                                playerInventory.setQuantityAtIndex(indexDest, totalQtyDest);
                                playerInventory.setQuantityAtIndex(indexSrc, totalQtySrc);
                                if (playerInventory.getQuantityAtIndex(indexSrc) == 0) { // Jika kosong setelah pemindahan
                                    playerInventory.setPtrItemAtIndex(indexSrc, NULL);
                                }
                            }
                        }
                    }
                } else if (slotIdDest[0] == 'C') { // Jika tujuannya ke slotCrafting
                    int indexSrc = playerInventory.findIndexBySlotId(slotIdSrc);
                    int indexDest = tableInventory.findIndexBySlotId(slotIdDest);
                    itemQty = playerInventory.getQuantityAtIndex(indexSrc);
                    int itemQtyDest = tableInventory.getQuantityAtIndex(indexDest);
                    if (itemQtyDest == 0) { // Jika ingin dipindahkan ke slot kosong
                        string itemNameSrc = playerInventory.getItemNameAtIndex(indexSrc);
                        itrTool = toolContainer.find(itemNameSrc);
                        itrNonTool = nonToolContainer.find(itemNameSrc);
                        if (itrTool != toolContainer.end()) {
                            int posBeforeMove = playerInventory.findPosForMOVE(itemNameSrc, slotIdSrc);
                            int posAfterMove = 0;
                            cout << posAfterMove << endl;
                            int durability = itrTool->second.getDurabilityAtPos(posBeforeMove);
                            cout << "yes" << endl;
                            itrTool->second.removeDurabilityAtPos(posBeforeMove);
                            itrTool->second.insertDurabilityAtPos(posAfterMove, durability);
                            cout << "yes" << endl;
                        }
                        tableInventory.setQuantityAtIndex(indexDest, itemQty);
                        tableInventory.setPtrItemAtIndex(indexDest, playerInventory.getPtrItemAtIndex(indexSrc));
                        playerInventory.setQuantityAtIndex(indexSrc, 0);
                        playerInventory.setPtrItemAtIndex(indexSrc, NULL);
                    
                    } else {
                        string itemNameDest = tableInventory.getItemNameAtIndex(indexDest);
                        itrTool = toolContainer.find(itemNameDest);
                        itrNonTool = nonToolContainer.find(itemNameDest);
                        if (itrTool != toolContainer.end()) { // Jika item Tool yang akan ditumpuk
                            cout << "Item Tool tidak dapat ditumpuk!" << endl;
                        } else { // Jika item NonTool yang akan ditumpuk
                            if (playerInventory.getItemIdAtIndex(indexSrc) != tableInventory.getItemIdAtIndex(indexDest)) { // Jika item berbeda
                                cout << "Item berbeda tidak dapat ditumpuk!" << endl;
                            } else {
                                int totalQtyDest = (itemQty+itemQtyDest) > MAX_CAP ? MAX_CAP : itemQty+itemQtyDest;
                                int totalQtySrc = (itemQty+itemQtyDest) > MAX_CAP ? itemQty+itemQtyDest-MAX_CAP : 0;
                                tableInventory.setQuantityAtIndex(indexDest, totalQtyDest);
                                playerInventory.setQuantityAtIndex(indexSrc, totalQtySrc);
                                if (playerInventory.getQuantityAtIndex(indexSrc) == 0) { // Jika kosong setelah pemindahan
                                    playerInventory.setPtrItemAtIndex(indexSrc, NULL);
                                }
                            }
                        }
                    }
                } else {
                    cout << "Id slot tidak valid!" << endl;
                }
            } else if (slotIdSrc[0] == 'C') { // Jika sumbernya dari slotCrafting
                // TODO
            } else {
                cout << "Id slot tidak valid!" << endl;
            }
        } 
        // Command USE
        else if (command == "USE") {
            string inventorySlotId;
            cin >> inventorySlotId;
            int index = playerInventory.findIndexBySlotId(inventorySlotId);
            if (playerInventory.getPtrItemAtIndex(index) == NULL) {
                cout << "Tidak ada item di slot!" << endl;
            } else {
                string itemName = playerInventory.getItemNameAtIndex(index);
                itrTool = toolContainer.find(itemName);
                itrNonTool = nonToolContainer.find(itemName);
                if (itrTool != toolContainer.end()) {
                    int pos = playerInventory.findPosForMOVE(itemName, inventorySlotId);
                    itrTool->second.decrementDurabilityAtPos(pos);
                    if (itrTool->second.getDurabilityAtPos(pos) == 0) { // Jika durability habis
                        itrTool->second.removeDurabilityAtPos(pos);
                        playerInventory.addQuantityAtIndex(index, -1); // kurangi quantity di slot
                        playerInventory.setPtrItemAtIndex(index, NULL);
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
                itemName = playerInventory.getItemNameAtIndex(i);
                idItem = playerInventory.getItemIdAtIndex(i);
                itrTool = toolContainer.find(itemName);
                itrNonTool = nonToolContainer.find(itemName);
                if (itrTool != toolContainer.end()) {
                    string slotId = playerInventory.getSlotIdAtIndex(i);
                    int pos = playerInventory.findPosForMOVE(itemName, slotId);
                    durability = itrTool->second.getDurabilityAtPos(pos);
                    outText = to_string(idItem) + ':' + to_string(durability);
                } else {
                    quantity = playerInventory.getQuantityAtIndex(i);
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
                    Item* slotContent = tableInventory.getSlot(i*MAX_ROW + j).getPointerItem();
                    tableContent[i][j] = slotContent;
                }
            }

            int maxWidth = 0;
            for (int i = 0; i<MAX_ROW; i++){
                int tableWidth = 0;
                for (int j = 0; j<MAX_COL; j++){
                    if (tableContent[i][j] != NULL){
                        tableWidth++;
                    }
                }
                if (tableWidth > maxWidth){
                    maxWidth = tableWidth;
                }
            }

            int maxHeight = 0;
            for (int j = 0; j<MAX_COL; j++){
                int tableHeight = 0;
                for (int i = 0; i<MAX_ROW; i++){
                    if (tableContent[i][j] != NULL){
                        tableHeight++;
                    }
                }
                if (tableHeight > maxHeight){
                    maxHeight = tableHeight;
                }
            }

            
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
                                    }

                                    else if (tableResep[m][n] != tableContent[j+m][k+n]->getName() && tableResep[m][n] != tableContent[j+m][k+n]->getType()){
                                        isSame = 0;
                                        cout << tableContent[j+m][k+n]->getName() << endl;
                                        cout << tableContent[j+m][k+n]->getType() << endl;
                                    }
                                }
                            }

                            if (isSame == 1){
                                isCrafted = 1;
                                for (int x = 0; x<MAX_ROW; x++){
                                    for (int y = 0; y<MAX_COL; y++){
                                        if (tableInventory.getSlot(x*MAX_ROW + y).getPointerItem() != NULL){
                                            tableInventory.getSlot(x*MAX_ROW + y).getPointerItem()->addQuantity(-1);
                                            cout << "yes" << endl;
                                            tableInventory.setQuantityAtIndex(x*MAX_ROW+y, 0);
                                            tableInventory.setPtrItemAtIndex(x*MAX_ROW+y, NULL);
                                            cout << "yes" << endl;
                                        }
                                    }
                                }
                                cout << "yes" << endl;

                                string itemName = recipeContainer[i].getOutput().getName();
                                int itemQty = recipeContainer[i].getQuantity();
                                itrTool = toolContainer.find(itemName);
                                itrNonTool = nonToolContainer.find(itemName);

                                if (itrTool != toolContainer.end()) { // Jika tipe item Tool
                                    int index = playerInventory.findIndexEmpty();
                                    int pos = playerInventory.findPosForGIVE(itemName);
                                    while (itemQty > 0 && index != -1) {
                                        itemQty--;
                                        playerInventory.addQuantityAtIndex(index, 1); // Menambah quantity di slot
                                        playerInventory.setPtrItemAtIndex(index, &itrTool->second); // Menunjuk ke alamat item di container
                                        itrTool->second.addQuantity(1); // Menambah quantity item di container
                                        itrTool->second.insertDurabilityAtPos(pos, 10); // Durability awal = 10;
                                        index = playerInventory.findIndexEmpty();
                                    }
                                    if (itemQty > 0) {
                                        cout << "Inventory penuh!" << endl;
                                    }

                                } else if ( itrNonTool != nonToolContainer.end() ) { // Jika tipe item NonTool
                                    // Temukan semua slot yang berisi item ini
                                    int index = playerInventory.findIndexItem(&itrNonTool->second);
                                    while (itemQty > 0 && index != -1) {
                                        int remainingQty = MAX_CAP - playerInventory.getQuantityAtIndex(index);
                                        if (remainingQty >= itemQty) {
                                            playerInventory.addQuantityAtIndex(index, itemQty);
                                            itrNonTool->second.addQuantity(itemQty);
                                            itemQty = 0;
                                        } else {
                                            playerInventory.addQuantityAtIndex(index, remainingQty);
                                            itrNonTool->second.addQuantity(remainingQty);
                                            itemQty -= remainingQty;
                                            index = playerInventory.findIndexItem(&itrNonTool->second);
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
                                        playerInventory.addQuantityAtIndex(index, QtyToBeAdded);
                                        playerInventory.setPtrItemAtIndex(index, &itrNonTool->second);
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
