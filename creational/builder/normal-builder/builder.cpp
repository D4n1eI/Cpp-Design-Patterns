#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>

using namespace std;

struct HTMLBuilder;

class HTMLElement
{
    friend class HTMLBuilder;
    string name, text;
    vector<HTMLElement> elements;
    const size_t indent_size = 2;

    HTMLElement() {};
    HTMLElement(const string &name, const string &text) : name{name}, text{text} {};

public:
    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
        {
            oss << string(indent_size * (indent + 1), ' ') << text << endl;
        }

        for (const auto &e : elements)
        {
            oss << e.str(indent + 1);
        }

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static HTMLBuilder create(string root_name);
};

struct HTMLBuilder
{
    HTMLElement root;
    HTMLBuilder(string root_name)
    {
        root.name = root_name;
    }

    HTMLBuilder add_child(string child_name, string child_text)
    {
        HTMLElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    string str() const
    {
        return root.str();
    }
    HTMLElement build(){
        return root;
    }
    operator HTMLElement() const { return root; };
};

HTMLBuilder HTMLElement::create(string root_name)
{
    return HTMLBuilder{root_name};
}

int main()
{

    auto text = "Hello";

    string output{};
    output += "<p>";
    output += text;
    output += "</p>";

    cout << output << endl;

    string words[] = {"hello", "world"};

    ostringstream oss;
    oss << "<ul>";
    for (auto w : words)
    {
        oss << "  <li>" << w << "</li>";
    }
    oss << "</ul>";

    cout << oss.str() << endl;

    HTMLBuilder builder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world").add_child("p", "Fluent Builder");
    cout << builder.str();

    HTMLElement elem = HTMLElement::create("ul").add_child("", "");

    HTMLElement::create("").add_child("li","List").build();
    return 0;
}
