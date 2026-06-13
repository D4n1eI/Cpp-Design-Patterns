#include <string>
#include <iostream>

struct Pingable
{
    virtual std::wstring ping(const std::wstring& message) = 0;
    virtual ~Pingable() = default;
};

struct Pong : Pingable
{
    std::wstring ping(const std::wstring& message) override
    {
        return message + L"Pong";
    }
};


void tryit(Pingable&p){
    std::wcout<<p.ping(L"ping")<<"\n";
}


int main(){
    Pong pp;
    for ( size_t i = 0 ; i < 3 ; i++){
        tryit(pp);
    }
    return 0;
}