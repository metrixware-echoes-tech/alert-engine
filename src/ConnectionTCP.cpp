#include "ConnectionTCP.h"

using boost::asio::ip::tcp;

//création d'un type de variable : prtConnectionTCP correspondant au pointeur d'un objet de type ConnectionTCP
typedef boost::shared_ptr<ConnectionTCP> ptrConnectionTCP;

// le constructeur créé le socket à base de l'ioservice
ConnectionTCP::ConnectionTCP(boost::asio::io_service& io_service)
    : m_socket(io_service)
{
}

ptrConnectionTCP ConnectionTCP::create(boost::asio::io_service& ios)
{
    return ptrConnectionTCP(new ConnectionTCP(ios));
}

tcp::socket& ConnectionTCP::socket()
{
    return m_socket;
}

ConnectionTCP::~ConnectionTCP()
{
        m_socket.close();
}