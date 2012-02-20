#ifndef SERVERTCP_H_INCLUDED
#define SERVERTCP_H_INCLUDED

#include "ConnectionTCP.h"

/**
* La classe ServerTCP permet la creation du serveur ainsi que la gestion des opérations asynchrones de connexion client.
* @author ECHOES Technologies (RHI)
* @date 2012-02-19
*/

class ServerTCP
{
public:
    /**
    constructeur de la classe ServeurTCP
    * @param io_service : l'objet io_service est pièce centrale de boost (coeur de la bibliothèque boost)
    * @param port : port d'écoute du serveur
    */
    ServerTCP(boost::asio::io_service& io_service, int port);

private:
    //objet qui permet d'accepter les connexions entrantes via la méthode async_accept(). il doit contenir, l'io_service, l'ip et le port à utiliser pour le serveur.
    tcp::acceptor m_acceptor;

    /**
    lancement de la méthode create() pour créer l'objet gérant la connexion avec en paramètre l'acceptor
    */
    void start_accept();

    /**
    fonction de callback qui est appelée lorsqu'un client se connecte sur la socket initialisée
    @param pointer : pointeur d'un objet de type ConnectionTCP
    @param error_code : objet d'erreur boost
    */
    void handle_accept(ConnectionTCP::pointer new_connection,const boost::system::error_code& error);
};
#endif // SERVERTCP_H_INCLUDED
