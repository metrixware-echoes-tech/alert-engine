#include "ConnectionManager.h"

//le constructeur créé un objet de type acceptor avec comme paramètre l'io_service, l'IP de la machine et le port 
//spécifié pour lancer le serveur et lance la méthode start_accept()
ConnectionManager::ConnectionManager(boost::asio::io_service& io_service, const tcp::endpoint& endpoint):
m_acceptor(io_service,endpoint)
{
    ConnectionManager::acceptConnection();
}

ConnectionManager::~ConnectionManager()
{
}

void ConnectionManager::acceptConnection()
{
    // On créé une nouvelle connexion (un socket) en créant un objet new_connection avec en paramètre l'ioservice 
    //stocké dans l'acceptor de l'objet serveur TCP    
    ConnectionTCP::ptrConnectionTCP new_connection = ConnectionTCP::create(m_acceptor.io_service());
    
    // On passe maintenant en attente de connexions client, tout est pret coté serveur, 
    //@param : notre socket et la fonction de callback pour ne pas être bloquant
    m_acceptor.async_accept
    (
        //new_connection est un pointeur d'ou ->
        new_connection->socket(),
        boost::bind(&ConnectionManager::handleAcceptConnection, this, new_connection,boost::asio::placeholders::error)
    );
}


void  ConnectionManager::handleAcceptConnection(ConnectionTCP::ptrConnectionTCP new_connection,const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "New sensor connected" << std::endl;
        //lecture des messages recu       
    }

}