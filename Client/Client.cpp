#include "Client.h"
#include <iostream>
#include "Logger.h"
#include "FileUtils.h"
#include "ProcessUtils.h"
#include "TCPSession.h"
using namespace NetworkUtils;

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
m_ioService(io_service)
{

}

int main(int argc, char* argv[])
{
    try
    {
        LOG_INIT();


        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        std::shared_ptr<boost::asio::io_service> ioService;
        ioService.reset(new boost::asio::io_service);
        

        tcp::resolver resolver(*ioService);
        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
        std::shared_ptr<Client> c = std::make_shared<Client>(*ioService, endpoint_iterator);

        auto session = std::make_shared<Network::TCPSession>(1, *ioService);
        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::MessageType::PING);
        std::cout << "Sending ping" << std::endl;
        


        std::thread t([&ioService]() {ioService->run();});
        t.join();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    system("pause");
    return 0;
}