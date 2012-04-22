/** 
 * La classe ConnectionManager permet la créations des connexions TCP en fonctions des demandes de connexions qui sont 
 * faites par les clients. C'est cette fonction qui écoute sur le réseau sur le port indiqué.
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-04-22
 */

#ifndef CONNECTIONMANAGER_H
#define	CONNECTIONMANAGER_H

#include "ConnectionTCP.h"

class ConnectionManager {
public:
    
    /**
     * Constructeur de la classe ConnectionManager
     * @param io_service : l'objet io_service est pièce centrale de boost (coeur de la bibliothèque boost)
     * @param endpoint : objet qui contient les informations réseaux nécessaires pour ouvrir un serveur (IP,port)
     */
    ConnectionManager(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
    
    /**
     * Destructeur
     */
    virtual ~ConnectionManager();
 
private:
    
   /**
    * Création d'une connexion TCP et mise en attente de clients, execution du handler en cas de connexion
    */
   void acceptConnection();

    /**
     * Fonction de callback qui est appelée lorsqu'un client se connecte sur la socket initialisée
     * @param pointer : pointeur d'un objet de type ConnectionTCP
     * @param error_code : objet d'erreur boost
     */
   void handleAcceptConnection(ConnectionTCP::ptrConnectionTCP newConnection,const boost::system::error_code& error);
   
    
    //C'est l'objet qui permet d'accepter les connexions entrantes via la méthode async_accept(). 
    //il doit contenir, l'io_service, l'ip et le port à utiliser pour le serveur.
    boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif	/* CONNECTIONMANAGER_H */

