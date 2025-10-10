#pragma once
class Engine{
private:
    double I_;
    double T_OVERHEAT_;
    double H_M_;
    double H_V_;
    double C_;
    double T_AMBIENT_;

    double velocity_;
    double temperature_;
    double time_;
public:
    Engine(double I, double T_overheat, double H_m, double H_v, double C, double T_ambient);
    double getVelocity() const { return velocity_; }
    double getTemperature() const { return temperature_; }
    double getTime() const { return time_; }
    bool isOverheated() const { return temperature_ >= T_OVERHEAT_; }
    bool isMaxSpeed() const;
    
    double getTorque();
    void simulationStep();
    double getPower();
    void reset();
    bool isMaxSpeed();
};