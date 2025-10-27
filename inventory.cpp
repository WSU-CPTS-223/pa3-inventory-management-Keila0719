#include "inventory.hpp"

void Inventory::parse(ifstream &file, HashTable<string, Product>& table, HashTable<string, vector<Product>>& categoryTable){
    // This is used to get the line from the sample data
    string currentLine;
    // Skip the headder line
    getline(file, currentLine);

    // Get all the data from the file and seprate them into each category
    while (getline(file,currentLine)) {
		Product product; 
		// Getting a line from the data
		std::stringstream ss(currentLine);

		// seprating each data:
        // Seprating data is tricky for this data since it's messy. So I made a function that will seprate it for each case
		vector<string> sepratedLine = parseCSVFiles(currentLine);
		// Lets get each category out and put the information into each variable
		// For uniqID
		string uniqID = sepratedLine[0];
		product.uniqId = uniqID;
		// For productname
		product.productName = sepratedLine[1];
		// For brandName
		product.brandName = sepratedLine[2];
		// For asin
		product.asin = sepratedLine[3];
		// For category
		product.category = sepratedLine[4];
		// For upcEanCode
		product.upcEanCode = sepratedLine[5];
		// For listPrice
		product.listPrice = sepratedLine[6];
		// For sellingPrice
		product.sellingPrice = sepratedLine[7];
		// For quantity
		product.quantity = sepratedLine[8];
		// For modelNumber
		product.modelNumber = sepratedLine[9];
		// For aboutProduct
		product.aboutProduct = sepratedLine[10];
		// For productSpecification
		product.productSpecification = sepratedLine[11];
		// For technicalDetails
		product.technicalDetails = sepratedLine[12];
		// For shippingWeight
		product.shippingWeight = sepratedLine[13];
		// For productDimensions
		product.productDimensions = sepratedLine[14];
		// For image
		product.image = sepratedLine[15];
		// For variants
		product.variants = sepratedLine[16];
		// For sku
		product.sku = sepratedLine[17];
		// For productUrl
		product.productUrl = sepratedLine[18];		
		// For stock
		product.stock = sepratedLine[19];
		// For productDetails
		product.productDetails = sepratedLine[20];
		// For dimensions
		product.dimensions = sepratedLine[21];
		// For color
		product.color = sepratedLine[22];
		// For ingredients
		product.ingredients = sepratedLine[23];
		// For directionToUse
		product.directionToUse = sepratedLine[24];
		// For isAmazonSeller
		product.isAmazonSeller = sepratedLine[25];
		// For sizeQuantityVariant
		product.sizeQuantityVariant = sepratedLine[26];
		// For productDescription
		product.productDescription = sepratedLine[27];

		// After seprating each information, add it into the table
		table.insert(uniqID, product);
		// COMMENT OUT LATER: used it to check if it actually got inserted
		//find(uniqID, table);
		
		// I created a table categoryTable which uses the category as a key. This will be used for listInventory function
		// Seprate the categories
		// get the string
		std::stringstream categoryStream(product.category);

		// seprate them using '|'
		while(categoryStream.good()){
			string eachCategory;
			getline(categoryStream, eachCategory, '|');
			//Take the space out from the front and back
			// From the front
			while(eachCategory[0] == ' '){
				eachCategory = eachCategory.substr(1);
			}
			// From the back
			while(eachCategory[eachCategory.size()-1] == ' '){
				eachCategory = eachCategory.substr(0, eachCategory.size() - 1);
			}
			// Check if that category already exist
			vector<Product>* exist = categoryTable.find(eachCategory);
			if(exist == nullptr){ 
				// If that category doesn't exist, create a new list with that category
				vector<Product> newList = { product };
				// insert the category and the newlist with the product inside the table
				categoryTable.insert(eachCategory, newList);
			}else{ //If the category does already exist, add it after the existing stuff
				exist->push_back(product);
			}
			// COMMENT OUT LATER: used it to check if it actually got inserted
			//listInventory(eachCategory, categoryTable);
		}
		
	}
}


