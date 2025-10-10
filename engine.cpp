#include "Engine.h"
#include "Config.h"
#include <algorithm>
Engine::Engine(double I, double T_overheat, double H_m, double H_v, double C, double T_ambient)
    : I_(I), T_OVERHEAT_(T_overheat), H_M_(H_m), H_V_(H_v), C_(C), T_AMBIENT_(T_ambient) {
    reset();
}
void Engine::reset(){
    velocity_=0.0;
    temperature_=T_AMBIENT_;
    time_=0.0;
}
double Engine::getTorque()  {
    
    for (int i = 0; i < Config::POINT_COUNT - 1; ++i) {
        if (velocity_ >= Config::V_VALUE[i] && velocity_ <= Config::V_VALUE[i + 1]) {
            double t = (velocity_ - Config::V_VALUE[i]) / 
                      (Config::V_VALUE[i + 1] - Config::V_VALUE[i]);
            return Config::M_VALUE[i] + t * (Config::M_VALUE[i + 1] - Config::M_VALUE[i]);
        }
    }
    
}
void Engine::simulationStep() {
    // Расчет крутящего момента
    double torque = getTorque();
    
    // Расчет ускорения (a = M / I)
    double acceleration = torque / I_;
    
    // Обновление скорости
    velocity_ += acceleration * Config::dt;
    velocity_ = std::max(0.0, velocity_); // Скорость не может быть отрицательной
    
    // Расчет скорости нагрева
    double heating_rate = torque * H_M_ + velocity_ * velocity_ * H_M_;
    
    // Расчет скорости охлаждения
    double cooling_rate = C_ * (T_AMBIENT_ - temperature_);
    
    // Обновление температуры
    temperature_ += (heating_rate + cooling_rate) * Config::dt;
    
    // Обновление времени
    time_ += Config::dt;
}
double Engine::getPower() {
    return getTorque()*velocity_/1000.0;
}
bool Engine::isMaxSpeed()  {
    
    return getTorque() < Config::min_torque;  

}