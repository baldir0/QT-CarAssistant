#include "expense.h"

Expense::Expense(string name,
                 string description,
                 expenseType type,
                 double moneyAmount,
                 QDate date)
{
    this->name = name;
    this->description = description;
    this->type = type;
    this->moneyAmount = moneyAmount;
    this->date = date;
}

void Expense::setName(std::string name)
{
    this->name = name;
}

void Expense::setDescription(std::string description)
{
    this->description = description;
}

void Expense::setType(expenseType type)
{
    this->type = type;
}

void Expense::setMoneyAmount(double moneyAmount)
{
    this->moneyAmount = moneyAmount;
}

void Expense::setDate(QDate date)
{
    this->date = date;
}

int Expense::getId() {
    return this->id;
}

string Expense::getName()
{
    return this->name;
}

string Expense::getDescription()
{
    return this->description;
}

int Expense::getType()
{
    return this->type;
}

string Expense::getStringifyType() {
    if (this->type == fuel) return "fuel";
    if (this->type == service) return "service";
    return "other";
}

double Expense::getMoneyAmount()
{
    return this->moneyAmount;
}

QDate Expense::getDate()
{
    return this->date;
}
