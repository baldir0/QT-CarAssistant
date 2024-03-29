#include "mainwidget.h"
#include "./ui_mainwidget.h"
#include "uicontroller.h"
#include "newcarform.h"
#include "newexpenseform.h"
#include "newfuelingform.h"
#include "oilchange.h"

#include "logger.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    Logger::log<typeof(*this)>("Main Widget Constructor ...");
    // LOAD FILES TO LIST
    this->fm = new FileManager();
    this->fm->checkSaveLocalization();
    this->loadingData = true;
    UIController::loadCarList(this->ui->SELECT_CAR);
    this->loadingData = false;

    this->ui->SELECT_CAR->setCurrentIndex(0);
    this->car = new Car(this->ui->SELECT_CAR->currentText());
    this->car->load();
    UIController::loadStatisticsPage(*this->car, *this->ui);
    UIController::loadServicePage(*this->car, *this->ui);
    UIController::loadHomePage(*this->car, *this->ui);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_SELECT_CAR_currentIndexChanged(int index)
{
    Logger::log<typeof(*this)>("Changing Active Car ...");
    if (index < 0 || loadingData) return;
    qDebug() << "Total Elements: " << this->ui->SELECT_CAR->count() << "Current Index:" << index;
    if (index == this->ui->SELECT_CAR->count() - 1) {
        qDebug() << "Add New Car";
        NewCarForm *form = new NewCarForm(this);
        form->exec();
        if (form->result()) {
            UIController::loadCarList(this->ui->SELECT_CAR);
        }
        Logger::log<typeof(*this)>("Car Created!");
        Logger::log<typeof(*this)>("Result: " + QString::number(form->result()));
        return;
    }

    qDebug() << "Loading Car Info...";
    this->car = new Car(this->ui->SELECT_CAR->currentText());
    this->car->load();
    UIController::loadHomePage(*this->car, *this->ui);
    Logger::log<typeof(*this)>("Active Car Changed!");
}

void MainWidget::on_CALCULATOR_OPERATION_PICK_currentIndexChanged(int index) {
    UIController::switchActiveCalculationFields(Calculator::translateIndexToType(index), *this->ui);
}

void MainWidget::on_HOME_BUTTON_clicked() {
    UIController::loadHomePage(*this->car, *this->ui);
    this->setPage(0);
}

void MainWidget::on_STATISTICS_BUTTON_clicked() {
    UIController::loadStatisticsPage(*this->car, *this->ui);
    this->setPage(1);
}

void MainWidget::on_SERVICE_BUTTON_clicked() {
    UIController::loadServicePage(*this->car, *this->ui);
    this->setPage(2);
}

void MainWidget::on_CALCULATOR_BUTTON_clicked() {
    UIController::switchActiveCalculationFields(Calculator::translateIndexToType(ui->CALCULATOR_OPERATION_PICK->currentIndex()), *this->ui);
    this->setPage(3);
}

void MainWidget::on_CALCULATOR_CALCULATE_BUTTON_clicked() {
    Calculator::CalculationType t = Calculator::translateIndexToType(ui->CALCULATOR_OPERATION_PICK->currentIndex());
    float result = 0;
    switch (t) {
        case Calculator::TRIP_PRICE:
            result = Calculator::tripPrice(
                        ui->CALCULATOR_DISTANCE_VALUE->value(),
                        ui->CALCULATOR_FUEL_PRICE_VALUE->value(),
                        ui->CALCULATOR_FUEL_CONSUMPTION_VALUE->value());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_RIDE_PRICE_VALUE);
        break;
        case Calculator::DISTANCE:
            result = Calculator::distance(ui->CALCULATOR_NEEDED_FUEL_VALUE->value(),
                                          ui->CALCULATOR_FUEL_CONSUMPTION_VALUE->value());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_DISTANCE_VALUE);
        break;
        case Calculator::FUEL_CONSUMPTION:
            result = Calculator::fuelConsumptionUnit(ui->CALCULATOR_DISTANCE_VALUE->value(),
                                                     ui->CALCULATOR_NEEDED_FUEL_VALUE->value());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_FUEL_CONSUMPTION_VALUE);
        break;
        case Calculator::NEEDED_FUEL:
            result = Calculator::neededFuel(ui->CALCULATOR_DISTANCE_VALUE->value(),
                                            ui->CALCULATOR_FUEL_CONSUMPTION_VALUE->value());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_NEEDED_FUEL_VALUE);
        break;
    }
}

void MainWidget::setPage(int index) {
    UIController::setPage(*this->ui->APP_CONTENT, index);
}


void MainWidget::on_DELETE_BUTTON_clicked() {
    if (this->car->remove()) {
        this->loadingData = true;
        UIController::loadCarList(this->ui->SELECT_CAR);
        this->loadingData = false;
    }
}


void MainWidget::on_ADD_PETROL_clicked() {
    NewFuelingForm * fueling = new NewFuelingForm(this, this->car);
    fueling->exec();
    UIController::loadHomePage(*this->car, *this->ui);
    this->car->save();
}


void MainWidget::on_REMOVE_PETROL_clicked() {
    QVector<Expense*> exList = this->car->getExpenses();
    QVector<Expense*>::Iterator it = exList.begin();
    if (!this->ui->PETROL_LIST->currentItem()) return;
    while (it != exList.end()) {
        Expense *ex = *it;
        QString name = this->ui->PETROL_LIST->currentItem()->text().split("-").at(0);
        if (ex->getName() == name) {
            this->car->removeExpense(exList.indexOf(*it));
            break;
        }
        it++;
    }
    this->car->save();
    UIController::loadHomePage(*this->car, *this->ui);
}


void MainWidget::on_ADD_EXPENSE_clicked() {
    NewExpenseForm * expense = new NewExpenseForm(this, this->car);
    expense->exec();
    this->car->save();
    UIController::loadHomePage(*this->car, *this->ui);
}


void MainWidget::on_REMOVE_EXPENSE_clicked() {
    QVector<Expense*> exList = this->car->getExpenses();
    QVector<Expense*>::Iterator it = exList.begin();
    if (!this->ui->EXPENSES_LIST->currentItem()) return;
    QString name = this->ui->EXPENSES_LIST->currentItem()->text().split("-").at(0);
    while (it != exList.end()) {
        Expense *ex = *it;
        if (ex->getName() == name) {
            this->car->removeExpense(exList.indexOf(*it));
            break;
        }
        it++;
    }
    this->car->save();
    UIController::loadHomePage(*this->car, *this->ui);
}


void MainWidget::on_SERVICE_OIL_CHANGE_UPDATE_BTN_clicked() {
    OilChange *oc = new OilChange(this, &this->car->getService());
    oc->exec();
    this->car->save();
}

