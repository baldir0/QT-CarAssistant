#include "expenses.h"

Expenses::Expenses()
{
    this->loadExpenses();
}

int Expenses::getLastElementId()
{
    return this->expenses.back().getId();
}

void Expenses::add(Expense expense)
{
    expense.setId(this->getLastElementId() + 1);
    this->expenses.push_back(expense);
}

void Expenses::remove(int expenseId)
{
    for (Expense ex : this->expenses) {
        this->expenses.remove_if([&ex](int id) { return id == ex.getId(); });
    }
}

void Expenses::loadExpenses() {
    // TODO
    // Załaduje wydaki z pliku czy tam gdzie są
}
