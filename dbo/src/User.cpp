#include "User.h"

using namespace std;

string Table::TRIGRAM = "USR";

template<typename T>
struct testStruct
{
    T a;
    string b;
};

User::User() : Table()
{

}


User::User(string name) : Table()
{
    this->setName(name);
    this->setTrigram("USR");
}

User::~User()
{
    //dtor
}

void User::setName(string value)
{
    this->name = value;
}

template<>
void QuiSuisJe<User>(const User & x)
{
    cout << "Je suis un <User>" << endl;
}

void User::test()
{
    string str("toto");
    QuiSuisJe(*this);
    QuiSuisJe(str); // "Je suis un <inconnu>"
    QuiSuisJe(1); // "Je suis un <int>"
    QuiSuisJe(1.23);

    testStruct<string> t1;
    t1.a = "toto";
    t1.b = "tata";

    testStruct<int> t2;
    t2.a = 42;
    t2.b = "titi";

    setFields(t1);
    setFields(t2);



}

