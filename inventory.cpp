#include "inventory.hpp"

void Inventory::parse(ifstream &file, HashTable<string, Product>& table){
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
		// For brandName
		product.brandName = sepratedLine[1];
		// For asin
		product.asin = sepratedLine[2];
		// For category
		product.category = sepratedLine[3];
		// For upcEanCode
		product.upcEanCode = sepratedLine[4];
		// For listPrice
		product.listPrice = sepratedLine[5];
		// For sellingPrice
		product.sellingPrice = sepratedLine[6];
		// For quantity
		product.quantity = sepratedLine[7];
		// For modelNumber
		product.modelNumber = sepratedLine[8];
		// For aboutProduct
		product.aboutProduct = sepratedLine[9];
		// For productSpecification
		product.productSpecification = sepratedLine[10];
		// For technicalDetails
		product.technicalDetails = sepratedLine[11];
		// For shippingWeight
		product.shippingWeight = sepratedLine[12];
		// For productDimensions
		product.productDimensions = sepratedLine[13];
		// For image
		product.image = sepratedLine[14];
		// For variants
		product.variants = sepratedLine[15];
		// For sku
		product.sku = sepratedLine[16];
		// For productUrl
		product.productUrl = sepratedLine[17];		
		// For stock
		product.stock = sepratedLine[18];
		// For productDetails
		product.productDetails = sepratedLine[19];
		// For dimensions
		product.dimensions = sepratedLine[20];
		// For color
		product.color = sepratedLine[21];
		// For ingredients
		product.ingredients = sepratedLine[22];
		// For directionToUse
		product.directionToUse = sepratedLine[23];
		// For isAmazonSeller
		product.isAmazonSeller = sepratedLine[24];
		// For sizeQuantityVariant
		product.sizeQuantityVariant = sepratedLine[25];
		// For productDescription
		product.productDescription = sepratedLine[26];

		// After seprating each information, add it into the table
		table.insert(uniqID, product);
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
		char c = line[i];
		// Check if the current category is the start of the quote, end of the quote or the word inside the quotes
		if(isInQuotes){ // Since true, we already started the word that has a quote.
			// Check if the current character is a quote or not
			if(line[i] == '"'){
				// Check if it has a comma after
				i++;
				if(line[i] == ','){ //This means the category ended
					// Add the category string into the sepratedLine vector
					sepratedLine.push_back(category); 
					// Reset the category string so we can add the characters for the next category
					category.clear(); 
					// Reset the charCount
					charCount = 0;
					// Reset the bool variable
					isInQuotes = false;
				}else{ // This means the category did not end and this quote is just one of the letter from that category
					i--;
					// Add that letter into the string
					category += line[i];
					charCount ++;
				}
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
					// Reset the category string so we can add the characters for the next category
					category.clear(); 
					// Reset the charCount
					charCount = 0;
				}
			}
		}
	}
	// Push the last catgory
	sepratedLine.push_back(category);

	// Once we are done seprating data into each category, return the vector with all the seprated category
	return sepratedLine;
}

void Inventory::find(string uniqID)
{
}

void Inventory::listInventory(string category)
{
}
