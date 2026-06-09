#pragma once
#include "person.hpp"

class PersonAddressBuilder;
class PersonJobBuilder;



class PersonBuilderBase
{
protected:
    Person &person;

public:
    PersonBuilderBase(Person &person);

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

    operator Person() const{
        return std::move(person);
    }
};

class PersonBuilder : public PersonBuilderBase
{
private:
    Person p;

public:
    PersonBuilder();  
};