#include "expense.h"

Expense::Expense(QString name, QDate date, double amount)
{
    this->name = name;
    this->date = date;
    this->expense = amount;
    this->type = this->OTHER;
}

Expense::Expense(QString name, QDate date, double amount, Expense::ExpenseType type) {
    this->name = name;
    this->date = date;
    this->expense = amount;
    this->type = type;
}

QString Expense::getName() {
    return this->name;
}

void Expense::setName(QString name) {
    this->name = name;
}

QString Expense::getDate() {
    return this->date.toString("dd.MM.yyyy");
}

void Expense::setDate(QString date) {
    this->date = QDate::fromString("dd.MM.yyyy");
}

double Expense::getExpense() {
    return this->expense;
}

void Expense::setExpense(double expense) {
    this->expense = expense;
}

int8_t Expense::getExpenseType() {
    return this->type;
}

void Expense::setExpenseType(Expense::ExpenseType type) {
    this->type = type;
}

QString Expense::toString()
{
    return name + "\t-\t" +
            date.toString("dd.MM.yyyy") + "\t-\t" +
            QString::number(expense);
}


