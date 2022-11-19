#ifndef SERVICE_H
#define SERVICE_H

#include <string>

using std::string;

class Service
{
    public:
        Service();
        bool maintenanceExpired();
        bool oilToChange();
    private:
        int maintenaceDate = 0; // Data Przeglądu
        int oilChangeDate = 0;
        int oilChangeMileage = 0;
        string oilType = "undefined";
        int mileage = 0;
};

#endif // SERVICE_H
