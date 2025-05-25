#include "GearShift.hpp"
#include <iostream>
#include "CLI/CLI.hpp"


int main(int argc, char **argv)
{
    CLI::App app{"App description"};

    int v = 0;
    int r = 0;
    int t = 0;
    app.add_option("-v", v, "Velocity (0-200)");
    app.add_option("-r", r, "Rpm (0-8000)");
    app.add_option("-t", t, "Throttle (0-100)");

    CLI11_PARSE(app, argc, argv);

    GearShift gearShift;
    gearShift.setInputs(v, r, t); 
    float newGear = gearShift.shift();

    return 0;
}
