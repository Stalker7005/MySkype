#include "Client.h"

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
io_service(io_service),
socket(io_service)
{
    DoConnect(endpointIterator);
}

void Client::Write(const NetworkUtils::ChatMessage& msg)
{
    auto handler = [this, msg]()
    {
        bool writeInProgress = !outputMessages.empty();
        outputMessages.push_back(msg);
        if (!writeInProgress)
        {
            DoWrite();
        }
    };

    io_service.post(handler);
}

void Client::Close()
{
    io_service.post([this]() { socket.close(); });
}

void Client::DoConnect(tcp::resolver::iterator endpoint_iterator)
{
    boost::asio::async_connect(socket, endpoint_iterator,
        [this](boost::system::error_code ec, tcp::resolver::iterator)
    {
        if (!ec)
        {
            DoReadHeader();
        }
    });
}

void Client::DoReadHeader()
{
    boost::asio::async_read(socket,
        boost::asio::buffer(read_msg_.data(), NetworkUtils::ChatMessage::header_length),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && read_msg_.decode_header())
        {
            DoReadBody();
        }
        else
        {
            socket.close();
        }
    });

}

void Client::DoReadBody()
{
    boost::asio::async_read(socket,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";
            DoReadHeader();
        }
        else
        {
            socket.close();
        }
    });
}

void Client::DoWrite()
{
    boost::asio::async_write(socket,
        boost::asio::buffer(outputMessages.front().data(),
            outputMessages.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            outputMessages.pop_front();
            if (!outputMessages.empty())
            {
                DoWrite();
            }
        }
        else
        {
            socket.close();
        }
    });
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
        Client c(io_service, endpoint_iterator);

        std::thread t([&io_service]() { io_service.run(); });

        char line[NetworkUtils::ChatMessage::max_body_length + 1];
        while (std::cin.getline(line, NetworkUtils::ChatMessage::max_body_length + 1))
        {
            NetworkUtils::ChatMessage msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.Write(msg);
        }

        c.Close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}