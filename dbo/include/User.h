#ifndef USER_H
#define USER_H

#include <Table.h>

class User : public Table
{
private:

public:
    User();
    User(std::string name);
    virtual ~User();
    enum Role
    {
        Visitor = 0,
        Admin = 1,
        Alien = 42
    };

    std::string name;
    std::string password;
    Role        role;
    int         karma;

    void setName(std::string value);

    /*
    int myint[] = {1,2,3,4};
    for (int& i : myint)
    {
        cout << i << endl;
    }
    */

    template<class Action>
    void persist(Action& a)
    {
        std::string test[] = {"A","B","C"};
        for (std::string& i : test)
        {
            Wt::Dbo::field(a, name,     this->formatColumnName(i));
        }
        Wt::Dbo::field(a, name,     this->formatColumnName("NAME"));
        Wt::Dbo::field(a, password, this->formatColumnName("PASSWORD"));
        Wt::Dbo::field(a, role,     this->formatColumnName("ROLE"));
    }

    void test();
};

namespace Wt
{
    namespace Dbo
    {
        template<>
        struct dbo_traits<User> : public dbo_default_traits
        {
            static const char *surrogateIdField()
            {
                return "USR_ID";
            }
            static const char *versionField()
            {
                return 0;
            }
        };
    }
}


#endif // USER_H
