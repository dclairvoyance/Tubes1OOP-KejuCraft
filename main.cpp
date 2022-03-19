#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <map>
#include "Item.h"
#include "Inventory.h"
#include "Slot.h"
using namespace std;

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

    // Container untuk tool dan nontool
    map<string, Tool> toolContainer;
    map<string, NonTool> nonToolContainer;

    // Inventory pemain
    Inventory playerInventory;

    // Path ke folder config
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    // Membaca file item config
    ifstream itemConfigFile(itemConfigPath);
    string intext;

    // Pisahkan item tool dan nontool
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

    // Pembacaan file item config selesai
    itemConfigFile.close();
    cout << "EOF reached.." << endl;

    // Membaca file recipe
    // for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
    //     cout << entry.path() << endl;
    // }

    // Membuat iterator
    map<string, Tool>::iterator itrTool;
    map<string, NonTool>::iterator itrNonTool;

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

    string command;
    while (cin >> command) {
        if (command == "SHOW") {
            for (int i=0; i<MAX_SLOT; i++) {
                // print inventory
                cout << "[" << playerInventory.getSlotIdAtIndex(i) << " ";
                if (playerInventory.getPtrItemAtIndex(i) != NULL) {
                    cout << playerInventory.getItemIdAtIndex(i) << " ";
                    string itemName = playerInventory.getItemNameAtIndex(i);
                    string slotId = playerInventory.getSlotIdAtIndex(i);
                    int pos = playerInventory.findPosForMOVE(itemName, slotId);
                    itrTool = toolContainer.find(itemName);
                    itrNonTool = nonToolContainer.find(itemName);
                    if (itrTool != toolContainer.end()) { // Jika tool, cetak durability
                        cout << itrTool->second.getDurabilityAtPos(pos);
                    } else { // Jika nontool, cetak quantity
                        cout << playerInventory.getQuantityAtIndex(i);
                    }
                } else {
                    cout << playerInventory.getQuantityAtIndex(i);
                }
                cout << "] ";

                if (i%9 == 8) {
                    cout << endl;
                }
            }
        } else if (command == "GIVE") {
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
            } else { // Jika tipe item NonTool
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
        } else if (command == "DISCARD") {
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
        } else if (command == "MOVE") {
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
                            int posAfterMove = playerInventory.findPosForMOVE(itemNameSrc, slotIdDest) - 1;
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
                                int totalQtySrc = (itemQty+itemQtyDest) > MAX_CAP ? totalQtyDest-MAX_CAP : 0;
                                playerInventory.setQuantityAtIndex(indexDest, totalQtyDest);
                                playerInventory.setQuantityAtIndex(indexSrc, totalQtySrc);
                                if (playerInventory.getQuantityAtIndex(indexSrc) == 0) { // Jika kosong setelah pemindahan
                                    playerInventory.setPtrItemAtIndex(indexSrc, NULL);
                                }
                            }
                        }
                    }
                } else if (slotIdDest[0] == 'C') { // Jika tujuannya ke slotCrafting
                    // TODO
                } else {
                    cout << "Id slot tidak valid!" << endl;
                }
            } else if (slotIdSrc[0] == 'C') { // Jika sumbernya dari slotCrafting
                // TODO
            } else {
                cout << "Id slot tidak valid!" << endl;
            }
        } else if (command == "USE") {
            string inventorySlotId;
            cin >> inventorySlotId;
            int index = playerInventory.findIndexBySlotId(inventorySlotId);
            string itemName = playerInventory.getItemNameAtIndex(index);
            itrTool = toolContainer.find(itemName);
            itrNonTool = nonToolContainer.find(itemName);
            if (itrTool != toolContainer.end()) {
                int pos = playerInventory.findPosForMOVE(itemName, inventorySlotId);
                itrTool->second.decrementDurabilityAtPos(pos);
                if (itrTool->second.getDurabilityAtPos(pos) == 0) { // Jika durability habis
                    itrTool->second.removeDurabilityAtPos(pos);
                    itrTool->second.addQuantity(-1); // kurangi quantity di container
                    playerInventory.addQuantityAtIndex(index, -1); // kurangi quantity di slot
                }
            } else {
                cout << "Item NonTool tidak dapat digunakan!" << endl;
            }
        } else if (command == "EXPORT") {
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
        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}