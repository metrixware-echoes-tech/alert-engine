#include <iostream>
#include "ConnectionTCP.h"
#include "ConnectionManager.h"

using namespace std;

//int main()
//{
//        try
//        {
//            //pièce centrale de boost : l'io_service (coeur de la bibliothèque boost)    
//            boost::asio::io_service io_service;
//            //création d'un endpoint avec l'ip d'écoute et le port d'écoute
//            tcp::endpoint endpoint(tcp::v4(), 7171);
//            
//            //a revoir
//            ConnectionManager mConnectionManager(io_service, endpoint);
//            
//            //execute les actions asynchrones. Cette méthode est bloquante
//            io_service.run();
//        }
//        catch (std::exception& e)
//        {
//                std::cerr << "Exception: " << e.what() << "\n";
//        }
//
//        return 0;
//}

//test serialisation
#include "Message.h"
//main test de la sérialisation
int main()
{
    Message mess1;
    std::string s;
    s.assign("[ids=\"1-2-1-2-4-2\" value=\"lkihazaz\"]");
    mess1.unserializeValue(s);

    return 0;
}