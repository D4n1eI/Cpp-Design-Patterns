#pragma once
#include <iostream>


#include "hot-drink.hpp"



struct HotDrinkFactory{
    virtual std::unique_ptr<HotDrink> make() const = 0;
};