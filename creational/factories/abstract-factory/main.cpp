#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>
#include <math.h>
#include "hot-drink-factory.hpp"
#include "drink-factory.hpp"
using namespace std;



int main(){


    DrinkFactory df;
    auto c = df.make_drink("coffee");
    c->prepare(100);


    return 0;
}