// Copyright 2018 devborz

#pragma once

#include <iostream>
#include <thread>
#include "picosha2.h"
#include "log.h"

using namespace picosha2;

bool isValid(const std::string& hash) {
    for(unsigned int i = 0; i < 32; i++) {
        if ((i < 28 && hash[i] == '0') || (i >= 28 && hash[i] != '0')) {
            return false;
        }
    }
    return true;
}

void calculateSHA(const unsigned int& threadNumber) {
    unsigned char ch1 = rand() % 94 + 32;
    unsigned char ch2 = rand() % 94 + 32;
    unsigned char ch3 = rand() % 94 + 32;
    unsigned char ch4 = rand() % 94 + 32;

    const std::vector<unsigned char> Data = {ch1, ch2, ch3, ch4};
    const std::string hash = hash256_hex_string(Data);

    std::string data;
    for(const auto& ch: Data)
        data += ch;

    logTrace(data, hash, threadNumber);
    if (isValid(hash))  logInfo(data, hash, threadNumber);
}

void begin() {
    auto threadsCount = std::thread::hardware_concurrency();
    std::cout << threadsCount;
    std::vector<std::thread> threads(threadsCount);
    for(unsigned int i = 0; i < threadsCount; i++) {
        threads[i] = std::thread(calculateSHA, i + 1);
    }
}
