#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iomanip>
#include <iostream>
//namespace logging = boost::log;

void logTrace(const std::string& data, const std::string& hash,
        const unsigned int& threadNumber) {
    boost::log::add_file_log("log.log");

    BOOST_LOG_TRIVIAL(trace) << "THREAD " << std::setw(3)
    << "#" + std::to_string(threadNumber) << ": [INPUT DATA - " << std::setw(5)
    << data << ", HASH - " << hash << "]\n";

}

void logInfo(const std::string& data, const std::string& hash,
        const unsigned int& threadNumber) {
    boost::log::add_file_log("log.log");

    BOOST_LOG_TRIVIAL(info) << "THREAD " << std::setw(3)
    << "#" + std::to_string(threadNumber) << ": [INPUT DATA - " << std::setw(5)
    << data << ", HASH - " << hash << "]\n";

}
