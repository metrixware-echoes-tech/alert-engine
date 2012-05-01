#include "MessageManager.h"
#include <string>
#include "Message.h"

MessageManager::MessageManager(ConnectionTCP::ptrConnectionTCP mmPtrConnectionTCP):
mPtrConnection(mmPtrConnectionTCP)
{
    std::cout << "starting reception of sensor messages" << std::endl;
}
    
void MessageManager::waitForDatas()
{
    //on lance l'écoute d'événements
//    mPtrConnection->async_read(mMessage,
//                                 boost::bind(
//                                             &MessageManager::handleWaitForDatas,
//                                             shared_from_this(),
//                                             boost::asio::placeholders::error
//                                             )
//                                 );
}

void MessageManager::handleWaitForDatas(const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << " message recu " << std::endl;
        waitForDatas();
    }
}