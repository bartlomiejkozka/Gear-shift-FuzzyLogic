#include "GearShift.hpp"
#include <iostream>


int main()
{
    GearShift gearShift;
    gearShift.setInputs(90, 1000, 100); 
    float newGear = gearShift.shift();
    std::cout << "Recommended Gear: " << newGear << std::endl;

    return 0;
}