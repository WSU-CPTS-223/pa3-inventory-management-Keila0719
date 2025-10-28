[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA4 Skeleton Code
We expect a fully functioning command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.



-------------------------------------------------------------------------------------------------------------------------

How to run the code:
        1.  Open WSL: If you don't have WSL, follow the Microsoft guide to install WSL.
        2.  Clone GitHub Repository: run the following in WSL
            a.  git clone https://github.com/WSU-CPTS-223/pa2-avl-map-Keila0719.git
            b.  Navigate into the cloned folder: cd repo-name
        3.  Install Build Tools: run the following in WSL to install the build tool.
            a.  Sudo apt update
            b.  Sudo apt install build-essential git
        4. Change directory into the project folder
        5. Run : make
        6. Run the Program : ./main

-------------------------------------------------------------------------------------------------------------------------

Description:    
        Save the data given by the .csv file into a HashTree. I created two trees. One with the uniqID as the key and one as the category
        as the key. There will be two main functions, find <inventoryid> and listInventory <category_string>. The find function will accepts
        a string of inventoryid where it will find the product with a uniqID that matches the id that was inserted by the user and prints all
        the information about that product. The listInventory function will accepts a string of category_string where the user will enter a 
        category and the function will print the uniqid and product name for all the products that is under that category.

-------------------------------------------------------------------------------------------------------------------------

Additional Cleanup:
        - No additional cleanup. 

-------------------------------------------------------------------------------------------------------------------------

Testing Functions NOTES: 
    (You can run the test function by typing :test when running the program)

        Testing Insertion:
                - The test insertion will test if inserting function will insert elements into the hashTable as intended. Insertion function should use the uniqID as the key to that product. First it will convert the uniqID into an int and use that as an index to find where it will be inserted. Once it's able to find the corresponding spot, it will insert the Values. After every insertion, it will check if it needs to be rehashed. Since the loading factor is set as 0.5 rehash will happen whenever the hashtable is half full meaning (number of element)/(capacity) > 0.5. If it does need to be rehashed, it will multiply the capacity by 2 and find the nearest prime number that is greater than capacity*2.   
 
            Testing:         
                1. Normal Usage : Simple inputs, <key, value>
                            - Inputting information into the table worked as intended. It will use the first string inserted as the key and the second string as the value.

                2. Edge cases: Duplicates
                            - When I was testing what would happen when there are duplicates, in this test I tested (red, 1) and (red, 5), the first one will be accepted, and the second one will not. This is because we are using information with uniqID which means there is only one type of id for only one product so I made sure the function will not accept duplicates!

                3. error case: empty key or empty Value
                            - When we are inserting empty key, it will still run and count the empty uniqID as empty string and still look for index using the empty string and insert it. This key can be accessed by typing "" <-empty string. This was handy when doing insertion for the categories because some product didn't have a category and i used the empty string as a way to deal with those situations.
                            When the values are empty meaning missing information, it will still run and just have empty string as a place holders.
        
        
        Testing Parsing:
                - The test parsing will test if parse function reads the data line by line and separate the line with each of their corresponding category. The data we are given is complex since some are in quotes, some not, and some are empty. Also, we can’t simply use comma as a separation spot because there are commas inside each category so I created a function parseCSV() which will separate the information for me.
                
            Testing:
                - Let’s see if parsing works as intended. When I was testing, I used a smaller data file with only 10 lines of data so if there is an error, we will have an easier time figuring out what is happening.

                1. Normal case: parsing with the same format data
                        Problem 1: splitting the line at wrong places.
                            - After the test, parsing did read the line one by one, but some data was split at the wrong spot. This was because my parsingCSV() function splitting whenever I had “, so I fixed that. After fixing the parsingCSV() function, it is working as intended!

                2. Error case: When there are less than 28 categories
                        - When there are less than 28 categories, it will insert empty strings for missing information until we have 28 categories

        Testing Find <inventoryid>:
                - In this test I’m checking if it will find the correct product and prints the information correctly and when we can’t find the product because the user inserted a product that doesn’t exist, it will print out "Inventory/Product not found".

                1.	Normal Case 1: Accessing Something that exists in the table
                        Problem 1: Even after I parsed, it wasn't printing anything. It always said "Inventory/Product not found"
                            - This happened because after parsing, the destruction was called because we were excited about the function after parsing which caused it to cause destruction. To dix this I made sure they are in the same function.

                        Problem 2: Sometimes the program crashes
                            - After fixing the parsing problem It worked at first but there is sometimes the program crash. This was because it was trying to call destruction to an empty table. I was parsing in multiple places for testing reason so I made sure I only parse once like how I will when I construct the actual functions (not testing functions). After fixing that problem, now it works as intended! It prints all data that is under the inventoryid!
                    
                2. Edge Case: Finding something that does not exist in the table
                        -  When I was trying to find something that doesn’t exist in the table, it worked as intended! It prints "Inventory/Product not found"

                3. Error Case: Finding something with no key
                        - If for some reason we are trying to search for a product with no key, it is still possible to search for it by simply searing with an empty string. Users can insert "" <-empty string and it will print the product with no uniqID.

        
        Testing listInventory <Category_string>:
                - For this test, I’m making sure the product under the inserted categories are all printed. Making sure it is the correct product and when the category doesn’t exist, it will print out "Invalid Category"

                1.	Normal Case 1: Accessing Something that exists in the table
                        Problem 1: When I was trying to access something that exist in the table, it was only printing one product even when there is more than one product under that category. 
                            - This problem was happening because I wasn’t storing the information correctly. When I was trying to add a product under a category that already exists, it was added but replacing the product that was already there which made it so that there will only be one product at max. This was a simple mistake where I had an if statement when I was inserting but forgot to create another statement. After fixing the problem it was inserting more than one product under each category!

                        Problem 2: After I fixed the first problem I had, there is another problem that appeared. Now it’s causing errors when I try to get the ArrayList to that category. 
                            - This problem was happening because there was a mismatch between what was returned and what the function was supposed to return. When trying to access the Values of the category, I created a function which at first would return ArrayList<ArrayList<product>> which is not what they were supposed to return. This caused problem since there was a mismatch. However, after changing the return to match the return type as ArrayList<product> it was working!
                
                2. Edge Case 2: Finding something that does not exist on the table
                            - When I was finding a category that doesn’t exist on the table, it did work as intended and it printed "Invalid Category"

                3. Error Case: Having no category
                             - In the PA3 assignment, it was saying there are some products with no category. To also keep the products with no category, I made sure that these products are inserted under the category NA, so when wanting to access these products, the user can simply type NA. This will allow it to print all products with no category listed.

