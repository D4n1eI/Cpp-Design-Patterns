#pragma once

#include "hot-drink-factory.hpp"

#include "hot-drink.hpp"
#include "coffee-factory.hpp"
#include <map>
#include "tea-factory.hpp"

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory()
    {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string &name)
    {
        auto drink = hot_factories[name]->make();
        return drink;
    }
};