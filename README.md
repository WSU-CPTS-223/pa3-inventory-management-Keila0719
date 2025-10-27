[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA4 Skeleton Code
We expect a fully functioninig command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.

How to run the code:
        1.	Open WSL: If you don't have WSL, follow the Microsoft guide to install WSL.
        2.	Clone GitHub Repository: run the following in WSL
            a.	git clone https://github.com/WSU-CPTS-223/pa2-avl-map-Keila0719.git
            b.	Navigate into the cloned folder: cd repo-name
        3.	Install Build Tools: run the following in WSL to install the build tool.
            a.	Sudo apt update
            b.	Sudo apt install build-essential git
        4. Change directory into the project folder
        5. Run : make
        6. Run the Program : ./main

Description:    
        Save the data given by the .csv file into a HashTree. I created two trees. One with the uniqID as the key and one as the category
        as the key. There will be two main functions, find <inventoryid> and listInventory <category_string>. The find function will accepts
        a string of inventoryid where it will find the product with a uniqID that matches the id that was inserted by the user and prints all
        the information about that product. The listInventory function will accepts a string of category_string where the user will enter a 
        category and the function will print the uniqid and product name for all the products that is under that category.

Additional Cleanup:
	    - No additional cleanup. 

Testing Functions NOTES: 
    (You can run the test function by typing :test when running the program)

        Testing Insertion:
                - The test insertion will test if inserting function will insert elements into the hashtable as intended. Insertion function should use the uniqID of
                    that product as a key. First it will convert the uniqID into an int and use that as an index to find where it will be inserted. Once it's
                    able to find the corresponding spot, it will insert the Values at that index. After every insertion, it will check if it needs to be rehash.
                    Rehash will happen when ever the hashtable is half full meaning (number of element)/(capacity) > 0.5 since the loading factor is set as 0.5.
                    If it does need to be rehash, it will multiply the capacity by 2 and find the nearest primenumber that is greater than capacity*2.   
                
                Testing:         
                1. Normal Usage : Simple inputs, <string, string>
                    - It worked!
                2. Edge cases : Duplicates
                    - When we insert a duplicate like (red, 1) and (red, 5), the first one will be accepted and the second one will not
                    - In our normal cases, we use uniqID as our key so when in our normal case, we will not have duplicates
                    - It didn't overwrite or insert it so worked well
                3. error case : no key or no Value
                    - First I tested ("a", nullptr) -> this crashed the program saying "Exception has occurred. Aborted" cool.
                    - Second I tested (nullptr, "3") -> same outcome
                    - In our data, we won't have a nullptr for either Key or Value so it's all good
                    - It was cool to learn about this

        Testing Parsing:
                - The test parsing will test if parse function will read the data line by line and separate the line with each of their corresponding category.
                    The parse function
                - Lets see if parsing works as intended (using a smaller data file with only 10 lines of data so if there is an error, we know what is happening)
                - The parsing did read the line one by one but with some data it split the line at where they are not supposed to
                - fixed my parsingCSV() function where it will separate the lines by each character.
                - Now it works as intended!

        Testing Find <inventoryid>:
                1. Normal Usage 1 : Accessing Something that exists in the table
                    - Even after I parse, it wasn't printing anything. It always said "Inventory/Product not found" - why?
                        - Figured it out: it was because after parsing, destruction was called. I made sure that they were in the same function.
                    - It worked at first but there are sometimes the program crash - why?
                        - Figured it out: It was trying to call destruction to an empty table. I was parsing in multiple place for testing reason so I made sure parse was only called once
                    - Now it works as intended! It prints all data that is under the inventoryid
                2. Normal Usage 2 : Finding something that does not exist in the table
                    - Worked as intended! It prints "Inventory/Product not found"

        Testing listInventory <Category_string>:
                1. Normal Usage 1 : Accessing Something that exists in the table
                    - It's only printing one product - why?
                        - Figured it out: I wasn't storing the information correctly. It was always replacing the information under that category which made it only have one information at max
                    - Now it's causing error when I'm trying to get the vector to the category. - why?
                        - Apparently it the function findcategory was trying to return vector<vector<Product>> which was not the correct return type which is vector<Product>. Fixed it and now it's working!
                2. Normal Usage 2 : Finding something that does not exist in the table
                    - This worked as intended! It prints "Invalid Category"
                3. Error Case : Having no category
                    - Yes! it did work, when searching for a category "" <- empty string, it does print the products with no category