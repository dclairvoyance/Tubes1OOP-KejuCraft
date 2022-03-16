#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include "Item.h"
using namespace std;

int main() {
    ifstream indata;
    string intext, filename;
    map<int, Tool> toolContainer;
    map<int, NonTool> nonToolContainer;

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
            toolContainer.insert(pair<int, Tool> (item.getId(), item));
        } else {
            NonTool item(id, name, type, 0);
            nonToolContainer.insert(pair<int, NonTool> (item.getId(), item));
        }
    }

    // Pembacaan file selesai
    indata.close();
    cout << "EOF reached.." << endl;

    // Membuat iterator
    map<int, Tool>::iterator itrTool;
    map<int, NonTool>::iterator itrNonTool;

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