#ifndef EXPENSES_H
#define EXPENSES_H

#include <list>
#include "expense.h"

using std::list;

class Expenses
{
    public:
        Expenses();

        int getLastElementId();

        void add(Expense expense);
        void remove(int id);
        void saveExpenses();
        void loadExpenses();

    private:
        list<Expense> expenses;
};

#endif // EXPENSES_H
