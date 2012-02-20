#ifndef CONNECTIONTCP_H_INCLUDED
#define CONNECTIONTCP_H_INCLUDED

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <iterator>
#include <string>

/**
* La classe ConnectionTCP permet la creation d'un objet par connexion TCP . Celui-ci contiendra la socket ainsi que les méthodes pour lire les messages envoyés par les clients.
* Cette classe hérite de la classe enable_share_from_this qui permet d'ajouter à l'objet un pointer qui contient sa propre adresse.
* @author ECHOES Technologies (RHI)
* @date 2012-02-19
*/

using boost::asio::ip::tcp;

class ConnectionTCP : public boost::enable_shared_from_this<ConnectionTCP>
{
    public:
        /**
        constructeur de la classe ConnectionTCP
        * @param io_service : l'objet io_service est pièce centrale de boost (coeur de la bibliothèque boost)
        */
        ConnectionTCP(boost::asio::io_service& io_service);

        /**
        méthode statique qui créé un objet de type ConnectionTCP
        * @param ioservice : l'ioservice instancié
        * @return pointer : un pointeur vers l'objet créé
        */
        typedef boost::shared_ptr<ConnectionTCP> pointer;
        static pointer create(boost::asio::io_service& ios);

        /**
        méthode qui retourne le socket
        * @return socket
        */
        tcp::socket& socket();

        /**
        Méthode qui accueille les clients et leur envoi un message d'accueil
        */
    //    void start();

        /**
        Méthode qui lit les messages sur la socket et les met dans un buffer. Si au bout de 5sec le client n'a rien envoyé on ferme la connexion.
        */
        void do_read();

    private:
        tcp::socket m_socket;
     //   std::string m_message;
        boost::array<char, 128> m_buffer;
        boost::asio::deadline_timer m_timer;

        /**
        Méthode de callback en ecriture
        */
     //   void handle_write(const boost::system::error_code& error);

        /**
        Méthode de callback en lecture
        */
        void handle_read(const boost::system::error_code& error);

        /**
        Méthode qui ferme le socket
        */
        void close();
};
#endif // CONNECTIONTCP_H_INCLUDED


