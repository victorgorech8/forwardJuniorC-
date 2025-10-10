#pragma once
namespace Config{
    constexpr double I=10.0;
    constexpr double M_VALUE[]={20,75,100,105,75,0};
    constexpr double V_VALUE[]={0,75,150,200,250,300};
    constexpr int POINT_COUNT=6;
    constexpr double T_OVERHEAT =110.0;
    constexpr double H_M=0.011;
    constexpr double H_V=0.0001;
    constexpr double C=0.01;
    constexpr double dt=0.1;
    constexpr double min_torque=1.0;
}