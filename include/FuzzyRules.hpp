#ifndef FUZZY_RULES_HPP
#define FUZZY_RULES_HPP

#include <unordered_map>
#include <tuple>
#include "FuzzyHelpers.hpp"


/*
* Key concept in rules:
* 1. When the throttle level is high or very high, we can assume that the driver wants to dynamicly accelerate, 
*    so we should not shift to a higher gear, myabe shift to a lower gear, especially when engine RPM is low.
*/

/*
* The rules:
*   | Velocity   | Engine RPM      | Throttle Level  | Gear
*-----------------------------------------------------------
* 1 | Very Low   | Low/Medium/High | Low/Medium/High | Start
* 2 | Low        | Low/Medium      | Low/Medium/High | Low
* 3 | Low        | High            | Low/Medium/High | Medium     -> want sailing -> shift up gear
* 4 | Medium     | Low             | High            | Low        -> dynamic acceleration -> shift down gear
* 5 | Medium     | Low/Medium      | Low/Medium      | Medium
* 6 | Medium     | Medium          | High            | Medium     
* 7 | Medium     | High            | Low/Medium/High | High       -> want sailing -> shift up gear
* 8 | High       | Low             | High            | Medium     -> dynamic acceleration -> shift down gear
* 9 | High       | Medium/High     | Low/Medium/High | High       -> despite possiblity of high RPM, we wish to shift up, but its last gear
* 10| High       | Low             | Low/Medium      | High        
*/

struct FuzzyRules
{
    inline static const std::unordered_map<std::tuple<Velocity::level, EngineRpm::level, ThrottleLevel::level>, Gear::level> rules = [] () {
        std::unordered_map<std::tuple<Velocity::level, EngineRpm::level, ThrottleLevel::level>, Gear::level> temp;
      
        for (auto v : {Velocity::level::VERY_LOW, Velocity::level::LOW, Velocity::level::MEDIUM, Velocity::level::HIGH, Velocity::level::VERY_HIGH}) 
        {
            for (auto r : {EngineRpm::level::LOW, EngineRpm::level::MEDIUM, EngineRpm::level::HIGH}) 
            {
                for (auto t : {ThrottleLevel::level::LOW, ThrottleLevel::level::MEDIUM, ThrottleLevel::level::HIGH}) 
                {
                    // 1
                    if (v == Velocity::level::VERY_LOW && 
                        (r == EngineRpm::level::LOW || r == EngineRpm::level::MEDIUM || r == EngineRpm::level::HIGH) && 
                        (t == ThrottleLevel::level::LOW || t == ThrottleLevel::level::MEDIUM || t == ThrottleLevel::level::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::START;
                    }
                    // 2
                    else if ((v == Velocity::level::LOW || v == Velocity::level::MEDIUM) && 
                    (r == EngineRpm::level::LOW || r == EngineRpm::level::MEDIUM || r == EngineRpm::level::HIGH) && 
                    (t == ThrottleLevel::level::LOW || t == ThrottleLevel::level::MEDIUM || t == ThrottleLevel::level::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::LOW;
                    }
                    // 3
                    else if (v == Velocity::level::LOW && 
                    (r == EngineRpm::level::LOW || r == EngineRpm::level::MEDIUM || r == EngineRpm::level::HIGH) && 
                    (t == ThrottleLevel::level::LOW || t == ThrottleLevel::level::MEDIUM || t == ThrottleLevel::level::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::MEDIUM;
                    }
                    // 4
                    else if (v == Velocity::level::MEDIUM && 
                             r == EngineRpm::level::LOW && 
                             t == ThrottleLevel::level::HIGH)
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::LOW;
                    }
                    // 5 and 6
                    else if (v == Velocity::level::MEDIUM && 
                             (r == EngineRpm::level::LOW || r == EngineRpm::level::MEDIUM) && 
                             (t == ThrottleLevel::level::LOW || t == ThrottleLevel::level::MEDIUM || t == ThrottleLevel::level::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::MEDIUM;
                    }
                    // 7
                    else if (v == Velocity::level::MEDIUM && 
                             r == EngineRpm::level::HIGH && 
                             (t == ThrottleLevel::level::LOW || t == ThrottleLevel::level::MEDIUM || t == ThrottleLevel::level::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::HIGH;
                    }
                    // 8
                    else if (v == Velocity::level::HIGH && 
                             r == EngineRpm::level::LOW && 
                             t == ThrottleLevel::level::HIGH)
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::MEDIUM;
                    }
                    // 9 and 10
                    else if (v == Velocity::level::HIGH && 
                             (r == EngineRpm::level::MEDIUM || r == EngineRpm::level::HIGH || r == EngineRpm::level::LOW) && 
                             (t == ThrottleLevel::level::LOW || t == ThrottleLevel::level::MEDIUM || t == ThrottleLevel::level::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::level::HIGH;
                    }
                }
            }
        }

        return temp;
    }();
};


#endif
