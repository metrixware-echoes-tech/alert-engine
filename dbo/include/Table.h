#ifndef TABLE_H
#define TABLE_H

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>


class Table //classe abstraite
{
    public:
        Table();
        virtual ~Table();

        static std::string SEP;
        static std::string TABLE_PREFIX;
        static void setTrigram(std::string value);
        static std::string getTrigram();




    protected:
        std::string formatColumnName(std::string value);
        static std::string TRIGRAM;


    private:


};

template<typename T>
void QuiSuisJe(const T & x)
{
    std::cout << "Je suis un <inconnu>" << std::endl;
}

template<typename T>
void setFields(const T & t)
{
    const T a = t;

    std::cout << a.a << std::endl;
    std::cout << a.b << std::endl;

    /*
    for (T& i : a)
    {
        std::cout << i << std::endl;
    }
    */
}


#endif // TABLE_H
