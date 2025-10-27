#include "inventory.hpp"
#include "hashTable.hpp"
#include "product.hpp"

#include <iostream>
#include <string>

using namespace std;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

void printTest()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. insert - Tests if " << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, HashTable<string, Product>& table, HashTable<string, vector<Product>>& categoryTable)
{
    Inventory inventory;
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // find the inventoryid that the user entered after "find "
        string inventoryid = line.substr(4);
        // Check if there are extra spaces infront of the inventoryid, if there are, erase it
        while(inventoryid[0] == ' '){
            inventoryid = inventoryid.substr(1);
        }
        // Check if there are extra spaces at the end
        while(inventoryid[inventoryid.size()-1] == ' '){
			inventoryid = inventoryid.substr(0, inventoryid.size() - 1);
		}
        // Check if the string is empty or not
        if(inventoryid.empty()){
            cout << "find <inventoryid>: your inventoryid is empty. Please type the id you want to search after find\n"<< endl;
        }else{
            inventory.find(inventoryid, table);
        }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory ") == 0)
    {
        // find the category that the user entered after "listInventory "
        string category_string = line.substr(13);
        // Check if there are extra spaces infront of the category word, if there are, erase it
        while(category_string[0] == ' '){
            category_string = category_string.substr(1);
        }
        // Check if there is extra space at the end
        while(category_string[category_string.size()-1] == ' '){
				category_string = category_string.substr(0, category_string.size() - 1);
		}
        // Check if the string is empty or not
        if(category_string.empty()){
            cout << "listInventory <category_string>: your category_string is empty. Please type the id you want to search after listInventory\n"<< endl;
        }else{
            inventory.listInventory(category_string, categoryTable);
        }
    }
}

void bootStrap(ifstream &file, HashTable<string, Product>& table, HashTable<string, vector<Product>>& categoryTable)
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices

    

    // Parse data into the two tables
    Inventory inventory;
    inventory.parse(file, table, categoryTable);
}

int main(int argc, char const *argv[])
{
    // Create two hashTables that will be used in this program. initial capacity set as 101
    HashTable<string, Product> table(101);
    HashTable<string, vector<Product>> categoryTable(101);

    // Open the csv file
    ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");

    // If the file didn't open, we will let the user know and exit
    if(!file.is_open()){
        cout << "File failed to open" << endl;
        return 0;
    }

    string line;
    bootStrap(file, table, categoryTable);

    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, table, categoryTable);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "_____________________________________________________________________________\n" << endl;
        cout << " Enter:\n\t:quit - exit. \n\t:help - list supported commands.\n\t:test - list test operations" << endl;
        cout << "\n> ";
    }
    return 0;
}
