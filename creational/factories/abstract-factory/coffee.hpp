#pragma once
#include <iostream>
#include "hot-drink.hpp"

struct Coffee : public HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Grind some beans, boil water, pour "<<volume << " ml, some cream and enjoy!";
    }
}; 