#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <QDateTime>

using std::string;

class Expense
{
    private:
        int id;
        string name;
        string description = "undefined";
        int type;
        double moneyAmount;
        QDate date;


    public:
        enum expenseType {
            fuel = 0,
            service,
            other
        };

        Expense(string name,
                string description,
                expenseType type,
                double moneyAmount,
                QDate date);

        void setId(int id);
        void setName(string name);
        void setDescription(string description);
        void setType(expenseType type);
        void setMoneyAmount(double moneyAmount);
        void setDate(QDate date);

        int getId();
        string getName();
        string getDescription();
        int getType();
        string getStringifyType();
        double getMoneyAmount();
        QDate getDate();
};

#endif // EXPENSE_H
