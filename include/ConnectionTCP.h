/**
 * La classe ConnectionTCP permet la creation d'un objet par connexion TCP . Celui-ci contiendra la socket ainsi que les
 * méthodes pour lire les messages envoyés par les clients.
 * Cette classe hérite de la classe enable_share_from_this qui permet d'ajouter à l'objet un pointeur qui contient 
 * l'adresse de l'objet lui même
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-04-21
 */

#ifndef CONNECTIONTCP_H
#define CONNECTIONTCP_H

#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/tuple/tuple.hpp>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using boost::asio::ip::tcp;

class ConnectionTCP : public boost::enable_shared_from_this<ConnectionTCP>
{
    public:
        
        //création d'un type de variable :connectionTCP_ptr correspondant au pointeur d'un objet de type ConnectionTCP
        typedef boost::shared_ptr<ConnectionTCP> ptrConnectionTCP;
        
        /**
         * Constructeur de la classe ConnectionTCP
         * @param io_service l'objet io_service est pièce centrale de boost (coeur de la bibliothèque boost)
         */
        ConnectionTCP(boost::asio::io_service& io_service);

        /**
         * Méthode statique qui créé un objet de type ConnectionTCP
         * @param ioservice          l'ioservice instancié
         * @return ptrConnectionTCP un pointeur vers l'objet créé cf typedef en bas
         */   
        static ptrConnectionTCP create(boost::asio::io_service& ios);

        /**
         * Méthode qui retourne le socket tout simplement
         * @return socket
         */
        tcp::socket& socket();

        /**
         * Méthode qui fait la lecture asynchrone sur le socket, utilisation de template afin de ne pas dépendre du type
         *  de données à recevoir et du handler à appeler
         * @param const T& t type de donnée reçues
         * @param Handler    méthode à appeler au déclenchement de la lecture asynchrone via bind
         */
        template <typename T, typename Handler>
        void async_read(T& t, Handler handler)
        {
            // On récupère le header
            void (ConnectionTCP::*f)( const boost::system::error_code&, T&, boost::tuple<Handler>) = &ConnectionTCP::handle_read_header<T, Handler>;
            boost::asio::async_read(
                                    m_socket,
                                    boost::asio::buffer(m_in_header),
                                    boost::bind(
                                                f,
                                                this,
                                                boost::asio::placeholders::error,
                                                boost::ref(t),
                                                boost::make_tuple(handler)
                                                )
                                    );
        }

        /**
         * méthode qui vérifie le header et lance la dé sérialisation des données via "handle_read_data"
         * @param const error_code code d'erreur en cas de soucis
         * @param const T& t       type de données gérer
         * @param Handler          méthode à appeler au déclenchement
         */
        template <typename T, typename Handler>
        void handle_read_header(const boost::system::error_code& e, T& t, boost::tuple<Handler> handler)
        {
            if(e)
            {
                //comm à revoir après comprehension
                boost::get<0>(handler)(e);
            }
            else
            {
                //on formate un input stream comme le header, composé de char et du contenu de m_in_header sur la bonne
                //taille (header_length)
                std::istringstream stream_header_in(std::string(m_in_header, header_length));
                //on initialise une variable pour stocker la taille du message en hexa
                std::size_t m_in_datasize = 0;
                //on teste bien que la taille que l'on met dans m_in_datasize est non nulle, si c'est nul on informe que
                //le header est non valide
                if (!(stream_header_in >> std::hex >> m_in_datasize))
                {
                    boost::system::error_code error(boost::asio::error::invalid_argument);
                    boost::get<0>(handler)(error);
                    return;
                }
                //on récupère les données maintenant

                //on resize notre char de récupération des données en fonction de la taille du header récupérée
                m_in_data.resize(m_in_datasize);
                //ligne non comprise, mais appelà handle read data
                void (ConnectionTCP::*f) (const boost::system::error_code&, T&, boost::tuple<Handler>) = &ConnectionTCP::handle_read_data<T, Handler>;

                //on ré écoute
                boost::asio::async_read(
                                        m_socket,
                                        boost::asio::buffer(m_in_data),
                                        boost::bind(f,this,boost::asio::placeholders::error, boost::ref(t), handler)
                                        );
            }
        }

        /**
         * méthode qui désérialise les données utiles recues
         * @param error_code code d'erreur en cas de soucis
         * @param const T& t type de données à désérialiser
         * @param Handler    méthode à appeler au déclenchement
         */
        template <typename T, typename Handler>
        void handle_read_data(const boost::system::error_code& e, T& t, boost::tuple<Handler> handler)
        {
            if(e)
            {
                //comm à revoir après comprehension
                boost::get<0>(handler)(e);
            }
            else
            {
                try
                {
                    //on met dans une string les données du string de reception en rapport avec sa taille
                    std::string archive_data(&m_in_data[0], m_in_data.size());
                    //on créer un flux texte d'entrée pour les datas et on met archive_data dans stream_data_in
                    std::istringstream stream_data_in(archive_data);
                    //on applique le désarchivage du flux texte
                    boost::archive::text_iarchive archive(stream_data_in);
                    //on rempli le buffer avec l'archive désérialisée
                    archive >> t;
                }
                catch (std::exception& e)
                {
                    //en cas d'echec
                    boost::system::error_code error(boost::asio::error::invalid_argument);
                    boost::get<0>(handler)(error);
                    return;
                }
                // On informe l'appelant que tout s'est bien passé     
                //comm à revoir après comprehension
                boost::get<0>(handler)(e);
            }
        }

        /**
         *destructeur
         */
        virtual ~ConnectionTCP();

    private:
        //socket TCP
        tcp::socket m_socket;
        //taille du header
        enum { header_length = 8 };
        //chaine de caractères du header à envoyer
        std::string m_out_header;
        //chaine de caractères du message à envoyer
        std::string m_out_data;
        //chaine de caractères du header à recevoir
        char m_in_header[header_length];
        //vecteur de type char du message à recevoir (retaillé en fonction du header)
        std::vector<char> m_in_data;
};
#endif // CONNECTIONTCP_H
