#ifndef SHARED_HPP
#define SHARED_HPP

#include <cstdint>
#include <unordered_map>


/*
* The funciton which determines the mothod to calulate the probability of a value being in a triangular fuzzy set.
*/

inline float triangular(float x, float a, float b, float c) 
{
    if (x <= a || x >= c) return 0.0f;
    else if (x == b) return 1.0f;
    else if (x < b) return (x - a) / (b - a);
    else return (c - x) / (c - b);
}

inline float calcProbability(float value, const std::array<uint8_t, 3>& range) 
{
    if (value < range[0] || value > range[2]) return 0.0f;
    return triangular(static_cast<float>(value), static_cast<float>(range[0]), static_cast<float>(range[1]), static_cast<float>(range[2]));
}


/*
* Velocity, EngineRpm ThrottleLevel and Gear structures are helpers to clearly get probabilities for Fuzzy Logic rules.
*/

struct Velocity
{
    enum class VelocityLevel 
    {
        VERY_LOW,
        LOW,
        MEDIUM,
        HIGH,
        VERY_HIGH
    };

    inline static const std::unordered_map<VelocityLevel, std::array<uint8_t, 3>> velocityRanges = {
        {VelocityLevel::VERY_LOW, {0, 0, 20}},
        {VelocityLevel::LOW, {10, 30, 50}},
        {VelocityLevel::MEDIUM, {40, 60, 80}},
        {VelocityLevel::HIGH, {70, 90, 120}},
        {VelocityLevel::VERY_HIGH, {100, 120, 255}}
    };
};

struct EngineRpm
{
    enum class RpmLevel 
    {
        LOW,
        MEDIUM,
        HIGH
    };

    inline static const std::unordered_map<RpmLevel, std::array<uint16_t, 3>> rpmRanges = {
        {RpmLevel::LOW, {0, 1500, 2500}},
        {RpmLevel::MEDIUM, {2000, 3000, 4000}},
        {RpmLevel::HIGH, {3500, 4500, 6000}}
    };
};

struct ThrottleLevel
{
    enum class ThrottleLevelEnum 
    {
        LOW,
        MEDIUM,
        HIGH
    };

    inline static const std::unordered_map<ThrottleLevelEnum, std::array<uint8_t, 3>> throttleRanges = {
        {ThrottleLevelEnum::LOW, {0, 30, 50}},
        {ThrottleLevelEnum::MEDIUM, {40, 60, 80}},
        {ThrottleLevelEnum::HIGH, {70, 90, 100}}
    };
};

struct Gear
{
    enum class GearLevel
    {
        START,
        LOW,
        MEDIUM,
        HIGH
    };

    inline static const std::unordered_map<GearLevel, std::array<uint8_t, 3>> gearRanges = {
        {GearLevel::START, {0, 0, 2}},
        {GearLevel::LOW, {0, 2, 4}},
        {GearLevel::MEDIUM, {2, 4, 6}},
        {GearLevel::HIGH, {4, 6, 7}}
    };
};

#endif
