#ifndef SERVICE_H
#define SERVICE_H
#define DATE_FORMAT "dd.MM.yyyy"

#include <QDate>

class Service
{
private:
    QDate productionDate;
    QDate insuranceDate;
    QDate oilChangeDate;
    QDate serviceDate;
    int oilChangeMileage;
    short tankCapacity;
    float engineCapacity;
    int8_t fuelType;

    const int OIL_CHANGE_MILEAGE = 10000;
    const int INSURANCE_EXPIRE_YEARS = 1;
    const int OIL_CHANGE_YEARS = 1;
    const int SERVICE_EXPIRE_YEARS = 1;

public:
    enum FuelType : std::int8_t{
        GASOLINE,
        DIESEL,
        GAS,
        OTHER
    };

    Service();
    Service(QString insuranceDate, QString oilChangeDate, QString serviceDate, int oilChangeMileage);
    QString getProductionDate();
    void setProductionDate(QString date);
    QString getInsuranceDate();
    void setInsuranceDate(QString date);
    QString getOilChangeDate();
    void setOilChangeDate(QString date);
    QString getServiceDate();
    void setServiceDate(QString date);
    int getOilChangeMileage();
    void setOilChangeMileage(int value);
    short getTankCapacity();
    void setTankCapacity(short value);
    float getEngineCapacity();
    void setEngineCapacity(float value);
    int8_t getFuelType();
    QString getFuelTypeName();
    void setFuelType(Service::FuelType fuelType);
    /**
     * @brief Service::checkInsuranceDate
     * @return false if Insurance is expired, otherwise returns true
     */
    bool checkInsuranceDate();
    bool checkOilChangeDate();
    bool checkOilChangeMileage();
    bool checkServiceDate();
};

#endif // SERVICE_H
