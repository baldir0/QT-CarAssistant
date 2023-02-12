#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>
#include <QDate>

class Expense
{
public:
    enum ExpenseType : int8_t{
        REFUELING,
        SERVICE,
        PARTS,
        OTHER
    };

    Expense(QString name, QDate date, double amount);
    Expense(QString name, QDate date, double amount, Expense::ExpenseType type);

    QString getName();
    void setName(QString name);
    QString getDate();
    void setDate(QString date);
    double getExpense();
    void setExpense(double amount);
    int8_t getExpenseType();
    void setExpenseType(Expense::ExpenseType type);

    static ExpenseType getExpenseTypeFromInt(int val);

    QString toString();
private:
    QString name;
    int8_t type;
    QDate date;
    double expense;
};

#endif // EXPENSE_H
