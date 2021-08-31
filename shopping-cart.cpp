#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include <limits> 

using namespace std;

//class Item
class Item
{
private:
    string itemName;
    string itemDescription;
    double itemPrice;
    int itemQuantity;

public:
//Mutators
    void SetName(string);
    void SetPrice(double);
    void SetQuantity(int);
    void SetDescription (string);

//Accessors
    string GetName() const;
    double GetPrice() const;
    int GetQuantity() const;
    string GetDescription() const;

//default constructor
    Item(string = "none", string = "none", double = 0.00, int = 0);

// print function, also accessor
    void Print() const;
    void PrintDescription() const;
};

// Shopping cart class
class ShoppingCart
{
private:
    string customerName;
    string currentDate;
    vector<Item> itemsCart;    
    int FindItemIndex(const string&) const; 

public:
// Accessors 
    string GetCustomerName() const;
    string GetDate() const;
    int GetTotalQuantity() const;
    double GetTotalCost() const;
    void PrintTotal() const;
    void PrintDescriptions() const;
// Mutators
    void AddItem(const Item&);
    void RemoveItem(const string&);
    void ChangeQuantity(const string&, int); 
    ShoppingCart(string = "none", string = "April 1, 2020");   
};


// default constructor for Item class
Item::Item(string name, string desc, double price, int quantity) : itemName(name), itemDescription(desc), itemPrice(price), itemQuantity(quantity){
}

// default constructor for Shopping class
ShoppingCart::ShoppingCart(string name, string date) : customerName(name), currentDate(date){
}

// functions Set...
void Item::SetName(string name){
    itemName = name;
}

void Item::SetPrice(double price){
    itemPrice = price;
}

void Item::SetQuantity(int q){
    itemQuantity = q;
}

void Item::SetDescription(string desc){
    itemDescription = desc;
}

// functions Get...
string Item::GetName() const{
    return itemName;
}

double Item::GetPrice() const{
    return itemPrice;
}

int Item::GetQuantity() const{
    return itemQuantity;
}

string Item::GetDescription() const{
    return itemDescription;
}

string ShoppingCart::GetCustomerName() const{
    return customerName;
}

string ShoppingCart::GetDate() const{
    return currentDate;
}


//Prints description
void Item::PrintDescription() const{
    // Milk: white gallon, 1 gallon
    cout << GetName() << ": " << GetDescription() << endl;
}

//Prints the item summary
void Item::Print() const{
// sets it to round after 2 decimal places
    cout << setprecision(2) << fixed;
    // Milk: 10 @ $1 = $10
    if (GetQuantity()*GetPrice() != 0){
        cout << GetName() << ": " << GetQuantity() << " at $" << GetPrice() << " = $" << (GetQuantity() * GetPrice()) << endl;
    }
}
/****** Shopping Cart *////////

//Prints customer name and date
void printCustomerNameAndDate(ShoppingCart& list)
{
  cout << "\nCustomer name: " << list.GetCustomerName() << endl;
  cout << "Today's date: " << list.GetDate() << endl;
}

