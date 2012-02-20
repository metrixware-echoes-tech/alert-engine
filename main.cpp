#include <iostream>
#include "ConnectionTCP.h"
#include "ServerTCP.h"

using namespace std;

int main()
{
	try
	{
		//pièce centrale de boost : l'io_service (coeur de la bibliothèque boost)
		boost::asio::io_service io_service;
		// Création d'un serveur TCP
		ServerTCP centralisateur(io_service, 7171);
		//execute les actions asynchrones. Cette méthode est bloquante
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
