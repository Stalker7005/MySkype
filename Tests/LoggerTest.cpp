
#include "catch.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include "Logger.h"

void LogInitThread()
{
    LOG_INIT(L"Test.log", true, Logger::LogLevel::ALL);

    for (int i = 0; i < 100000; ++i)
    {
        LOG_INFO("Hello I'am thred: %d", std::this_thread::get_id());
    }
    
}

TEST_CASE("LoggerTest")
{

    SECTION("Logger Concurency")
    {
        using namespace std::chrono_literals;
        /*for (int i = 0; i < 10; ++i)
        {*/
            auto t1 = std::async(std::launch::deferred, &LogInitThread);
            //std::thread t2(&LogInitThread);
            //std::thread t3(&LogInitThread);
            //std::thread t4(&LogInitThread);
            //std::thread t5(&LogInitThread);
            //std::thread t6(&LogInitThread);
            //std::thread t7(&LogInitThread);

            std::this_thread::sleep_for(100ms);
            //t1.get();
            //t2.join();
            //t3.join();
            //t4.join();
            //t5.join();
            //t6.join();
            //t7.join();
        /*}*/
        

        getchar();
    }
}




