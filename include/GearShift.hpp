#ifndef GEAR_CHANGE_HPP
#define GEAR_CHANGE_HPP

#include <cstdint>
#include "FuzzyHelpers.hpp"
#include "FuzzyRules.hpp"

/*
* Input parameters:
* - velocity: The current velocity of the vehicle.
* - engineRpm: The current engine RPM (Revolutions Per Minute).
* - ThrottleLevel: The current throttle (car's accelerator pedal) level (0-100).

* Output parameters:
* - gear: The current gear of the vehicle.
*/

/*
* Gear Change decistion is made for 0 - 7 gears, which probbably is the most common nowadays.
*/

class GearShift {

    public:
    //------------------
    // Attribs
    //------------------
    static constexpr uint8_t MAX_GEAR = 7; // Maximum gear number

    //------------------
    // Constructor
    //------------------
    GearShift() = default;
    ~GearShift() = default;
    GearShift(GearShift const&) = default;
    GearShift& operator=(GearShift const&) = default;

    //------------------
    // Setters
    //------------------
    void setVelocity(uint8_t v) { velocity = v; }
    void setEngineRpm(uint16_t rpm) { engineRpm = rpm; }
    void setThrottleLevel(uint8_t throttle) { throttleLevel = throttle; }
    void setInputs(uint8_t v, uint16_t rpm, uint8_t throttle) 
    {
        velocity = v;
        engineRpm = rpm;
        throttleLevel = throttle;
    }  

    //------------------
    // methods
    //------------------
    float const shift();

    //------------------
    // Helpers
    //------------------

    private:
    uint8_t gear;
    uint8_t velocity;
    uint16_t engineRpm;
    uint8_t throttleLevel;
};


#endif
