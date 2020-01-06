#pragma once
#include <boost/thread.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include "picosha2.h"
#include "task_log.h"

namespace sha = picosha2;

namespace task {
int multithreadRandom(const int& a, const int& b) {
  static std::default_random_engine gen(static_cast<unsigned>(
      std::chrono::system_clock::now().time_since_epoch().count()));
  std::uniform_int_distribution<int> distribution(a, b);
  return distribution(gen);
}

bool isValid(const std::string& hash) {
  for (unsigned int i = 60; i < 64; i++) {
    if (hash[i] != '0') {
      return false;
    }
  }
  return true;
}

void threadWork() {
  while (true) {
    std::vector<unsigned char> data(4);
    for (auto& character : data) character = multithreadRandom(32, 126);

    const std::string hash = sha::hash256_hex_string(data);

    std::string data_s;
    for (const auto& ch : data) data_s += ch;

    task_log::logTrace(data_s, hash);
    if (isValid(hash)) task_log::logInfo(data_s, hash);
  }
}

void startThreads() {
  task_log::init();

  auto threadsCount = boost::thread::hardware_concurrency();
  boost::thread_group threads;

  for (unsigned int i = 0; i < threadsCount; i++) {
    threads.create_thread(threadWork);
  }

  threads.join_all();
}
}  // namespace task
