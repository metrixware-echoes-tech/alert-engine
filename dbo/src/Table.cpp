#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>
#include "Table.h"

using namespace std;

string Table::SEP = "_";
string Table::TABLE_PREFIX = "T";

Table::Table()
{
    //ctor
}

Table::~Table()
{
    //dtor
}


string Table::formatColumnName(string value)
{
    return TRIGRAM + SEP + value;
}

void Table::setTrigram(string value)
{
    Table::TRIGRAM = value;
}

string Table::getTrigram()
{
    return Table::TRIGRAM;
}
