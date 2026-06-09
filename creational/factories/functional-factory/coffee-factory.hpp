#pragma once

#include "hot-drink-factory.hpp"
#include "coffee.hpp"
#include <iostream>


struct CoffeeFactory : HotDrinkFactory{

    virtual std::unique_ptr<HotDrink> make() const override{
        return std::make_unique<Coffee>();
    }
};