#pragma once
#include "hashTable.hpp"
#include "product.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using std::string;
using std::getline;

class Inventory{
public:
    ArrayList<string> parseCSVFiles(string line);
    void parse(ifstream& file, HashTable<string, Product>& table, HashTable<string, ArrayList<Product>>& categoryTable);
    void find(string inventoryID, HashTable<string, Product>& table);
    void listInventory(string category, HashTable<string, ArrayList<Product>>& categoryTable);
};