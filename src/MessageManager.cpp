#include "MessageManager.h"
#include <string>
#include "Message.h"

MessageManager::MessageManager(ConnectionTCP::ptrConnectionTCP mmPtrConnectionTCP):
mPtrConnection(mmPtrConnectionTCP)
{
    std::cout << "starting reception of sensor messages" << std::endl;
}

//test builder to use a MessageManager without networking system
MessageManager::MessageManager()
{
    //insert a network packet in the queue
    dataQueue.push("<165>1 2003-10-11T22:14:15Z mymachine.example.com echoes-alert-probe - 3216 - ID47 [offset=\"-1256\"][ids=\"1-2-1-2-4-2\" value=\"lkihazaz\"][ids=\"1-2-1-2-4-3\" value=\"lkihazaefzzefz\"][offset=\"-1256\"][ids=\"1-2-1-2-4-2\" value=\"lkihazaz\"]");
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