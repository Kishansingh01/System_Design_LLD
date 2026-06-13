#include<iostream>
#include<vector>

using namespace std;

// Product class representing any item in eCommerce
class Product{
    public:
        string name;
        double price;

        Product(string name,double price){
            this->name=name;
            this->price=price;
        }
};
// 1. Only responsible for cart related business logic
class ShoppingCart{
    private:
        vector<Product*>products; // Store heap related products.
    public:
        void addProduct(Product*p){
            products.push_back(p);
        }
    const vector<Product*>& getProducts(){
        return products;
    }
//  Calculate total price in the cart.
double calculateTotal(){
    double total=0;
    for(auto p:products){
        total+=p->price;
    }
    return total;
}
};
// 2. ShoppingCartPrinter: Only responsible for printing the invoices
class shoppingCartPrinter{
    private:
        ShoppingCart* cart;
    public:
        shoppingCartPrinter(ShoppingCart*cart){
            this->cart=cart;
        }
    void printInvoice(){
        cout<< "ShoppingCArt Invoice:\n";
        for(auto p:cart->getProducts()){
            cout<< p->name << "-$ " <<p->price << endl;
        }
        cout << "Total: $" << cart->calculateTotal() << endl;
    }
};

// Abstract class

class Persistence{
    private:
        ShoppingCart* cart;
    public:
        virtual void save(ShoppingCart* cart)= 0; // Pure virtual function
};
class SQLPersistence: public Persistence{
    public:
        void save(ShoppingCart* cart) override {
            cout << "Saving shopping cart to SQL DB..." << endl;
        }
};
class MongoPersistence : public Persistence{
    public:
        void save(ShoppingCart* cart) override{
            cout <<"Saving shopping cart to mongodb...." << endl;
        }
};
class FilePersistence: public Persistence{
    public:
        void save(ShoppingCart* cart) override{
            cout<<"Saving shopping cart to file.." << endl;
        }
};

int main(){
    ShoppingCart* cart= new ShoppingCart();
    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("mouse",50));

    shoppingCartPrinter* printer= new shoppingCartPrinter(cart);
    printer->printInvoice();

    Persistence* db= new SQLPersistence();
    Persistence* mongo=new MongoPersistence();
    Persistence* file= new FilePersistence();

    db->save(cart); // Save to SQL database.
    mongo->save(cart); // Save to mongoDB
    file->save(cart); // Save to file

    return 0;

}

