#ifndef SERVERTCP_CPP_INCLUDED
#define SERVERTCP_CPP_INCLUDED

#include "ServerTCP.h"

//le constructeur créé un objet de type acceptor avec comme paramètre l'io_service, l'IP de la machine et le port spécifié pour lancer le serveur et lance la méthode start_accept()
ServerTCP::ServerTCP(boost::asio::io_service& io_service, int port) : m_acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
    ServerTCP::start_accept();
}

void ServerTCP::start_accept()
{
    // on créé une nouvelle connexion en créant un objet new_connection avec en paramètre l'acceptor de l'objet serveur TCP
    ConnectionTCP::pointer new_connection = ConnectionTCP::create(m_acceptor.io_service());
    //on passe maintenant en attente de connexions client, tout est pret coté serveur, @param : notre socket et donner la fonction de callback pour ne pas être bloquant
    m_acceptor.async_accept
    (
        //new_connection est un pointeur d'ou ->
        new_connection->socket(),
        boost::bind(&ServerTCP::handle_accept, this, new_connection,boost::asio::placeholders::error)
    );
}


void  ServerTCP::handle_accept(ConnectionTCP::pointer new_connection,const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Reçu un client!" << std::endl;
        //lecture des messages recu
        new_connection->do_read();
        ServerTCP::start_accept();
    }
}

#endif // SERVERTCP_CPP_INCLUDED
