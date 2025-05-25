#include "GearShift.hpp"
#include "FuzzyHelpers.hpp"
#include "FuzzyInputs.hpp"

#include <iostream>

// 1. calculate the probabilities for velocity, engine RPM, and throttle level
// 2. choose only probabilities over 0
// 3. loop over whole rules that combines velocity, engine RPM, and throttle level nad get min
// 4. get min from every level of gear
// 5. take the max from the mins of evry kind of output (gear in this case)
// 6. calculate the gear by gravity center of the fuzzy set

float const GearShift::shift()
{
    std::unordered_map<Velocity::level, float> velocityProbabilities = calcProbabilities<Velocity>(velocity);
    std::unordered_map<EngineRpm::level, float> engineRpmProbabilities = calcProbabilities<EngineRpm>(engineRpm);
    std::unordered_map<ThrottleLevel::level, float> throttleLevelProbabilities = calcProbabilities<ThrottleLevel>(throttleLevel);
    std::cout << "Velocity probabilities: " << velocityProbabilities.size() << std::endl;
    for (const auto& [v, prob] : velocityProbabilities) 
    {
        std::cout << "Velocity: " << static_cast<int>(v) << ", Probability: " << prob << std::endl;
    }
    std::cout << "Engine RPM probabilities: " << engineRpmProbabilities.size() << std::endl;
    for (const auto& [r, prob] : engineRpmProbabilities) 
    {
        std::cout << "Engine RPM: " << static_cast<int>(r) << ", Probability: " << prob << std::endl;
    }
    std::cout << "Throttle Level probabilities: " << throttleLevelProbabilities.size() << std::endl;

    std::unordered_map<Gear::level, float> gearProbabilities;
    for (const auto& [v, vProb] : velocityProbabilities) 
    {
        for (const auto& [r, rProb] : engineRpmProbabilities) 
        {
            for (const auto& [t, tProb] : throttleLevelProbabilities) 
            {
                auto rule = std::make_tuple(v, r, t);
                if (FuzzyRules::rules.find(rule) != FuzzyRules::rules.end()) 
                {
                    std::cout << "FOUND" << std::endl;
                    Gear::level gear = FuzzyRules::rules.at(rule);
                    float probability = std::min({vProb, rProb, tProb});
                    if (gearProbabilities.find(gear) != gearProbabilities.end()) 
                    {
                        if (gearProbabilities[gear] < probability) 
                        {
                            gearProbabilities[gear] = probability;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else 
                    {
                        gearProbabilities[gear] = probability;
                    }
                }
            }
        }
    }

    std::cout << gearProbabilities.size() << std::endl;
    for (const auto& [gear, prob] : gearProbabilities) 
    {
        std::cout << "Gear: " << static_cast<int>(gear) << ", Probability: " << prob << std::endl;
    }
    return defuzzifyWeightedAverage(gearProbabilities, Gear::ranges);
}