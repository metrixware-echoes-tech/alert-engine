#include "StructuredData.h"

int main()
{
    StructuredData a;
    std::string toto;
    toto.assign("[prop@5875 ver=1 probe=12][res2@5875 offset=15 81-4-15-6-2=\"543\" 8-4-51-6-1=\"54546\"][res1@5875 offset=75 844-4-5-456-2=\"129873\" 8-445-5-645-1=\"pojl\"]");
    a.unserializeStructuredData(toto); 
    return 0;
}
