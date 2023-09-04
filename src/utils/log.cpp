#include "log.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include <iostream>
zrestlog::Log::Log()
{
    try 
    {
        logger = spdlog::basic_logger_mt("zrest", "zrestlog.txt");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}

std::shared_ptr<spdlog::logger> zrestlog::Log::getLogger(void)
{
    return logger;
}

static zrestlog::Log* gInstance=0;

zrestlog::Log* zrestlog::Log::getInstance(void)
{
    if(!gInstance)
    {
        gInstance = new Log();
    }
    return gInstance;
}