#pragma once

#include "hot-drink-factory.hpp"
#include "tea.hpp"
#include <iostream>


struct TeaFactory : HotDrinkFactory{

    virtual std::unique_ptr<HotDrink> make() const override{
        return std::make_unique<Tea>();
    }

};