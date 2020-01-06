#pragma once

#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;

namespace task_log {
std::string getId() {
  boost::thread::id th_id = boost::this_thread::get_id();
  std::stringstream id_str;
  id_str << th_id;

  return id_str.str();
}

void init() {
  auto sinkFile = boost::log::add_file_log(
      keywords::file_name = "logs/log_%N.log",
      keywords::rotation_size = 128 * 1024 * 1024,
      keywords::format =
          (expr::stream << expr::format_date_time<boost::posix_time::ptime>(
                               "TimeStamp", "%Y-%m-%d %H:%M:%S")
                        << ": <" << logging::trivial::severity << "> "
                        << expr::smessage));
  sinkFile->set_filter(logging::trivial::severity >= logging::trivial::trace);

  auto sinkConsole = logging::add_console_log(
      std::cout,
      keywords::format =
          (expr::stream << expr::format_date_time<boost::posix_time::ptime>(
                               "TimeStamp", "%Y-%m-%d %H:%M:%S")
                        << ": <" << logging::trivial::severity << "> "
                        << expr::smessage));
  sinkConsole->set_filter(logging::trivial::severity >= logging::trivial::info);

  logging::add_common_attributes();
}

void logTrace(const std::string& data, const std::string& hash) {
  std::string id = getId();

  BOOST_LOG_TRIVIAL(trace) << " THREAD " << std::setw(3) << "#" + id
                           << ": [INPUT DATA - " << std::setw(5) << data
                           << ", HASH - " << hash << "]\n";
}

void logInfo(const std::string& data, const std::string& hash) {
  std::string id = getId();

  BOOST_LOG_TRIVIAL(info) << "THREAD " << std::setw(3) << "#" + id
                          << ": [INPUT DATA - " << std::setw(5) << data
                          << ", HASH - " << hash << "]\n";
}
}  // namespace task_log
