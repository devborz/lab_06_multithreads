// Copyright 2018 devborz

#pragma once

#include <iostream>
#include "picosha2.h"
#include "log.h"
#include <chrono>
#include <random>

using namespace picosha2;

int _random(const int a, const int b)
{
    static std::default_random_engine gen(
        static_cast<unsigned>(
            std::chrono::system_clock::now().time_since_epoch().count()
        )
    );
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(gen);
}

bool isValid(const std::string& hash) {
    for(unsigned int i = 60; i < 64; i++) {
        if (hash[i] != '0') {
            return false;
        }
    }
    return true;
}

void calculateSHA() {
    unsigned int i = 0;
    while(true) {
        unsigned char ch1 = _random(32, 126);
        unsigned char ch2 = _random(32, 126);
        unsigned char ch3 = _random(32, 126);
        unsigned char ch4 = _random(32, 126);

        const std::vector<unsigned char> Data = {ch1, ch2, ch3, ch4};
        const std::string hash = hash256_hex_string(Data);

        std::string data;
        for(const auto& ch: Data)
            data += ch;

        logTrace(data, hash);
        if (isValid(hash))  logInfo(data, hash);
        i++;
    }
}

void begin() {
    auto threadsCount = boost::thread::hardware_concurrency();
    boost::thread threads[threadsCount];

    init();

    for(unsigned int i = 0; i < threadsCount; i++) {
        threads[i] = boost::thread(calculateSHA);
    }
    for(unsigned int i = 0; i < threadsCount; i++) {
        threads[i].join();
    }
}
