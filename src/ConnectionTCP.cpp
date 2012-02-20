#include "ConnectionTCP.h"

using boost::asio::ip::tcp;

// le constructeur créé le socket à base de l'ioservice et initialise un timer à 5 secondes.
ConnectionTCP::ConnectionTCP(boost::asio::io_service& io_service) : m_socket(io_service), m_timer(io_service, boost::posix_time::seconds(5))
{
}

tcp::socket& ConnectionTCP::socket()
{
    return m_socket;
}


typedef boost::shared_ptr<ConnectionTCP> pointer;
pointer ConnectionTCP::create(boost::asio::io_service& ios)
{
    return pointer(new ConnectionTCP(ios));
}
/*
void ConnectionTCP::start()
{
    m_message = "Bienvenue sur le serveur!";

    boost::asio::async_write
    (
        m_socket,
        boost::asio::buffer(m_message),
        boost::bind(&ConnectionTCP::handle_write, shared_from_this(), boost::asio::placeholders::error)
    );
}

void ConnectionTCP::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        ConnectionTCP::do_read();
    }
    else
    {
        std::cout << error.message() << std::endl;
    }
}
*/
void ConnectionTCP::do_read()
{
    // On lance une écoute
    boost::asio::async_read
    (
        m_socket,
        boost::asio::buffer(m_buffer),

        // shared_from_this correspond au pointeur hérité de la classe enable_share_from_this
        boost::bind(&ConnectionTCP::handle_read, shared_from_this(),boost::asio::placeholders::error)
    );
    // lancement du timer
    m_timer.expires_from_now(boost::posix_time::seconds(5));
    m_timer.async_wait(boost::bind(&ConnectionTCP::close, shared_from_this() ));
    copy(m_buffer.begin(),m_buffer.end(),std::ostream_iterator<char>(std::cout," "));
    std::cout << std::endl;
}

void ConnectionTCP::handle_read(const boost::system::error_code& error)
{
    if (!error)
    {
        // On réécoute
        do_read();
    }
    else
    {
        std::cout << error.message() << std::endl;
        close();
    }
}

void ConnectionTCP::close()
{
    m_socket.close();
    std::cout << "ferme" << std::endl;
}
