#pragma once
#include <chrono>

namespace utils {
    float hireTimeInSeconds();
}

// Utils.cpp
#include "Utils.hpp"
#include <chrono>

float utils::hireTimeInSeconds() {
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - startTime;
    return elapsed.count();
}