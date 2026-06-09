#pragma once
#include <iostream>

#include <memory>
struct HotDrink{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};
