#include "test.hpp"
using std::cout;
using std::endl;

// This is used to test the insert function with more simple information
void Test::testInsert(HashTable<string, string> &testTable)
{
    
    cout<<"TESTING INSERTION\n[ To make it simple, I'm using HashTable<string, string> ]\n"<<endl;
    // Insert some in testTable
    testTable.insert("red", "1");
    testTable.insert("red", "0");
    testTable.insert("blue", "2");
    testTable.insert("green", "3");
    testTable.insert("yellow", "4");
    testTable.insert("brown", "5");
    testTable.insert("purple", "6");
    testTable.insert("pink", "7");
    testTable.insert("black", "8");
    testTable.insert("white", "9");
    testTable.insert("orange", "10");

    // Lets see if it actually inserted properly by printing them
    for(int i = 0; i < testTable.getCapacity(); i++){
        HashNode<string,string>* current = testTable.getBucket(i);
        cout << "" << i << ": ";
        //check if it's empty or not
        if(!current){
            cout<< "empty"<<endl;
        }else{
            cout<< "" << current->key<< ", " << current->value<<endl;
        }
    }
}

// This is used to test if parse function works. we are using a smaller data to see if it works
void Test::testParse(HashTable<string, Product> &testNormalTable, HashTable<string, ArrayList<Product>>& testCategoryTable)
{
    cout<< "TESTING PARSING\nSince the actual data is hugem I made a sample .csv file with the copy of the first 10 data from the actual csv file.\nI will going to test if parsing is working by using that file." <<endl;
    // Open the csv file
    ifstream file("test_marketing_sample.csv");

    // If the file didn't open, we will let the user know and exit
    if(!file.is_open()){
        cout << "File failed to open" << endl;
        return;
    }

    // We will parse the test_marketing_sample.csv file and insert information into testNormalTable and testCategoryTable
    Inventory inventory;
    inventory.parse(file, testNormalTable, testCategoryTable);

    // Close file after parsing
    file.close();

}

// This is used to test if the find function works and using a smaller hashtable
void Test::testFind(HashTable<string, Product> &testNormalTable)
{
    cout<< "TESTING FIND <INVENTORYID>\n I will be using testNormalTable to do this operation." << endl;
    Inventory inventory;

    string find1 = "e04b990e95bf73bbe6a3fa09785d7cd0";
    string find2 = "bc178f33a04dbccefa95b165f8b56830";
    string find3 = "a";
    // Testing something that exist in the file
    inventory.find(find1, testNormalTable);
    inventory.find(find2, testNormalTable);
    // Testing something that does not exist in the file
    inventory.find(find3, testNormalTable);
}

// This is used to test if the listInventory function works and using a smaller hashtable
void Test::testListInventory(HashTable<string, ArrayList<Product>>& testCategoryTable)
{
    cout<< "TESTING LISTINVENTORY <CATEGORY_STRING>\n I will be using testNormalTable to do this operation." << endl;
    Inventory inventory;
    string find1 = "Toys & Games";
    string find2 = "Model Kits";
    string find3 = "a";
    string find4 = "";
    // Testing a category that exist in the file
    inventory.listInventory(find1, testCategoryTable);
    inventory.listInventory(find2, testCategoryTable);
    // Testing something that does not exist in the file
    inventory.listInventory(find3, testCategoryTable); 
    // Testing with nothing in it since some products doesn't have a category
    inventory.listInventory(find4, testCategoryTable);
} 
