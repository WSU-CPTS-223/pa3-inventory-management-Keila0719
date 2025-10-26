#pragma once
#include <string>
#include <vector>

using std::string;

class Product{
public:
    string uniqId;
    string productName;
    string brandName;
    string asin;
    string category;
    string upcEanCode;
    string listPrice;
    string sellingPrice;
    string quantity;
    string modelNumber;
    string aboutProduct;
    string productSpecification;
    string technicalDetails;
    string shippingWeight;
    string productDimensions;
    string image;
    string variants;
    string sku;
    string productUrl;
    string stock;
    string productDetails;
    string dimensions;
    string color;
    string ingredients;
    string directionToUse;
    string isAmazonSeller;
    string sizeQuantityVariant;
    string productDescription;
    
    Product() = default;
    Product(string newUniqId, string newProductName, string newBrandName, string newAsin, string newCategory, string newUpcEanCode,
            string newListPrice, string newSellingPrice, string newQuantity, string newModelNumber, string newAboutProduct, string newProductSpecification,
            string newTechnicalDetails, string newShippingWeight, string newProductDimensions, string newImage, string newVariants, string newSku,
            string newProductUrl, string newStock, string newProductDetails, string newDimensions, string newColor, string newIngredients, string newDirectionToUse,
            string newIsAmazonSeller, string newSizeQuantityVariant, string newProductDescription): uniqId(newUniqId), productName(newProductName),
            brandName(newBrandName), asin(newAsin), category(newCategory), upcEanCode(newUpcEanCode), listPrice(newListPrice), sellingPrice(newSellingPrice),
            quantity(newQuantity), modelNumber(newModelNumber), aboutProduct(newAboutProduct), productSpecification(newProductSpecification),
            technicalDetails(newTechnicalDetails), shippingWeight(newShippingWeight), productDimensions(newProductDimensions), image(newImage),
            variants(newVariants), sku(newSku), productUrl(newProductUrl), stock(newStock), productDetails(newProductDetails), dimensions(newDimensions),
            color(newColor), ingredients(newIngredients), directionToUse(newDirectionToUse), isAmazonSeller(newIsAmazonSeller),
            sizeQuantityVariant(newSizeQuantityVariant), productDescription(newProductDescription){}
            
};