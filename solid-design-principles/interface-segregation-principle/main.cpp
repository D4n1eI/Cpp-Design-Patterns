#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Document;

// struct IMachine{
//     virtual void print(Document & doc)=0;
//     virtual void scan(Document & doc)=0;
//     virtual void fax(Document & doc)=0;
// };

// struct MFP : IMachine{
//     virtual void print(Document & doc)override{
//         //ok
//     }
//     virtual void scan(Document & doc)override{
//         //ok
//     }
//     virtual void fax(Document & doc)override{
//         //ok
//     }
// };

// struct Scanner : IMachine{
//     virtual void print(Document & doc)override{

//     }
//     virtual void scan(Document & doc)override{
//         //ok
//     }
//     virtual void fax(Document & doc)override{

//     }
// };

struct IPrint
{
    virtual void print(Document &doc) = 0;
};

struct IScan
{
    virtual void scan(Document &doc) = 0;
};

struct IFax
{
    virtual void fax(Document &doc) = 0;
};

struct Scanner : IScan
{
    virtual void scan(Document &doc) override
    {
        cout << "Scanning...";
    }
};

struct Printer : IPrint
{
    virtual void print(Document &doc) override
    {
        cout << "Printing...";
    }
};

struct IMachine : IPrint, IScan
{
};

struct Machine : IMachine
{
    IPrint &printer;
    IScan &scanner;

    Machine(IPrint printer, IScan scanner) : printer{printer}, scanner{scanner} {}


    virtual void print(Document &doc) override{
        printer.print(doc);
    }

    virtual void scan(Document &doc) override{
        scanner.scan(doc);
    }

};

int main()
{
    return 0;
}