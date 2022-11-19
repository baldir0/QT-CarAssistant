#ifndef CALCULATOR_H
#define CALCULATOR_H


class Calculator
{
    public:
        Calculator();
        static double calculatePrice(double price, double distance, double consumption);
        static double calculateConsumption(double distance, double fuel);
        static double calculateRange(double consumption, double fuel);
        static double calculateNeededFuel(double distance, double consumption);

        void setPrice(double price);
        void setConsumption(double consumption);
        void setDistance(double distance);
        void setFuel(double fuel);

        double getPrice();
        double getConsumption();
        double getDistance();
        double getFuel();

        double calculatePrice();
        double calculateConsumption();
        double calculateRange();
        double calculateNeededFuel();
    private:
        double price;
        double distance;
        double consumption;
        double fuel;
};

#endif // CALCULATOR_H
