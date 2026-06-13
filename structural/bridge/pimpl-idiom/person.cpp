#include "person.hpp"
#include <iostream>

class Person::PersonImpl
{
public:
    void Person::PersonImpl::greet(Person *p)
    {
        std::cout << "Hello, my name is " << p->name << std::endl;
    }

private:
    
};

Person::Person() : impl{new PersonImpl}
{
}

Person::~Person()
{
    delete impl;
}

void Person::greet()
{
    impl->greet(this);
}