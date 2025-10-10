#include "TestStand.h"
#include "Engine.h"
#include <iostream>
double TestStand::runOverHeatTest(Engine &engine){
    engine.reset();
    while (!engine.isOverheated()){
        engine.simulationStep();
        if (engine.getTime()>1000.0){
            return 0.0;
        }
        return engine.getTime();
    }
}
 std::pair<double ,double> TestStand::runMaxPowerTest(Engine &engine){
    engine.reset();
    double max_power = 0.0;
    double max_power_velocity = 0.0;
    double prev_velocity = -1.0;
    while (!engine.isMaxSpeed()){
        engine.simulationStep();
        double current_power = engine.getPower();
        if (current_power > max_power) {
            max_power = current_power;
            max_power_velocity = engine.getVelocity();
        }
         if (engine.getTime() > 1000.0) {
            break;
        }
    }
    return std::make_pair(max_power,max_power_velocity);
}

