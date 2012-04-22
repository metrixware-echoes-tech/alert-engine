#include "ConnectionTCP.h"

using boost::asio::ip::tcp;

//création d'un type de variable : prtConnectionTCP correspondant au pointeur d'un objet de type ConnectionTCP
typedef boost::shared_ptr<ConnectionTCP> connectionTCP_ptr;

// le constructeur créé le socket à base de l'ioservice et renvoie un pointeur cf shared_ptr
ConnectionTCP::ConnectionTCP(boost::asio::io_service& io_service)
    : m_socket(io_service)
{
}

connectionTCP_ptr ConnectionTCP::create(boost::asio::io_service& ios)
{
    return connectionTCP_ptr(new ConnectionTCP(ios));
}

tcp::socket& ConnectionTCP::socket()
{
    return m_socket;
}

ConnectionTCP::~ConnectionTCP()
{
    //dtor
}