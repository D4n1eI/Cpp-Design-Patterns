
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>    


using namespace std;

struct Token
{
    enum Type
    {
        integer,
        plus,
        minus,
        lparen,
        rparen
    } type;
    string text;

    Token(Type &type, string &text) : type{type}, text{text}
    {
    }

    friend ostream &operator<<(ostream &os, Token &token)
    {
        os << " " << token.text << " ";
        return os;
    }
};

vector<Token> lex(const string &input)
{
    vector<Token> result;
    for (int i = 0; i < input.size(); i++)
    {
        switch (input.at(i))
        {
        case '+':
            result.emplace_back(Token::plus, "+");
            break;
        case '-':
            result.emplace_back(Token::minus, "-");
            break;

        case '(':
            result.emplace_back(Token::lparen, "-");
            break;
        case ')':
            result.emplace_back(Token::rparen, "-");
            break;
        default:
            ostringstream buffer;
            buffer << input.at(i);
            for ( int j = i+1 ; i < input.size(); j++){
                if (isdigit(input[j])){
                    buffer<<input[j];
                    ++i;
                }
                else{
                    result.emplace_back(Token::integer,buffer.str());
                    break;
                }
            }
            break;
        }
    }
    return result;
}

int main()
{
    string input{"(13-4)-(14+1)"};

    auto tokens = lex(input);
    for (auto&token:tokens){
        cout << token <<" ";
    }
    return 0;
}