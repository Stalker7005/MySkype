//#include "Client.h"
//#include <iostream>
//#include "Logger.h"
//#include "FileUtils.h"
//#include "ProcessUtils.h"
//
//using namespace NetworkUtils;
//
//Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpointIterator) : 
//m_io_service(io_service),
//m_socket(io_service),
//m_inMsgHeaderBlob(std::make_shared<Serialization::Blob>()),
//m_inMsgBodyBlob(std::make_shared<Serialization::Blob>()),
//m_outMsgBlob(std::make_shared<Serialization::Blob>()),
//m_serializer(std::make_unique<Serialization::Serializer>())
//{
//    DoConnect(endpointIterator);
//}
//
//void Client::Write(const std::shared_ptr<NetworkUtils::NetworkMessage> msg)
//{
//    m_io_service.post([this, msg]()
//    {
//        m_outputMessages.push_back(msg);
//        if (!m_outputMessages.empty())
//        {
//            DoWriteHeader();
//        }
//    });
//}
//
//void Client::CloseConnection()
//{
//    m_io_service.post([this]() { m_socket.close(); });
//}
//
//void Client::DoConnect(tcp::resolver::iterator endpoint_iterator)
//{
//    boost::asio::async_connect(m_socket, endpoint_iterator,
//        [this](boost::system::error_code ec, tcp::resolver::iterator)
//    {
//        if (!ec)
//        {
//            DoReadHeader();
//        }
//        else
//        {
//            LOG_ERR("Can't connect to server!");
//        }
//    });
//}
//
//void Client::DoReadHeader()
//{
//    auto headerSize = NetworkUtils::NetworkMessage::GetHeaderSize();
//    m_inMsgHeaderBlob->Reserve(headerSize);
//    auto self = shared_from_this();
//
//    boost::asio::async_read(m_socket,
//        boost::asio::buffer(m_inMsgHeaderBlob->GetData(), headerSize),
//        [this, self](boost::system::error_code ec, std::size_t /*length*/)
//    {
//        if (!ec)
//        {
//            auto headerInfo = NetworkMessage::ParseHeader(m_inMsgHeaderBlob->GetData());
//            //TODO add message handling
//            auto messageType = headerInfo.first;
//            auto messageSize = headerInfo.second;
//
//            DoReadBody(messageSize);
//        }
//        else
//        {
//            LOG_ERR("Can't read header");
//            CloseConnection();
//        }
//    });
//
//}
//
//void Client::DoReadBody(std::uint64_t bodySize)
//{
//    m_inMsgBodyBlob->Reserve(bodySize);
//    auto self = shared_from_this();
//
//    boost::asio::async_read(m_socket,
//        boost::asio::buffer(m_inMsgBodyBlob->GetData(), bodySize),
//        [this, self](boost::system::error_code ec, std::size_t /*length*/)
//    {
//        if (!ec)
//        {
//            OnPong();
//            DoReadHeader();
//        }
//        else
//        {
//            LOG_INFO("Can't read body!");
//            CloseConnection();
//        }
//    });
//}
//
//void Client::DoWriteHeader()
//{
//    auto outMsg = m_outputMessages.front();
//    m_serializer->Serialize(m_outMsgBlob, outMsg);
//    auto self = shared_from_this();
//    outMsg->SetMessageSize(m_outMsgBlob->Size());
//
//    boost::asio::async_write(m_socket,
//        boost::asio::buffer(outMsg->GetHeader(), outMsg->GetHeaderSize()),
//        [this, self](boost::system::error_code ec, std::size_t /*lenght*/)
//    {
//        if (!ec)
//        {
//            DoWriteBody();
//        }
//        else
//        {
//            LOG_ERR("Can't write header!");
//            CloseConnection();
//        }
//    }
//    );
//}
//
//void Client::DoWriteBody()
//{
//    auto self = shared_from_this();
//    boost::asio::async_write(m_socket,
//        boost::asio::buffer(m_outMsgBlob->GetData(), m_outMsgBlob->Size()),
//        [this, self](boost::system::error_code ec, std::size_t /*length*/)
//    {
//        if (!ec)
//        {
//            m_outputMessages.pop_front();
//            if (!m_outputMessages.empty())
//            {
//                DoWriteHeader();
//            }
//        }
//        else
//        {   
//            LOG_ERR("Can't write body!");
//            CloseConnection();
//        }
//    });
//}
//
//void Client::OnPong()
//{
//    auto message = NetworkMessage::Create(NetworkMessage::Type::PING);
//    std::cout << "Ping" << std::endl;
//    Write(message);
//}
//
//int main(int argc, char* argv[])
//{
//    try
//    {
//        LOG_INIT();
//
//
//        if (argc != 3)
//        {
//            std::cerr << "Usage: chat_client <host> <port>\n";
//            return 1;
//        }
//
//        boost::asio::io_service io_service;
//
//        tcp::resolver resolver(io_service);
//        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
//        std::shared_ptr<Client> c = std::make_shared<Client>(io_service, endpoint_iterator);
//
//        
//        auto message = NetworkUtils::NetworkMessage::Create(NetworkUtils::NetworkMessage::Type::PING);
//        std::cout << "Sending ping" << std::endl;
//        c->Write(message);
//
//        
//        std::thread t([&io_service]() {io_service.run();});
//        t.join();
//
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
//    system("pause");
//    return 0;
//}


#include <iostream>
#include <stdexcept>
#include <string>
#include "Logger.h"

#pragma comment(lib,"odbc32.lib")

#include "nanodbc.h"




int main()
{
    LOG_INIT();
    LOG_INFO("Hello World");
    LOG_ERR("Bla");

    setlocale(LC_ALL, "RUS");
    nanodbc::string_type connString = L"Driver={SQL Server};Server=IVAN-ой\\SQLEXPRESS;Database=Autolot";
    try
    {
        nanodbc::connection conn(connString, 5);
        if (conn.connected())
        {
            auto query = std::wstring(L"Select Make FROM Object;");
            nanodbc::result rows = nanodbc::execute(conn, query);
            for (auto i = 1; rows.next(); ++i)
            {
                std::wcout << i << " :" << rows.get<nanodbc::string_type>(0) << std::endl;
            }
        }
        else
        {
            std::wcout << L"Can't open db" << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        std::wcout << "Error:" << ex.what() << std::endl;
        system("pause");
    }
    
}