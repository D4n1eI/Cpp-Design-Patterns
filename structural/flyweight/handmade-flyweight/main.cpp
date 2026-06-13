#include <iostream>
#include <boost/bimap.hpp>

typedef u_int32_t key;

struct User
{
    User(const std::string &first_name, const std::string &last_name)
        : first_name_id{add(first_name)},
          last_name_id{add(last_name)}
    {
    }

    const std::string &get_first_name() const
    {
        return names.left.find(first_name_id)->second;
    }

    const std::string &get_last_name() const
    {
        return names.left.find(last_name_id)->second;
    }

protected:
    key first_name_id;
    key last_name_id;

    static boost::bimap<key, std::string> names;
    static key seed;

    static key add(const std::string &s)
    {
        auto it = names.right.find(s);
        if (it == names.right.end())
        {
            key id = ++seed;
            names.insert({id, s});
            return id;
        }
        return it->second;
    }
};

key User::seed{0};
boost::bimap<key, std::string> User::names{};

std::ostream &operator<<(std::ostream &os, const User &user)
{
    os << "First name: " << user.get_first_name() << " Last Name: " << user.get_last_name();
    return os;
}

int main()
{
    User user1{"John","Smith"};
    User user2{"Jane","Smith"};

    std::cout << user1 << '\n';
    std::cout << user2 << '\n';

    return 0;
}