/* parseCSVFiles Function:
    Accepts: 
            string line
    Return: 
            vector<string> (this includes all 27 categories seprated from that line)
    Description:
            This parse and seprates the data into each of their categories.
			There are two types of data here. 
				The one that has a quote around them. ex: "--------",
					- This means that there are commas inside the quotes and they are seprated by quotes
				The one that doesn't have a quote and 
					- This means that there are no other commas except the one at the end that seprates the categories
			By using this information, we are going to check if this category has a quote around it or not and seprate
			them accordingly.
*/ 
vector<string> Inventory::parseCSVFiles(string line)
{
	// Where we are adding each category strings
	vector<string> sepratedLine;
	// Where we are constructing the string by adding the character one by one
	string category;
	// Counts to see how many characters are in there. Mainly used to see if we are at the first letter of the category
	int charCount = 0;
	// Checks if the current category is inside a quote
	bool isInQuotes = false;
	//check if there is a quote at the front and back of the string
	for(int i = 0; i < line.size(); i++){ // There are 27 categories in the string line
		// Check if the current category is the start of the quote, end of the quote or the word inside the quotes
		if(isInQuotes){ // Since true, we already started the word that has a quote.
			// Check if the current character is a quote or not
			if(line[i] == '"'){
				// Check if it's an quote inside the string
				if(i+1 < line.size() && line[i+1] == '"'){ 
					// If yes, add a quote into category string
					category += '"';
					i++;
				}else{
					// If not, it's the end of the quote
					isInQuotes = false;
				}
			}else{	// If the current letter is not a quote
					// Add that letter into the string
					category += line[i];
			}
		}else{ // If false, it means it's the start quote or it just doesn't have a quote for this category
			// Check if the current character is a quote
			if(line[i] == '"' && charCount == 0){ // If true, it means the start of quote
				// Since the quote started, make the bool true
				isInQuotes = true;
			}else{ // If the word doesn't start with a quote
				// Check if the current character is a comma
				if(line[i] == ','){ // This means that it's the end of that category
					// Add the category string into the sepratedLine vector
					sepratedLine.push_back(category); 
					//cout << "" << category << endl;

					// Reset the category string so we can add the characters for the next category
					category.clear(); 
					// Reset the charCount
					charCount = 0;
				}else{
					category += line[i];
					charCount ++;
				}
			}
		}
	}
	// Push the last catgory
	sepratedLine.push_back(category);

	// TESTING IF IT WORKS : COMMENT OUT LATER
	/*
	if(sepratedLine.size() != 28){
		if(sepratedLine.size() > 28){
			cout<< "larger: " << sepratedLine.size() << " " << sepratedLine[0] << endl; 
		}else{
			cout<< "smaller: " << sepratedLine[0] << endl; 
			while(sepratedLine.size() != 27){
				sepratedLine.push_back("");
			}
		}
	}
	*/
	
	// Once we are done seprating data into each category, return the vector with all the seprated category
	return sepratedLine;
}

void Inventory::find(string inventoryID, HashTable<string, Product>& table)
{
	// Get the value of the inventoryID product
	Product* inventoryProduct = table.find(inventoryID);

	// Check if they were actually able to find the product for the inventoryID
	if(inventoryProduct == nullptr){
		// Not able to find
		cout << "Inventory/Product not found\n" << endl;
	}else{
		// Was able to find so print all details
		// I like to make it line up so using \t to line them 
		cout << "uniqId: \t\t" << inventoryProduct->uniqId << endl;
		cout << "productName: \t\t" << inventoryProduct->productName << endl;
		cout << "brandName: \t\t" << inventoryProduct->brandName << endl;
		cout << "asin: \t\t\t" << inventoryProduct->asin << endl;
		cout << "category: \t\t" << inventoryProduct->category << endl;
		cout << "upcEanCode: \t\t" << inventoryProduct->upcEanCode << endl;
		cout << "listPrice: \t\t" << inventoryProduct->listPrice << endl;
		cout << "sellingPrice: \t\t" << inventoryProduct->sellingPrice << endl;
		cout << "quantity: \t\t" << inventoryProduct->quantity << endl;
		cout << "modelNumber: \t\t" << inventoryProduct->modelNumber << endl;
		cout << "aboutProduct: \t\t" << inventoryProduct->aboutProduct << endl;
		cout << "productSpecification: \t" << inventoryProduct->productSpecification << endl;
		cout << "technicalDetails: \t" << inventoryProduct->technicalDetails << endl;
		cout << "shippingWeight: \t" << inventoryProduct->shippingWeight << endl;
		cout << "productDimensions: \t" << inventoryProduct->productDimensions << endl;
		cout << "image: \t\t\t" << inventoryProduct->image << endl;
		cout << "variants: \t\t" << inventoryProduct->variants << endl;
		cout << "sku: \t\t\t" << inventoryProduct->sku << endl;
		cout << "productUrl: \t\t" << inventoryProduct->productUrl << endl;
		cout << "stock: \t\t\t" << inventoryProduct->stock << endl;
		cout << "productDetails: \t" << inventoryProduct->productDetails << endl;
		cout << "dimensions: \t\t" << inventoryProduct->dimensions << endl;
		cout << "color: \t\t\t" << inventoryProduct->color << endl;
		cout << "ingredients: \t\t" << inventoryProduct->ingredients << endl;
		cout << "directionToUse: \t" << inventoryProduct->directionToUse << endl;
		cout << "isAmazonSeller: \t" << inventoryProduct->isAmazonSeller << endl;
		cout << "sizeQuantityVariant: \t" << inventoryProduct->sizeQuantityVariant << endl;
		cout << "productDescription: \t\n" << inventoryProduct->productDescription << endl;
	}
}

void Inventory::listInventory(string category, HashTable<string, vector<Product>>& categoryTable){
	// Get the table of the product that matches the category
	vector<Product> products = categoryTable.findCategory(category);
	// Check if they were actually able to find the product for the inventoryID
	if(products.empty()){
		// Not able to find
		cout << "Invalid Category\n" << endl;
	}else{
		// Print all with the finding category
		for(int i = 0; i < products.size(); i++){
			cout << "uniqId: \t\t" << products[i].uniqId << endl;
			cout << "productName: \t\t" << products[i].productName << "\n\n"<< endl;
		}
	}
}
