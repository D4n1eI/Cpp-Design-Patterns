#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Relationship
{
    Parent,
    Child,
    Sibling
};

struct Person
{
    string name;
};


struct RelationshipBrowser{
    virtual vector<Person> findAllChildrenOf(string name) = 0;
};



struct Relationships : RelationshipBrowser// low-level module
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person &parent, const Person &child)
    {
        relations.push_back({parent, Relationship::Parent, child});
        relations.push_back({child, Relationship::Child, parent});
    }

    virtual vector<Person> findAllChildrenOf(string name) override{
        vector<Person> result;
        for (auto && [first,rel,second]:relations){
            if (first.name == name && rel == Relationship::Parent){
                cout << name << " is the parent of "<<second.name<<"\n";
            }
        }
        return result;
    }
};

struct Research
{ // high-level
    // Research(Relationships &relationships)
    // {
    //     auto & relations = relationships.relations;
    //     for ( auto &&[first,rel,second]:relations){
    //         if (first.name == "John" && rel==Relationship::Parent){
    //             cout <<"John has a child called "<<second.name<<"\n";
    //         }
    //     }
    // }
    Research(RelationshipBrowser & browser){
        for (auto& child : browser.findAllChildrenOf("John")){
            cout << "John has a child called "<<child.name<<"\n";
        }
    }
};

int main()
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);

    return 0;
}