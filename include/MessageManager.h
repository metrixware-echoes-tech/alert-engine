/** 
 * La classe MessageManager la gestion des messages envoyés par les clients, elle remplie les structures serializables
 * afin de stocker les infos en base ensuite
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-04-22
 */

#ifndef MESSAGEMANAGER_H
#define	MESSAGEMANAGER_H

#include "ConnectionTCP.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Message.h"

class ConnectionManager;

class MessageManager : public boost::enable_shared_from_this<MessageManager> 
{
public:
    //création d'un type de variable :ptrMessageManager correspondant au pointeur 
    //d'un objet de type MessageManager
    typedef boost::shared_ptr<MessageManager> ptrMessageManager;    
    
    /**
     * Constructeur de la classe
     * @param la connexion TCP associée 
     */
    MessageManager(ConnectionTCP::ptrConnectionTCP mmPtrConnectionTCP);
    
    /**
     * Créateur d'un gestionnaire de messages et mise en attente de messages de la sonde
     * @param la connexion TCP associée à la session
     * @return un pointeur vers l'objet lui même
     */
     static ptrMessageManager create(ConnectionTCP::ptrConnectionTCP mmPtrConnectionTCP)
     {
        ptrMessageManager manager(new MessageManager(mmPtrConnectionTCP));
        manager->waitForDatas();
        return manager;
     }
    
    
    void waitForDatas();
    
    void handleWaitForDatas(const boost::system::error_code &error);
    
private:
    
    
   // Message mMessage;
    //pointeur vers la connexion TCP associée à la session de chat
    ConnectionTCP::ptrConnectionTCP mPtrConnection;
    
};

#endif	/* MESSAGEMANAGER_H */