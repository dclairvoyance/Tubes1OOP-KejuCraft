#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include "Item.h"
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

    ifstream indata;
    string intext, filename;
    map<string, Tool> toolContainer;
    map<string, NonTool> nonToolContainer;

    // Input nama file
    cout << "Enter filename: ";
    cin >> filename;

    // Membuka file
    indata.open(filename.c_str());
    if (!indata) {
        cerr << "Error: File could not be opened" << endl;
        exit(1);
    }

    // Pisahkan item tool dan nontool
    while (getline(indata, intext)) {
        stringstream ss(intext);
        string name, type, isTool;
        int id;
        ss >> id;
        ss >> name;
        ss >> type;
        ss >> isTool;
        if (isTool == "TOOL") {
            Tool item(id, name, type, 0, 10);
            toolContainer.insert(pair<string, Tool> (item.getName(), item));
        } else {
            NonTool item(id, name, type, 0);
            nonToolContainer.insert(pair<string, NonTool> (item.getName(), item));
        }
    }

    // Pembacaan file selesai
    indata.close();
    cout << "EOF reached.." << endl;

    // Membuat iterator
    map<string, Tool>::iterator itrTool;
    map<string, NonTool>::iterator itrNonTool;

    // Mencetak seluruh isi map
    for (itrNonTool = nonToolContainer.begin(); itrNonTool!=nonToolContainer.end(); itrNonTool++) {
        cout << itrNonTool->first << endl;
        itrNonTool->second.print();
        cout << endl;
    }

    cout << "Tools: " << endl;
    for (itrTool = toolContainer.begin(); itrTool!=toolContainer.end(); itrTool++) {
        cout << itrTool->first << endl;
        itrTool->second.print();
        cout << endl;
    }

    return 0;
}