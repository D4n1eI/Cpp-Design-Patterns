#include <iostream>

#include <string>

#include <sstream>

template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable &obj) = 0;
};

struct VisitorBase
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;
    virtual void accept(VisitorBase &obj)
    {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV *>(&obj))
            ev->visit(*this);
    }
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double value) : value{value}
    {
    }
    virtual void accept(VisitorBase &obj)
    {
        using DEV = Visitor<DoubleExpression>;
        if (auto ev = dynamic_cast<DEV *>(&obj))
            ev->visit(*this);
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *left, Expression *right) : left{left}, right{right} {}

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }
    virtual void accept(VisitorBase &obj)
    {
        using AEV = Visitor<AdditionExpression>;
        if (auto ev = dynamic_cast<AEV *>(&obj))
            ev->visit(*this);
    }
};

struct ExpressionPrinter : VisitorBase, Visitor<DoubleExpression>, Visitor<AdditionExpression>
{

    void visit(AdditionExpression &obj) override
    {
        oss << "(";
        obj.left->accept(*this);
        oss << "+";
        obj.right->accept(*this);
        oss << ")";
    }
    void visit(DoubleExpression &obj) override
    {
        oss << obj.value;
    }

    std::string str() const
    {
        return oss.str();
    }

private:
    std::ostringstream oss;
};

int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}}};

    ExpressionPrinter ep;
    ep.visit(*e);
    std::cout << ep.str() << std::endl;
}