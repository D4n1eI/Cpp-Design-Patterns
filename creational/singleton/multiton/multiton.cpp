#include <map>
#include <memory>
#include <iostream>
using namespace std;

enum class Importance
{
    Primary,
    Secondary,
    Tertiary
};

template <typename T, typename Key = std::string>
class Multiton
{
public:
    static shared_ptr<T> get(const Key &key)
    {
        if (const auto it = instances.find(key);
            it != instances.end())
        {
            return it->second;
        }
        auto instance = make_shared<T>();
        instances[key] = instance;
        return instance;
    }

protected:
    Multiton() = default;
    virtual ~Multiton() = default;

private:
    static map<Key, shared_ptr<T>> instances;
};


class Printer{
    public:
    Printer(){
        ++Printer::totalInstancesCount;
        cout << "A total of "<<Printer::totalInstancesCount<< " instances created so far.";
    }
    private:
    static int totalInstancesCount;
};


int Printer::totalInstancesCount = 0;
template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;




int main(){

    typedef Multiton<Printer,Importance> mt;

    auto main = mt::get(Importance::Primary);
    auto aux = mt::get(Importance::Secondary);
    auto aux2 = mt::get(Importance::Tertiary);

    return 0;
}