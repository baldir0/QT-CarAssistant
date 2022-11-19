#ifndef CAR_H
#define CAR_H

#include <string>

using std::string;

class Car
{
    public:
        Car(string name, string description);
        Car(string name, string description, string model, string fuelType, string brand, double engineCapacity, int productionDate);

        string getName();
        string getDescription();
        string getModel();
        string getFuelType();
        string getBrand();
        double getEngineCapacity();
        int getProductionDate();
    private:
        string name;
        string description;
        string model = "undefined";
        string fuelType = "undefined";
        string brand = "undefined";
        double engineCapacity = 0.0;
        int productionDate = 0; // Rocznik
};

#endif // CAR_H
