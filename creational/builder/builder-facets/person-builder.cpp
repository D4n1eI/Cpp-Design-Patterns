#include "person-builder.hpp"
#include "person-address-builder.hpp"
#include "person-job-builder.hpp"

PersonBuilderBase::PersonBuilderBase(Person &person) : person{person} {}

PersonBuilder::PersonBuilder() : PersonBuilderBase{p} {}


PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{person};
}
PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder{person};
}