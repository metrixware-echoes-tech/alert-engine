#include "StructuredData.h"

int main()
{
    StructuredData a;
    std::string toto;
    toto.assign("[prop@5875 ver=1 probe=12][res2@5875 offset=15 8-4-5-6-2=\"543\" 8-4-5-6-1=\"54546\"][res1@5875 offset=15 8-4-5-6-2=\"543\" 8-4-5-6-1=\"54546\"]");
    a.unserializeStructuredData(toto);   
    return 0;
}