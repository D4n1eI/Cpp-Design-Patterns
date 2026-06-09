#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>
#include <cmath>

struct Address
{
    std::string city, street;
    int suite;
    Address(const std::string &city, const std::string &street, const int &suite) : city{city}, street{street}, suite{suite} {}
    friend std::ostream &operator<<(std::ostream &os, const Address addr)
    {
        os << "Address:["
           << "city: " << addr.city << ", "
           << "street: " << addr.street << ", "
           << "suite: " << addr.suite
           << "]";
        return os;
    }

    Address(const Address &other) : city{other.city},street{other.street},suite{other.suite}{}
};

struct Contact
{
    std::string name;
    Address *address;
    Contact(const std::string &name, Address *address) : name{name}, address{address} {}

    friend std::ostream &operator<<(std::ostream &os, const Contact contc)
    {
        os << "Contact:["
           << "name: " << contc.name << ", "
           << "address: " << contc.address
           << "]";
        return os;
    }

    Contact(const Contact &other) : name{other.name}, address{new Address{*other.address}}
    {
    }
};


int main()
{
    Contact john{"John Doe", new Address{"London", "123 East Dr", 123}};

    Contact jane = john; // shallow copy
    jane.name = "Jane Smith";
    jane.address->suite = 124;

    std::cout << john << std::endl;

    std::cout << jane << std::endl;

    return 0;
}