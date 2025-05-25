#ifndef SHARED_HPP
#define SHARED_HPP

#include <cstdint>
#include <unordered_map>
#include "FuzzyInputs.hpp"
#include <tuple>


// have to add hashing for std::tuple to use it as a key in unordered_map
namespace std {
    template<>
    struct hash<std::tuple<Velocity::level, EngineRpm::level, ThrottleLevel::level>> {
        std::size_t operator()(const std::tuple<Velocity::level, EngineRpm::level, ThrottleLevel::level>& t) const noexcept {
            auto h1 = std::hash<int>{}(static_cast<int>(std::get<0>(t)));
            auto h2 = std::hash<int>{}(static_cast<int>(std::get<1>(t)));
            auto h3 = std::hash<int>{}(static_cast<int>(std::get<2>(t)));
            return h1 ^ (h2 << 1) ^ (h3 << 2); // proste mieszanie bitów
        }
    };
}


/*
* The funciton which determines the mothod to calulate the probability of a value being in a triangular fuzzy set.
*/

inline float triangular(float x, float a, float b, float c) 
{
    if (x < a || x > c) return 0.0f;
    else if (x == b) return 1.0f;
    else if (x < b) return (x - a) / (b - a);
    else return (c - x) / (c - b);
}


// already returns only probabilities over 0
// The probabilites equals 0 does not matter, because they are not used in the rules

template<class T>
inline std::unordered_map<typename T::level, float> calcProbabilities(float value) 
{
    std::unordered_map<typename T::level, float> probabilities;
    for (auto& [key, range] : T::ranges) 
    {
        float prob = triangular(value, static_cast<float>(range[0]), static_cast<float>(range[1]), static_cast<float>(range[2]));
        if (prob > 0.0f) 
        {
            probabilities[key] = prob;
        }
    }
    return probabilities;
}

// Function for calculate the gravity center of a fuzzy set
// weighted average - centroid of peaks - approximate method

inline float defuzzifyWeightedAverage(const std::unordered_map<Gear::level, float>& memberships, const std::unordered_map<Gear::level, std::array<uint8_t, 3>>& ranges) {
    float numerator = 0.0f;
    float denominator = 0.0f;

    for (const auto& [label, weight] : memberships) 
    {
        float peak = ranges.at(label)[1];
        numerator += peak * weight;
        denominator += weight;
    }

    if (denominator == 0.0f) return 0.0f;
    return numerator / denominator;
}

#endif
