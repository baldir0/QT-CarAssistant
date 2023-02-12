#include "service.h"
#include "service.h"
#include "logger.h"


Service::Service() { };

Service::Service(QString insuranceDate, QString oilChangeDate, QString serviceDate, int oilChangeMileage) {
    Logger::log<typeof(*this)>("Creating Service Data ... ");
    this->insuranceDate = QDate::fromString(insuranceDate, DATE_FORMAT);
    this->oilChangeDate = QDate::fromString(oilChangeDate, DATE_FORMAT);
    this->serviceDate = QDate::fromString(serviceDate, DATE_FORMAT);
    this->oilChangeMileage = oilChangeMileage;
    Logger::log<typeof(*this)>("Service Data Created!");
}

QString Service::getProductionDate() {
    return this->productionDate.toString(DATE_FORMAT);
}

void Service::setProductionDate(QString date) {
    this->productionDate = QDate::fromString(date, DATE_FORMAT);
}

QString Service::getInsuranceDate() {
    return this->insuranceDate.toString(DATE_FORMAT);
}

void Service::setInsuranceDate(QString date) {
    this->insuranceDate = QDate::fromString(date, DATE_FORMAT);
}

QString Service::getOilChangeDate() {
    return this->oilChangeDate.toString(DATE_FORMAT);
}

void Service::setOilChangeDate(QString date) {
    this->oilChangeDate = QDate::fromString(date, DATE_FORMAT);
}

QString Service::getServiceDate() {
    return this->serviceDate.toString(DATE_FORMAT);
}

void Service::setServiceDate(QString date) {
    this->serviceDate = QDate::fromString(date, DATE_FORMAT);
}

int Service::getOilChangeMileage() {
    Logger::log<typeof(*this)>("Oil Change Mileage:" + QString::number(this->oilChangeMileage));
    return this->oilChangeMileage;
}

void Service::setOilChangeMileage(int value) {
    this->oilChangeMileage = value;
}

int Service::getCurrentMileage()
{
    return this->currentMileage;
}

void Service::setCurrentMileage(int value)
{
    this->currentMileage = value;
}

short Service::getTankCapacity() {
    return this->tankCapacity;
}

void Service::setTankCapacity(short value) {
    this->tankCapacity = value;
}

float Service::getEngineCapacity() {
    return this->engineCapacity;
}

void Service::setEngineCapacity(float value) {
    this->engineCapacity = value;
}

int8_t Service::getFuelType() {
    return this->fuelType;
}

QString Service::getFuelTypeName() {
        switch(this->fuelType) {
            case Service::GASOLINE:
                return QString("Gasoline");
            case Service::DIESEL:
                return QString("Diesel");
            case Service::GAS:
                return QString("Gas");
            case Service::OTHER:
                return QString("Other");
            default:
                return QString("Unsupported");
        }
}

void Service::setFuelType(Service::FuelType fuelType) {
    this->fuelType = fuelType;
}

bool Service::checkInsuranceDate() {
    QDate insuranceExpireDate = this->insuranceDate.addYears(INSURANCE_EXPIRE_YEARS);
    if (QDate::currentDate().daysTo(insuranceExpireDate) < 0)
        return false;
    return true;
}

bool Service::checkOilChangeDate() {
    QDate nextOilChange = this->oilChangeDate.addYears(OIL_CHANGE_YEARS);
    if (QDate::currentDate().daysTo(nextOilChange) < 0)
        return false;
    return true;
}

bool Service::checkOilChangeMileage() {
    if (this->currentMileage - this->oilChangeMileage > OIL_CHANGE_MILEAGE)
        return false;
    return true;
}

bool Service::checkServiceDate() {
    QDate nextServiceDate = this->serviceDate.addYears(SERVICE_EXPIRE_YEARS);
    if (QDate::currentDate().daysTo(nextServiceDate) < 0)
        return false;
    return true;
}
