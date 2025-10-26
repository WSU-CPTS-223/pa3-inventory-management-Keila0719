#include "inventory.hpp"

void Inventory::parse(ifstream &file, HashTable<string, Product> table){
    // This is used to get the line from the sample data
    string currentLine;
    // Skip the headder line
    getline(file, currentLine);

    // Get all the data from the file and seprate them into each category
    while (getline(file,currentLine)) {
		Product product; 
        string uniqID;
		// Getting a line from the data
		std::stringstream ss(currentLine);

		// seprating each data:
        // Seprating data is tricky for this data since it's messy. So we are seprating each one by... idk
		// For uniqID,
		getline(ss, uniqID, ',');
        
		// For productName
		getline(ss, product.productName, ',');
		// For city
		getline(ss, uscity.city, ',');
		// For state_id
		getline(ss, uscity.state_Id, ',');
		// For state_name
		getline(ss, uscity.state_Name, ',');
		// For zcta
		getline(ss, uscity.zcta, ',');
		// For parent_zcta
		getline(ss, uscity.parent_Zcta, ',');
		// For population
		getline(ss, uscity.population, ',');
		// For density
		getline(ss, uscity.density, ',');
		// For county_fips
		getline(ss, uscity.county_Fips, ',');
		// For county_name
		getline(ss, uscity.county_Name, ',');
    
}

void Inventory::find(string uniqID)
{
}

void Inventory::listInventory(string category)
{
}
