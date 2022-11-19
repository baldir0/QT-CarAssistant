#include "calculator.h"

Calculator::Calculator()
{

}



double Calculator::calculatePrice() {
    return this->calculatePrice(this->price, this->distance, this->consumption);
}

double Calculator::calculateConsumption() {
    return this->calculateConsumption(this->distance, this->consumption);
}

double Calculator::calculateRange() {
    return this->calculateRange(this->consumption, this->fuel);
}

double Calculator::calculateNeededFuel() {
    return this->calculateNeededFuel(this->distance, this->consumption);
}



double Calculator::calculatePrice(double price, double distance, double consumption) {
    return distance * consumption * price / 100;
}

double Calculator::calculateConsumption(double distance, double fuel) {
    return fuel / distance * 100;
}

double Calculator::calculateRange(double consumption, double fuel) {
    return fuel / consumption * 100;
}

double Calculator::calculateNeededFuel(double distance, double consumption) {
    return distance * consumption / 100;
}
