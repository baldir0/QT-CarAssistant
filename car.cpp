#include "car.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDate>
#include "savemanager.h"
#include "filemanager.h"
#include "logger.h"

Car::Car(QString vehicleName) {
    Logger::log<typeof(*this)>("Creating Object ...");
    this->saveFileName = vehicleName + ".dat";
    Logger::log<typeof(*this)>("Object Created!");
}

Car::Car(QString name,
    QString description,
    QString model,
    QString brand,
    QString productionDate,
    QString insuranceDate,
    QString oilChangeDate,
    QString serviceDate,
    short tankCapacity,
    float engineCapacity,
         Service::FuelType fuelType) {
    Logger::log<typeof(*this)>("Creating Object ...");
    this->saveFileName = name + ".dat";
    this->name = name;
    this->description = description;
    this->model = model;
    this->brand = brand;
    this->service.setProductionDate(productionDate);
    this->service.setInsuranceDate(insuranceDate);
    this->service.setOilChangeDate(oilChangeDate);
    this->service.setOilChangeMileage(0);
    this->service.setCurrentMileage(0);
    this->service.setServiceDate(serviceDate);
    this->service.setTankCapacity(tankCapacity);
    this->service.setEngineCapacity(engineCapacity);
    this->service.setFuelType(fuelType);
    Logger::log<typeof(*this)>("Object Created!");
}

void Car::save() {
    Logger::log<typeof(*this)>("Saving car ...");
    QMap<int, QString> fileData;

    fileData.insert(0, this->name);
    fileData.insert(1, this->description);
    fileData.insert(2, this->model);
    fileData.insert(3, this->brand);
    fileData.insert(4, this->service.getProductionDate());
    fileData.insert(5, this->service.getInsuranceDate());
    fileData.insert(6, this->service.getOilChangeDate());
    fileData.insert(7, this->service.getServiceDate());
    fileData.insert(8, QString::number(this->service.getOilChangeMileage()));
    fileData.insert(9, QString::number(this->service.getTankCapacity()));
    fileData.insert(10, QString::number(this->service.getEngineCapacity()));
    fileData.insert(11, QString::number(this->service.getFuelType()));
    fileData.insert(12, QString::number(this->service.getCurrentMileage()));

    QVectorIterator<Expense*> it(this->expenseList);
    while (it.hasNext()) {
        Expense *tmp = it.next();
        short lastKey = fileData.lastKey();
        fileData.insert(lastKey + 1, tmp->getName());
        fileData.insert(lastKey + 2, tmp->getDate());
        fileData.insert(lastKey + 3, QString::number(tmp->getExpense()));
        fileData.insert(lastKey + 4, QString::number(tmp->getExpenseType()));

    }
    this->debugFieldsValue();
    SaveManager::save(FileManager::getSaveLocation() + this->saveFileName, fileData);
    Logger::log<typeof(*this)>("Car saved!");
}

void Car::load() {
    Logger::log<typeof(*this)>("Loading car ...");
    QMap<int, QString> fileData = SaveManager::load(FileManager::getSaveLocation() + this->saveFileName);
    QMapIterator<int, QString> it(fileData);

    for (short i = 0 ; i < 13 ; i ++) {
        it.next();
        this->assignLoadedValues(it.key(), it.value());
    }

    while(it.hasNext()) {
        Expense *ex = new Expense(
                    it.next().value(),
                    QDate::fromString(it.next().value(), "dd.MM.yyyy"),
                    it.next().value().toDouble(),
                    Expense::ExpenseType(it.next().value().toInt()));
        this->expenseList.append(ex);
    }
    Logger::log<typeof(*this)>("Car loaded!");
    // this->debugFieldsValue();
}

bool Car::remove() {
    Logger::log<typeof(*this)>("Removing Car ...");
    const QString filePath = FileManager::getSaveLocation() + this->saveFileName;
    if (!FileManager::remove(filePath)) return false;

    QMap <int, QString> fileData = SaveManager::load(FileManager::getSaveLocation() + "list.dat");
    QMapIterator <int, QString> it(fileData);
    it.next();
    while (it.hasNext()) {
        qDebug() << "[COMPARING] - " + it.value();
        if (it.value() == this->name) {
            fileData.remove(it.key());
            break;
        }
        it.next();
    }
    Logger::log<typeof(*this)>("Car Removed!");
    return SaveManager::save(FileManager::getSaveLocation() + "list.dat", fileData);
}

void Car::assignLoadedValues(int key, QString value)
{
    switch(key) {
        case 0: this->name = value; break;
        case 1: this->description = value; break;
        case 2: this->model = value; break;
        case 3: this->brand = value; break;
        case 4: this->service.setProductionDate(value); break;
        case 5: this->service.setInsuranceDate(value); break;
        case 6: this->service.setOilChangeDate(value); break;
        case 7: this->service.setServiceDate(value); break;
        case 8: this->service.setOilChangeMileage(value.toInt()); break;
        case 9: this->service.setTankCapacity(value.toShort()); break;
        case 10: this->service.setEngineCapacity(value.toFloat()); break;
        case 11: this->service.setFuelType(Service::FuelType(value.toInt())); break;
        case 12: this->service.setCurrentMileage(value.toInt()); break;
    }
}

void Car::addExpense(Expense *ex) {
    Logger::log<typeof(*this)>("Adding Expense ...");
    this->expenseList.append(ex);
}

void Car::removeExpense(int position) {
    Logger::log<typeof(*this)>("Removing Expense At " + QString::number(position) + " ...");
    this->expenseList.removeAt(position);
}

QString Car::getName() {
    return this->name;
}

void Car::setName(QString name) {
    this->name = name;
}

QString Car::getDescription() {
    return this->description;
}

void Car::setDescription(QString description) {
    this->description = description;
}

QString Car::getModel() {
    return this->model;
}

void Car::setModel(QString model) {
    this->model = model;
}

QString Car::getBrand() {
    return this->brand;
}

void Car::setBrand(QString brand) {
    this->brand = brand;
}

Service & Car::getService() {
    return this->service;
}

QVector<Expense *> Car::getExpenses()
{
    return this->expenseList;
}

void Car::debugFieldsValue() {
    qDebug() << "Name:" << name;
    qDebug() << "Descripiton:" << description;
    qDebug() << "Model:" << model;
    qDebug() << "Brand:" << brand;
    qDebug() << "Production Date:" << service.getProductionDate();
    qDebug() << "Insurance Date:" << service.getInsuranceDate();
    qDebug() << "Oil Change Date:" << service.getOilChangeDate();
    qDebug() << "Service Date:" << service.getServiceDate();
    qDebug() << "Tank Capacity:" << service.getTankCapacity();
    qDebug() << "Engine Capacity:" << service.getEngineCapacity();
    qDebug() << "Fuel Type:" << service.getFuelType();
    qDebug() << "Expenses:" << expenseList;
    QVectorIterator<Expense*> it(expenseList);
    while (it.hasNext()) {
        Expense *ex = it.next();
        qDebug() << "Name:" << ex->getName() << "\tValue:" << ex->getExpense() << "\tType" << ex->getExpenseType() << "\tDate:" << ex->getDate();
    }
}
