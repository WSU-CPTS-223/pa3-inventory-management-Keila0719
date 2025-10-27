#pragma once
#include "hashTable.hpp"
#include "product.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::getline;
using std::vector;

class Inventory{
public:
    vector<string> parseCSVFiles(string line);
    void parse(ifstream& file, HashTable<string, Product>& table, HashTable<string, vector<Product>>& categoryTable);
    void find(string inventoryID, HashTable<string, Product>& table);
    void listInventory(string category, HashTable<string, vector<Product>>& categoryTable);
};