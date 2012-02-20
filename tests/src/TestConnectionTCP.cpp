#include "TestConnectionTCP.h"
#include "UnitTest++.h"

namespace
{
    TEST(test1)
    {
        //pièce centrale de boost : l'io_service (coeur de la bibliothèque boost)
		boost::asio::io_service io_service;
		ConnectionTCP::pointer new_connection = ConnectionTCP::create(io_service);
		//ConnectionTCP::pointer new_connection2 = ConnectionTCP::create(io_service);

        CHECK_EQUAL(new_connection,new_connection->shared_from_this());
    }
}
