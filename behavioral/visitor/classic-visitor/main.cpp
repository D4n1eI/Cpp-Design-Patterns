#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct DoubleExpression;
struct AdditionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;
    virtual void visit(SubtractionExpression *se) = 0;
};

struct ExpressionPrinter : ExpressionVisitor
{

    std::ostringstream oss;

    std::string str() const { return oss.str(); };
    void visit(AdditionExpression *de) override;
    void visit(DoubleExpression *ae) override;
    void visit(SubtractionExpression *se) override;
};

struct Expression
{
    virtual void accept(ExpressionVisitor *visitor) = 0;
};

struct ExpressionEvaluator : ExpressionVisitor
{
    double result;

    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubtractionExpression *se) override;
};
struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double value) : value{value}
    {
    }

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
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

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

struct SubtractionExpression : Expression
{
    Expression *left;
    Expression *right;

    SubtractionExpression(Expression *left, Expression *right) : left{left}, right{right}
    {
    }

    ~SubtractionExpression()
    {
        delete left;
        delete right;
    }

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

void ExpressionPrinter::visit(DoubleExpression *de)
{
    oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression *ae)
{
    bool need_braces = dynamic_cast<SubtractionExpression *>(ae->right);
    if (need_braces)
        oss << "(";
    ae->left->accept(this);
    oss << "+";
    ae->right->accept(this);
    if (need_braces)
        oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression *se)
{
    bool need_braces = dynamic_cast<SubtractionExpression *>(se->right);
    if (need_braces)
        oss << "(";
    se->left->accept(this);
    oss << "-";
    se->right->accept(this);
    if (need_braces)
        oss << ")";
}

int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new SubtractionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}}};

    ExpressionPrinter ep;
    ep.visit(e);
    std::cout << ep.str() << std::endl;

    ExpressionEvaluator ev;
    ev.visit(e);
    std::cout << ep.str()<<"="<<ev.result<<std::endl;
    return 0;
}

void ExpressionEvaluator::visit(DoubleExpression *de)
{
    result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression *ae)
{
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result+=temp;
}

void ExpressionEvaluator::visit(SubtractionExpression *se)
{
    se->left->accept(this);
    auto temp = result;
    se->right->accept(this);
    result-=temp;
}
