/** 
 * La classe SensorMessage expose le format des messages recus par les sondes
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-04-22
 */

#ifndef SENSORMESSAGE_H
#define	SENSORMESSAGE_H

#include <string>
#include <map>
#include <list>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>

class SensorMessage {
public:
    //
    //reprise code chatmessage
    //
        /**
        Méthode qui efface les chaines de caratères de l'objet message
        */
        void reset();

        //données d'un message
        //type d'évenement
        int m_type;
        //chaine de caractères du message
        std::string m_message;
        //login de l'emetteur
        std::string m_login;

        //méthode serialize pour créer des archives de messages sérialisée correctements
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar & m_type;
            ar & m_message;
            ar & m_login;
        }

        enum {
            NEW_MSG =0, //new message
            PERSON_LEFT = 1, //personn ayant quitté la room
            PERSON_CONNECTED = 2, // nouvelle personne connectée à la room
        };
};

#endif	/* SENSORMESSAGE_H */

