#pragma once
#include "Engine.h"
#include <utility>
class TestStand{
public:
    static double runOverHeatTest(Engine &engine);
    static std::pair<double ,double> runMaxPowerTest(Engine &engine);
};