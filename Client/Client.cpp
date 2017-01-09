#include "Client.h"
#include <iostream>
#include "Logger.h"
#include "FileUtils.h"
#include "ProcessUtils.h"

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

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
        std::shared_ptr<Client> c = std::make_shared<Client>(io_service, endpoint_iterator);

        
        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::MessageType::PING);
        std::cout << "Sending ping" << std::endl;
        c->Write(message);

        
        std::thread t([&io_service]() {io_service.run();});
        t.join();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    system("pause");
    return 0;
}