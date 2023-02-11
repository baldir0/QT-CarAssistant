#ifndef CALCULATOR_H
#define CALCULATOR_H


class Calculator
{
    public:
        static float tripPrice(float distance, float fuelPrice, float fuelConsumption);
        static float distance(float fuel, float fuelConsumption);
        static float fuelConsumptionUnit(float distance, float consumedFuel);
        static float neededFuel(float distance, float fuelConsumption);

        enum CalculationType {
            TRIP_PRICE,
            DISTANCE,
            FUEL_CONSUMPTION,
            NEEDED_FUEL
        };
        static CalculationType translateIndexToType(int index);
};

#endif // CALCULATOR_H
