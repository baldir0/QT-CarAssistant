#include "calculator.h"

#include <QDebug>
float Calculator::tripPrice(float distance, float fuelPrice, float fuelConsumption) {
    qDebug() << distance;
    return distance * fuelConsumption / 100 * fuelPrice;
}

float Calculator::distance(float fuel, float fuelConsumption) {
    return 100 / fuelConsumption * fuel;
}

float Calculator::fuelConsumptionUnit(float distance, float consumedFuel) {
    return consumedFuel / distance * 100;
}

float Calculator::neededFuel(float distance, float fuelConsumption) {
    return distance / 100 * fuelConsumption;
}

Calculator::CalculationType Calculator::translateIndexToType(int index) {
    switch (index) {
        case 0: return TRIP_PRICE;
        case 1: return DISTANCE;
        case 2: return FUEL_CONSUMPTION;
        case 3: return NEEDED_FUEL;
        default: return TRIP_PRICE;
    }
}
