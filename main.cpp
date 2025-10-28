/*
Programmer: Keila Holcombe
Assignment: PA3
Class: CPT223 Fall 2025	
Date: 10-23-2025
Description:    
        Save the data given by the .csv file into a HashTree. I created two trees. One with the uniqID as the key and one as the category
        as the key. There will be two main functions, find <inventoryid> and listInventory <category_string>. The find function will accepts
        a string of inventoryid where it will find the product with a uniqID that matches the id that was inserted by the user and prints all
        the information about that product. The listInventory function will accepts a string of category_string where the user will enter a 
        category and the function will print the uniqid and product name for all the products that is under that category.
*/

#include "inventory.hpp"
#include "hashTable.hpp"
#include "product.hpp"
#include "test.hpp"
#include "arrayList.hpp"

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

// This is the function to access the test function
void test()
{
    string line;
    Test tests;

    // These are for my testing functions
    HashTable<string, string> testTable(101);
    HashTable<string, Product> testNormalTable(101);
    HashTable<string, ArrayList<Product>> testCategoryTable(101);
        cout << "____________________________________________________________________________________________" << endl;

    cout << "Parsing already happened\n" << endl;
    tests.testParse(testNormalTable, testCategoryTable);

    cout << "Supported list of commands: " << endl;
    cout << " 1. testInsert - Tests if the insertion is working (Recommend doing the insertion before doing the other operation since doing other function in a empty table is pointless)\n" << endl;
    //cout << " 2. testParse - Tests if parsing works by using a smaller csv file\n" << endl;
    cout << " 3. testFind - Tests if the listInventory function is working\n" << endl;
    cout << " 4. testListInventory - Tests if the listInventory function is working\n" << endl;
    cout << " 5. exit - Exit from the test menu" << endl;

    // DIrect the user depending on what funciton they choose.
    // loops until they quit
    while (getline(cin, line) && line != "exit")
        {
        if (line == "testInsert")
        {
            tests.testInsert(testTable);
        }else if (line == "testFind")
        {
            tests.testFind(testNormalTable);
        }else if (line == "testListInventory")
        {
            tests.testListInventory(testCategoryTable);
        }
        cout << "Supported list of commands: " << endl;
        cout << "____________________________________________________________________________________________" << endl;
        cout << " 1. testInsert - Tests if the insertion is working (Recommend doing the insertion before doing the other operation since doing other function in a empty table is pointless)\n" << endl;
        //cout << " 2. testParse - Tests if parsing works by using a smaller csv file\n" << endl;
        cout << " 3. testFind - Tests if the listInventory function is working\n" << endl;
        cout << " 4. testListInventory - Tests if the listInventory function is working\n" << endl;
        cout << " 5. exit - Exit from the test menu" << endl;
    }
    return;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0) ||
           (line == ":test");
}

void evalCommand(string line, HashTable<string, Product>& table, HashTable<string, ArrayList<Product>>& categoryTable){
    Inventory inventory;
    if (line == ":help")
    {
        printHelp();
    }else if (line == ":test")
    {
        test(); 
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // find the inventoryid that the user entered after "find "
        string inventoryid = line.substr(4);
        // Check if there are extra spaces infront of the inventoryid, if there are, erase it
        while(!inventoryid.empty() && inventoryid[0] == ' '){
            inventoryid = inventoryid.substr(1);
        }
        // Check if there are extra spaces at the end
        while(!inventoryid.empty() && inventoryid[inventoryid.size()-1] == ' '){
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
            cout << "Searching products with empty category\n" << endl;
            inventory.listInventory("", categoryTable);
        }else{
            inventory.listInventory(category_string, categoryTable);
        }
    }
}

void bootStrap(ifstream &file, HashTable<string, Product>& table, HashTable<string, ArrayList<Product>>& categoryTable){
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter \n\t:quit - exit.\n\t:help - list supported commands.\n\t:test - goes to test menu with available test commands (only able to do the test commands here)." << endl;
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
    HashTable<string, ArrayList<Product>> categoryTable(101);

    
    
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

    // exit from file 
    file.close();
    return 0;
}
