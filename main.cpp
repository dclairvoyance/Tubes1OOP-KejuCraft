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
            Tool item(id, name, type, 0, 10); // Durability awal = 10
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
        if (command == "GIVE") {
            string itemName;
            int itemQty;
            cin >> itemName >> itemQty;
            itrTool = toolContainer.find(itemName);
            itrNonTool = nonToolContainer.find(itemName);
            if (itrTool != toolContainer.end()) { // Jika tipe item Tool
                int countEmpty = playerInventory.countSlotEmpty();
                if (countEmpty < itemQty) {
                    cout << "Inventory penuh!" << endl;
                } else {
                    itrTool->second.addQuantity(itemQty); // Menambah quantity item di container
                    for (int i=0; i<itemQty; i++) {
                        int index = playerInventory.findIndexEmpty();
                        playerInventory.addQuantityAtIndex(index, 1); // Menambah quantity di slot
                        playerInventory.setPtrItemAtIndex(index, &itrTool->second); // Menunjuk ke alamat item di container
                    }
                }
            } else { // Jika tipe item NonTool
                // Temukan semua slot yang berisi item ini
                int index = playerInventory.findIndexItem(&itrNonTool->second);
                while (itemQty > 0 && index != -1) {
                    int remainingQty = 64 - playerInventory.getQuantityAtIndex(index);
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
                    if (itemQty > 64) {
                        QtyToBeAdded = 64;
                        itemQty -= 64;
                    } else {
                        QtyToBeAdded = itemQty;
                        itemQty = 0;
                    }
                    playerInventory.addQuantityAtIndex(index, QtyToBeAdded);
                    playerInventory.setPtrItemAtIndex(index, &itrNonTool->second);
                    itrNonTool->second.addQuantity(QtyToBeAdded);
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
                playerInventory.addQuantityAtIndex(index, -itemQty); // Mengurangi item di slot
                if (playerInventory.getQuantityAtIndex(index) == 0) { // Jika habis, hapus pointer item
                    playerInventory.setPtrItemAtIndex(index, NULL);
                }
                // Mengurangi quantity di container
                if (itrTool != toolContainer.end()) {
                    itrTool->second.addQuantity(-itemQty);
                } else {
                    itrNonTool->second.addQuantity(-itemQty);
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
                        playerInventory.setQuantityAtIndex(indexDest, itemQty);
                        playerInventory.setPtrItemAtIndex(indexDest, playerInventory.getPtrItemAtIndex(indexSrc));
                        playerInventory.setQuantityAtIndex(indexSrc, 0);
                        playerInventory.setPtrItemAtIndex(indexSrc, NULL);
                    } else {
                        string itemNameDest = playerInventory.getItemNameAtIndex(indexDest);
                        itrTool = toolContainer.find(itemNameDest);
                        itrNonTool = nonToolContainer.find(itemNameDest);
                        if (itrTool != toolContainer.end()) {
                            cout << "Item Tool tidak dapat ditumpuk!" << endl;
                        } else {
                            int totalQtyDest = (itemQty+itemQtyDest) > 64 ? 64 : itemQty+itemQtyDest;
                            int totalQtySrc = (itemQty+itemQtyDest) > 64 ? totalQtyDest-64 : 0;
                            playerInventory.setQuantityAtIndex(indexDest, totalQtyDest);
                            playerInventory.setQuantityAtIndex(indexSrc, totalQtySrc);
                            if (playerInventory.getQuantityAtIndex(indexSrc) == 0) { // Jika kosong setelah pemindahan
                                playerInventory.setPtrItemAtIndex(indexSrc, NULL);
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
        } else {
            playerInventory.print();
        }
    }

    return 0;
}