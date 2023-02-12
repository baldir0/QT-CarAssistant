#ifndef CAR_H
#define CAR_H

#define DATE_FORMAT "dd.MM.yyyy"

#include <QString>
#include <QVector>
#include "expense.h"
#include "service.h"

class Car
{
private:
    QString saveFileName = "";
    QString name = "";
    QString description = "";
    QString model = "";
    QString brand = "";
    QVector<Expense*> expenseList;
    Service service;

    void assignLoadedValues(int key, QString value);

    void debugFieldsValue();
public:
    Car(QString name);
    Car(QString name,
        QString description,
        QString model,
        QString brand,
        QString productionDate,
        QString insuranceDate,
        QString oilChangeDate,
        QString serviceDate,
        short tankCapacity,
        float engineCapacity,
        Service::FuelType fuelType);

    void save();
    void load();
    bool remove();

    void addExpense(Expense *ex);
    void removeExpense(int position);

    QString getName();
    void setName(QString name);
    QString getDescription();
    void setDescription(QString description);
    QString getModel();
    void setModel(QString model);
    QString getBrand();
    void setBrand(QString brand);



    Service & getService();
    QVector<Expense*> getExpenses();
};

#endif // CAR_H
