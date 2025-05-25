#include "GearShift.hpp"
#include "FuzzyHelpers.hpp"
#include "FuzzyInputs.hpp"

#include <iostream>
#include <algorithm>


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

    return defuzzifyWeightedAverage(gearProbabilities, Gear::ranges);
}
