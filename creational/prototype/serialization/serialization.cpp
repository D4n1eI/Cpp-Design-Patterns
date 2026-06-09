#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>
#include <cmath>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace boost;

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

    Address(const Address &other) : city{other.city}, street{other.street}, suite{other.suite} {}

    Address(){}

    private:
    friend class serialization::access;
    template <class archive>
    void serialize(archive&ar,const unsigned version){
        ar & city;
        ar & street;
        ar & suite;
    }
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
    Contact(){}

private:
    friend class serialization::access;
    template <class archive>
    void serialize(archive&ar,const unsigned version){
        ar & name;
        ar & address;
    }
};

struct EmployeeFactory
{
    static std::unique_ptr<Contact> new_main_office_employee(const std::string &name, const int suite)
    {
        static Contact p{"", new Address{"London", "123 East Dr", 0}};
        return new_employee(name, suite, p);
    }

private:
    static std::unique_ptr<Contact> new_employee(const std::string &name, int suite, const Contact &prototype)
    {
        auto result = std::make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

int main()
{


    auto clone = [](Contact &c){
        std::ostringstream oss;
        archive::text_oarchive oa(oss);
        oa << c;
        std::string s = oss.str();
        std::cout << s << std::endl;

        std::istringstream iss{s};
        archive::text_iarchive ia(iss);
        Contact result;
        ia>>result;
        return result;
    };

    auto john = EmployeeFactory::new_main_office_employee("John",123);
    auto jane = clone(*john);
    jane.name = "Jane";
    std::cout << *john << std::endl;
    std::cout << jane << std::endl;
    return 0;
}
