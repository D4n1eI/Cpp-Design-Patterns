#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Expression
{
    virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double value) : value{value}
    {
    }

};

struct AdditionExpression : Expression
{
    Expression *left;
    Expression *right;

    AdditionExpression(Expression *left, Expression *right) : left{left}, right{right}
    {
    }

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

};

struct ExpressionPrinter
{
    std::ostringstream oss;

    void print(Expression *e)
    {
        if (auto de = dynamic_cast<DoubleExpression *>(e))
        {
            oss << de->value;
        }
        else if (auto ae = dynamic_cast<AdditionExpression *>(e))
        {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }
    std::string str() const
    {
        return oss.str();
    }
};
int main()
{
    auto e = new AdditionExpression{new DoubleExpression{1}, new AdditionExpression{
                                                                 new DoubleExpression{2}, new DoubleExpression{3}}};

    // std::ostringstream oss;

    // e->print(oss);
    // std::cout << oss.str() << std::endl;

    ExpressionPrinter ep;
    ep.print(e);
    std::cout << ep.str() << std::endl; 
    delete e;
    return 0;
}