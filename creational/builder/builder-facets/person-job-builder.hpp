#pragma once

class PersonJobBuilder : public PersonBuilderBase
{
    typedef PersonJobBuilder Self;

public:
    PersonJobBuilder(Person &person) : PersonBuilderBase(person)
    {

    }

    Self & at(std::string company_name){
        person.company_name= company_name;
        return *this;
    }

    Self & as_a(std::string position){
        person.position= position;
        return *this;
    }

    Self & earning(int anual_income){
        person.anual_income = anual_income;
        return *this;
    }
};