// 'p'- function, print menu 
char PrintMenu(){
    char choice;
    cout << "\nMenu\n";
    cout << "a - Add item to cart\n";
    cout << "d - Remove item from cart\n";
    cout << "c - Change item quantity\n";
    cout << "i - Output item descriptions\n";
    cout << "o - Output shopping cart\n";
    cout << "q - Quit\n";
    cout << "\nChoose an option: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

//'a' - function, add item
void ShoppingCart::AddItem(const Item& item){
   itemsCart.push_back(item);
}

//Find item index function 
int ShoppingCart::FindItemIndex(const string& name) const{
    for (unsigned int i =0; i < itemsCart.size(); i++){
        if (itemsCart.at(i).GetName() == name){
            return i;
        }
    }
    return -1;

}
// 'd' function, remove item
void ShoppingCart::RemoveItem(const string& name){

        if (FindItemIndex(name) == -1 ){
            cout << "Item not found in cart." << endl;
        }else{
            itemsCart.erase(itemsCart.begin()+ FindItemIndex(name));    
        }
}
// 'c' function, change quantity
void ShoppingCart::ChangeQuantity(const string& name, int quantityChange){
    int index = FindItemIndex(name);
    if (index == -1){
        cout << "Item not found in cart." << endl;
    } else{
        itemsCart.at(index).SetQuantity(quantityChange);
    }
    
    for (unsigned int i = 0; i < itemsCart.size(); i++){
        if ((quantityChange = 0)){
            itemsCart.erase(itemsCart.begin() + i);
        }
    }
}

// GetTotalQuantity function
int ShoppingCart::GetTotalQuantity() const {
    int totalQuantity = 0;
    for(unsigned int i = 0; i < itemsCart.size(); i++){
        totalQuantity += itemsCart.at(i).GetQuantity();
    }
    return totalQuantity;
}

//GetTotalCost function
double ShoppingCart::GetTotalCost() const{
    double total = 0.00;
    for (unsigned int i = 0; i < itemsCart.size(); i++){
        total += itemsCart.at(i).GetPrice() * itemsCart.at(i).GetQuantity();
    }
    return total;
}

//Prints the overall sum
void ShoppingCart::PrintTotal() const{
    if (itemsCart.size() == 0 ){
        cout << "Shopping cart is empty." << endl;
    }

    for (unsigned int i = 0; i < itemsCart.size(); i++){
        itemsCart.at(i).Print();
    }
    cout << endl << "Total: $" << GetTotalCost() << endl;
}

// Prints description of items
void ShoppingCart::PrintDescriptions()const {
    if (itemsCart.size() == 0){
        cout << "Shopping cart is empty." << endl;
    }

    for (unsigned int i = 0; i < itemsCart.size(); i++){
        Item currentItem = itemsCart.at(i);
        currentItem.PrintDescription();
    }
}

// made function for cleanness
void addItemFunction(ShoppingCart& list){
    string name, description;
    double price;
    int quantity;

    cout << "\nADD ITEM TO CART" << endl;
    cout << "Enter the item name: ";
    if (!getline(cin, name)){
        return;
    }
    cout << "Enter the item description: ";
    if (!getline(cin, description)){
        return;
    }
// error checking for price
    cout << "Enter the item price: $";
    while(!(cin >> price)){
        if (cin.eof()){
            return;
        } else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    cout << "Enter the item price: $";
    }
// error checking for quantity
    cout << "Enter the item quantity: ";
    while(!(cin >> quantity)){
        if (cin.eof()){
            return ;
        } else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    cout << "Enter the item quantity: ";
    }
    Item newItem(name, description, price, quantity);
    list.AddItem(newItem);
}

//for cleanliness inside switch statement
void removeItemFunction(ShoppingCart& list){
    string name;
    
    cout << "\nREMOVE ITEM FROM CART" << endl;
    cout << "Enter name of item to remove: ";
    getline(cin, name);
    list.RemoveItem(name);
}

// cleanliness
void changeQuantityFunction(ShoppingCart& list){
    string name;
    int quantity;

    cout << "\nCHANGE ITEM QUANTITY" << endl;
    cout << "Enter the item name: ";
    getline(cin, name);
    cout << "Enter the new quantity: ";
    cin >> quantity;
    list.ChangeQuantity(name, quantity);
}

// cleanliness
void printDescriptionsFunction(ShoppingCart& list){
    cout << endl;
    cout << list.GetCustomerName() << "\'s Shopping cart - " << list.GetDate();
    cout << endl << endl << "Item Descriptions" << endl;
    list.PrintDescriptions();
}

// cleanliness
void printTotalFunction(ShoppingCart& list){
    cout << endl;
    cout << list.GetCustomerName() << "\'s Shopping Cart - " << list.GetDate() << endl;
    cout << "Number of items: " << list.GetTotalQuantity() << endl << endl;
    list.PrintTotal();
}


/////////// INT MAIN//////////
int main(){

    string name, date;
    char userInput;

    // asks for customer name and date
    cout << "Enter customer's name: ";
    getline(cin, name);
// Control-D check
    if (cin.eof()){
            cout << endl;
            return 0;
        }
    cout << "Enter today's date: ";
    getline(cin, date);
// Control-D check
    if (cin.eof()){
            cout << endl;
            return 0;
        }
    ShoppingCart list(name, date);
    printCustomerNameAndDate(list);
    // while loop to run until 'q'
    while(userInput != 'q'){

// Control-D check
        if (cin.eof()){
            cout << endl;
            return 0;
        }
        userInput = PrintMenu();
        if (cin.eof()){
            cout << endl;
            return 0;
        }
    
    // checks for 'a', 'd', 'c', 'i', 'o', or 'q'
    switch(userInput){
    case 'a':
    
     addItemFunction(list);
        break;
    
    case 'd':
        removeItemFunction(list);
        break;
    
    case 'c':
        changeQuantityFunction(list);
        break;
    
    case 'i':
       printDescriptionsFunction(list);
       break;
    
    case 'o':
        printTotalFunction(list);
        break;

    case 'q':
        return 0;
        break;

    default:
        continue;
    }
}
    return 0;
}

