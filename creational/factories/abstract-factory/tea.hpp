#pragma once
#include <iostream>
#include "hot-drink.hpp"

struct Tea : public HotDrink
{

    void prepare(int volume) override
    {
        std::cout << "Take a tea bag, boil water, pour " << volume << " ml and "
                  << "add some lemon\n";
    }
};