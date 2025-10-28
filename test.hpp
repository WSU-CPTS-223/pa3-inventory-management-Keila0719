#include "hashTable.hpp"
#include "inventory.hpp"

class Test{
public:
    void testInsert(HashTable<string, string>& testTable);
    void testParse(HashTable<string, Product> &testNormalTable, HashTable<string, ArrayList<Product>>& testCategoryTable);
    void testFind(HashTable<string, Product> &testNormalTable);
    void testListInventory(HashTable<string, ArrayList<Product>>& testCategoryTable);
};