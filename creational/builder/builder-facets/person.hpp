#pragma once
#include <iostream>

class PersonBuilder;


class Person
{
public:
    std::string street_address, post_code, city;

    std::string company_name, position;
    int anual_income{0};

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;

    
    static PersonBuilder create();   
};

std::ostream& operator<<(std::ostream& os, const Person& person);