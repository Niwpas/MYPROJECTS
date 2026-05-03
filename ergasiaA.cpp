#include <iostream>
#include <string>
using namespace std;

class Product {
    private:
    int code;
    string name;
    float price;
    int quantity;
     
    static int productCount;

    public: 

// constructor 

    Product (int c = 0, string n = "", float p = 0.0, int q = 0) {
        code = c;
        name = n;
        price = p;
        quantity = q;
        productCount++;
    }

    //copy constructor 

Product (const Product &p) {
    code = p.code;
    name = p.name;
    price = p.price;
    quantity = p.quantity;
    productCount++;
}
~Product() {

}

float getPrice() const {
return price;
}

int getQuantity() const {
    return quantity;
}

void setQuantity(int q) {
    quantity = q;
}

// printing 

void print() const {
    std::cout<<"Code: "<<code<<endl;
    std::cout<<"Name: "<<name<<endl;
    std::cout<<"Price: "<<price<<endl;
    std::cout<<"Quantity: "<<quantity<<endl;
    std::cout<<"======================"<<endl;
}

static int getProductCount() {
    return productCount;
}

bool operator>(const Product &p) const {
    return price > p.price;
}

friend void printProduct(const Product &p);
friend void updateQuantity(Product &p, int q);
};

int Product::productCount = 0; 

void printProduct(const Product &p) {
    std::cout<<"[Friend Print]"<<endl;
    std::cout<<p.name<<" - "<<p.price<<" ("<<p.quantity<< " )"<<endl;
}

void updateQuantity(Product &p, int q) {
    p.quantity = q;   
}

class Store {
    private: 
    Product* products;
    int size;

    public:
    Store(int s) {
        size = s;
        products = new Product[size];
    }
    ~Store() {
        delete[] products;
    }
    void setProduct(int index, const Product &p) {
        if (index >= 0 && index < size) {
            products[index] = p;
        }
    }
    void printAll() const {
        for (int i = 0; i < size; i++) {
            products[i].print();
        }
    }
    Product getMostExpensive() const {
        Product max = products[0];
        for(int i = 1; i < size; i++) {
            if (products[i] > max) {
                max = products[i];
            }
        }
        return max;
    }
}; 

int main() {
    int n;
    std::cout<<"Dwse arithmo proiotnwnvn:"; 
    std::cin>>n;

    Store store(n);

    for (int i = 0; i < n; i++) {
        int code, quantity;
        string name;
        float price;

        std::cout<<"\nProduct "<<i+1<<endl;
        std::cout<<"Code: ";
        std::cin>>code;
        std::cout<<"Name: ";
        std::cin>>name;
        std::cout<<"Price: ";
        std::cin>>price;
        std::cout<<"Quantity: ";
        std::cin>>quantity;

        Product p(code, name, price, quantity);
        store.setProduct(i, p);

    }

std::cout<<"\nALL PRODUCTS: "<<endl;
store.printAll();

std::cout<<"\nMost Expensive Product: "<<endl;
Product max = store.getMostExpensive();
max.print();

std::cout<<"\nTotal Products: "<<Product::getProductCount()<<endl;

    return 0;
}

