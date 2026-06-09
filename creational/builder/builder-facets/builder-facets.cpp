#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>
#include "person.hpp"
#include "person-builder.hpp"
#include "person-address-builder.hpp"
#include "person-job-builder.hpp"

using namespace std;

int main(){

    Person p = Person::create()
                .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
                .works().at("PragmaSoft").as_a("Consultant").earning(10e6);


    std::cout << p << std::endl;
    return 0;
}