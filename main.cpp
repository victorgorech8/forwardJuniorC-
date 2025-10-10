#include <iostream>
#include <iomanip>
#include "Engine.h"
#include "TestStand.h"
#include "Config.h"
#include <locale>
#include <windows.h>
using namespace std;

void printConfiguration() {
    cout << "=== Конфигурация двигателя ===" << endl;
    cout << "Момент инерции (I): " << Config::I << " кг·м²" << endl;
    cout << "Температура перегрева: " << Config::T_OVERHEAT << " °C" << endl;
    cout << "Коэффициент H_m: " << Config::H_M << endl;
    cout << "Коэффициент H_v: " << Config::H_V << endl;
    cout << "Коэффициент C: " << Config::C << endl;
    cout << "Зависимость M(V):" << endl;
    for (int i = 0; i < Config::POINT_COUNT; ++i) {
        cout << "  V = " << Config::V_VALUE[i] << " -> M = " << Config::M_VALUE[i] << endl;
    }
    cout << "Временной шаг симуляции: " << Config::dt << endl;
    cout << "Значнеие момента для прекращения теста (погрешность): " << Config::min_torque << endl;
    cout << "===============================" << endl << endl;
}
void printSelect() {
    cout << "Выберите один из пунктов:"<< endl;
    cout << "1- Тест время перегрева двигателя" << endl;
    cout << "2- Тест на максимальную скорость двигателя: " <<  endl;
    cout << "3- Поменять температуру окружающей среды" << endl;
    cout << "4- Выход из программы" << endl;
}
int main(){
    SetConsoleOutputCP(CP_UTF8);  
    setlocale(LC_ALL, "ru_RU.UTF-8");
    double ambient_temperature;
    cout << "Введите температуру окружающей среды (°C): ";
    cin >> ambient_temperature;
    
    
    Engine engine(Config::I, Config::T_OVERHEAT, Config::H_M, 
                  Config::H_V, Config::C, ambient_temperature);
    int choice=0;
    printSelect();
    cin>>choice;
    while (choice!=4){
        if (choice==1){
             cout << "Двигатель перегрелся через: " << TestStand::runOverHeatTest(engine) << " секунд" << endl;
        }
        if (choice==2){
            auto result=TestStand::runMaxPowerTest(engine);
             cout << "Максимальная мощность: " << result.first << " кВт" << endl;
            cout << "При скорости вращения: " << result.second << " радиан/сек" << endl;
        }
        if (choice == 3) {
            cout << "Введите температуру окружающей среды (°C): ";
            cin >> ambient_temperature;

           engine= Engine(Config::I, Config::T_OVERHEAT, Config::H_M,
                Config::H_V, Config::C, ambient_temperature);
        }
        printSelect();
        cin>>choice;
    }
    cout<<"Зарвешение работы программы! Пока"<< endl;
    return 0;
};
