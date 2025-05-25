#ifndef FUZZY_INPUTS_HPP
#define FUZZY_INPUTS_HPP

#include <cstdint>
#include <unordered_map>
#include <array>


/*
* Velocity, EngineRpm ThrottleLevel and Gear structures are helpers to clearly get probabilities for Fuzzy Logic rules.
*/

struct Velocity
{
    enum class level
    {
        VERY_LOW,
        LOW,
        MEDIUM,
        HIGH,
        VERY_HIGH
    };

    inline static const std::unordered_map<level, std::array<uint8_t, 3>> ranges = {
        {level::VERY_LOW, {0, 0, 20}},
        {level::LOW, {0, 30, 50}},
        {level::MEDIUM, {20, 60, 100}},
        {level::HIGH, {60, 90, 140}},
        {level::VERY_HIGH, {100, 120, 200}}
    };
};

struct EngineRpm
{
    enum class level 
    {
        LOW,
        MEDIUM,
        HIGH
    };

    inline static const std::unordered_map<level, std::array<uint16_t, 3>> ranges = {
        {level::LOW, {0, 0, 2500}},
        {level::MEDIUM, {0, 3000, 5000}},
        {level::HIGH, {3000, 5000, 8000}}
    };
};

struct ThrottleLevel
{
    enum class level 
    {
        LOW,
        MEDIUM,
        HIGH
    };

    inline static const std::unordered_map<level, std::array<uint8_t, 3>> ranges = {
        {level::LOW, {0, 0, 40}},
        {level::MEDIUM, {0, 50, 80}},
        {level::HIGH, {50, 100, 100}}
    };
};

struct Gear
{
    enum class level
    {
        START,
        LOW,
        MEDIUM,
        HIGH
    };

    inline static const std::unordered_map<level, std::array<uint8_t, 3>> ranges = {
        {level::START, {1, 1, 2}},
        {level::LOW, {1, 2, 4}},
        {level::MEDIUM, {2, 4, 6}},
        {level::HIGH, {4, 6, 7}}
    };
};


#endif