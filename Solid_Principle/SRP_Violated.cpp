// SRP not  following.  Violating the rules.

#include<iostream>
#include<vector>
using namespace std;

// Product class representing any item of any ECommerce
class Product{
public:
    string name;
    double price;

    Product (string name,double price){
        this->name=name;
        this->price=price;
    };
};
// Violating SRP: ShoppingCart is handling multiple responsibilities
class ShoppingCart{
    private:
        vector<Product*>products;

    public:
        void addProduct(Product*p){
            products.push_back(p);
        }
        const vector<Product*>& getProducts(){
            return products;
        }

// 1. Calculate total price in cart

double calculateTotal(){
    double total=0;
    for (auto p:products){
        total+=p->price;
    }
    return total;
}
// 2. Violating SRP: Prints invoice (Should be in a seperate class)
void printInvoice(){
    cout<<"Shopping Cart Invoice:\n";
    for(auto p:products){
        cout<<p->name << "-$" << p->price << endl;
    }
    cout<< "Total : $ ::" << calculateTotal() << endl;
}
// 3. Violating SRP: Save to DataBase (Should be in a seperate class)
    void saveToDataBase(){
        cout<< " Saving shopping cart to database..." << endl;
    }
};

int main(){
    ShoppingCart* cart= new ShoppingCart();

    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",50));

    cart->printInvoice();
    cart->saveToDataBase();

    return 0;

}

