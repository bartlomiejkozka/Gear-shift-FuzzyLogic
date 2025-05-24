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
    inline static const std::unordered_map<std::tuple<Velocity::VelocityLevel, EngineRpm::RpmLevel, ThrottleLevel::ThrottleLevelEnum>, Gear::GearLevel> rules = [] () {
        std::unordered_map<std::tuple<Velocity::VelocityLevel, EngineRpm::RpmLevel, ThrottleLevel::ThrottleLevelEnum>, Gear::GearLevel> temp;
      
        for (auto v : {Velocity::VelocityLevel::VERY_LOW, Velocity::VelocityLevel::LOW, Velocity::VelocityLevel::MEDIUM, Velocity::VelocityLevel::HIGH, Velocity::VelocityLevel::VERY_HIGH}) 
        {
            for (auto r : {EngineRpm::RpmLevel::LOW, EngineRpm::RpmLevel::MEDIUM, EngineRpm::RpmLevel::HIGH}) 
            {
                for (auto t : {ThrottleLevel::ThrottleLevelEnum::LOW, ThrottleLevel::ThrottleLevelEnum::MEDIUM, ThrottleLevel::ThrottleLevelEnum::HIGH}) 
                {
                    // 1
                    if (v == Velocity::VelocityLevel::VERY_LOW && 
                        (r == EngineRpm::RpmLevel::LOW || r == EngineRpm::RpmLevel::MEDIUM || r == EngineRpm::RpmLevel::HIGH) && 
                        (t == ThrottleLevel::ThrottleLevelEnum::LOW || t == ThrottleLevel::ThrottleLevelEnum::MEDIUM || t == ThrottleLevel::ThrottleLevelEnum::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::START;
                    }
                    // 2
                    else if ((v == Velocity::VelocityLevel::LOW || v == Velocity::VelocityLevel::MEDIUM) && 
                    (r == EngineRpm::RpmLevel::LOW || r == EngineRpm::RpmLevel::MEDIUM || r == EngineRpm::RpmLevel::HIGH) && 
                    (t == ThrottleLevel::ThrottleLevelEnum::LOW || t == ThrottleLevel::ThrottleLevelEnum::MEDIUM || t == ThrottleLevel::ThrottleLevelEnum::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::LOW;
                    }
                    // 3
                    else if (v == Velocity::VelocityLevel::HIGH && 
                    (r == EngineRpm::RpmLevel::LOW || r == EngineRpm::RpmLevel::MEDIUM || r == EngineRpm::RpmLevel::HIGH) && 
                    (t == ThrottleLevel::ThrottleLevelEnum::LOW || t == ThrottleLevel::ThrottleLevelEnum::MEDIUM || t == ThrottleLevel::ThrottleLevelEnum::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::MEDIUM;
                    }
                    // 4
                    else if (v == Velocity::VelocityLevel::MEDIUM && 
                             r == EngineRpm::RpmLevel::LOW && 
                             t == ThrottleLevel::ThrottleLevelEnum::HIGH)
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::LOW;
                    }
                    // 5 and 6
                    else if (v == Velocity::VelocityLevel::MEDIUM && 
                             (r == EngineRpm::RpmLevel::LOW || r == EngineRpm::RpmLevel::MEDIUM) && 
                             (t == ThrottleLevel::ThrottleLevelEnum::LOW || t == ThrottleLevel::ThrottleLevelEnum::MEDIUM || t == ThrottleLevel::ThrottleLevelEnum::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::MEDIUM;
                    }
                    // 7
                    else if (v == Velocity::VelocityLevel::MEDIUM && 
                             r == EngineRpm::RpmLevel::HIGH && 
                             (t == ThrottleLevel::ThrottleLevelEnum::LOW || t == ThrottleLevel::ThrottleLevelEnum::MEDIUM || t == ThrottleLevel::ThrottleLevelEnum::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::HIGH;
                    }
                    // 8
                    else if (v == Velocity::VelocityLevel::HIGH && 
                             r == EngineRpm::RpmLevel::LOW && 
                             t == ThrottleLevel::ThrottleLevelEnum::HIGH)
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::MEDIUM;
                    }
                    // 9 and 10
                    else if (v == Velocity::VelocityLevel::HIGH && 
                             (r == EngineRpm::RpmLevel::MEDIUM || r == EngineRpm::RpmLevel::HIGH || r == EngineRpm::RpmLevel::LOW) && 
                             (t == ThrottleLevel::ThrottleLevelEnum::LOW || t == ThrottleLevel::ThrottleLevelEnum::MEDIUM || t == ThrottleLevel::ThrottleLevelEnum::HIGH))
                    {
                        temp[std::make_tuple(v, r, t)] = Gear::GearLevel::HIGH;
                    }
                }
            }
        }

        return temp;
    };
};


#endif
