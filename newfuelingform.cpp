#include "newfuelingform.h"
#include "ui_newfuelingform.h"
#include "expense.h"

NewFuelingForm::NewFuelingForm(QWidget *parent, Car * obj) :
    QDialog(parent),
    ui(new Ui::NewFuelingForm)
{
    ui->setupUi(this);
    this->car = obj;
}

NewFuelingForm::~NewFuelingForm()
{
    delete ui;
}

void NewFuelingForm::on_buttonBox_accepted()
{
    Expense * ex = new Expense(
                this->ui->Name_Edit->text(),
                QDate::fromString(this->ui->dateEdit->text(), "dd.MM.yyyy"),
                this->ui->Price->value(),
                Expense::REFUELING);
    qDebug() << ex->getName() << ex->getDate() << ex->getExpenseType() << ex->getExpense();
    this->car->getService().setCurrentMileage(this->ui->spinBox->value());

    this->car->addExpense(ex);
    this->close();
}


void NewFuelingForm::on_buttonBox_rejected()
{
    this->close();
}

