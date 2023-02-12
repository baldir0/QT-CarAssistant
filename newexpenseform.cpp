#include "newexpenseform.h"
#include "ui_newexpenseform.h"
#include "expense.h"

NewExpenseForm::NewExpenseForm(QWidget *parent, Car *obj) :
    QDialog(parent),
    ui(new Ui::NewExpenseForm)
{
    ui->setupUi(this);
    this->car = obj;
}

NewExpenseForm::~NewExpenseForm() {
    delete ui;
}

void NewExpenseForm::on_buttonBox_accepted() {
    Expense * ex = new Expense(
                this->ui->Name_Edit->text(),
                QDate::fromString(this->ui->dateEdit->text(), "dd.MM.yyyy"),
                this->ui->Price->value(),
                Expense::getExpenseTypeFromInt(this->ui->comboBox->currentIndex()));

    this->car->addExpense(ex);
}


void NewExpenseForm::on_buttonBox_rejected() {
    this->close();
}

