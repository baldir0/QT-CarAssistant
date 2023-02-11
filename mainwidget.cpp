#include "mainwidget.h"
#include "./ui_mainwidget.h"
#include "uicontroller.h"
#include "newcarform.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // LOAD FILES TO LIST
    this->fm = new FileManager();
    this->fm->checkSaveLocalization();
    this->loadingData = true;
    UIController::loadCarList(this->ui->SELECT_CAR);
    this->loadingData = false;

    this->ui->SELECT_CAR->setCurrentIndex(0);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_SELECT_CAR_currentIndexChanged(int index)
{
    if (index < 0 || loadingData) return;
    qDebug() << "Total Elements: " << this->ui->SELECT_CAR->count() << "Current Index:" << index;
    if (index == this->ui->SELECT_CAR->count() - 1) {
        qDebug() << "Add New Car";
        NewCarForm *form = new NewCarForm(this);
        form->exec();
        if (form->result()) {
            qDebug() << "Loading Car List";
            UIController::loadCarList(this->ui->SELECT_CAR);
        }
        qDebug() << "Result:" << form->result();
        return;
    }

    qDebug() << "Loading Car Info...";
    this->car = new Car(this->ui->SELECT_CAR->currentText());
    this->car->load();
    UIController::loadStatisticsPage(*this->car, *this->ui);
    UIController::loadServicePage(*this->car, *this->ui);
}

void MainWidget::on_CALCULATOR_OPERATION_PICK_currentIndexChanged(int index) {
    UIController::switchActiveCalculationFields(Calculator::translateIndexToType(index), *this->ui);
}

void MainWidget::on_HOME_BUTTON_clicked() {
    this->setPage(0);
}

void MainWidget::on_STATISTICS_BUTTON_clicked() {
    this->setPage(1);
}

void MainWidget::on_SERVICE_BUTTON_clicked() {
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
            result = Calculator::tripPrice(ui->CALCULATOR_DISTANCE_VALUE->text().toFloat(), ui->CALCULATOR_FUEL_PRICE_VALUE->text().toFloat(), ui->CALCULATOR_FUEL_CONSUMPTION_VALUE->text().toFloat());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_RIDE_PRICE_VALUE);
        break;
        case Calculator::DISTANCE:
            result = Calculator::distance(ui->CALCULATOR_NEEDED_FUEL_VALUE->text().toFloat(), ui->CALCULATOR_FUEL_CONSUMPTION_VALUE->text().toFloat());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_DISTANCE_VALUE);
        break;
        case Calculator::FUEL_CONSUMPTION:
            result = Calculator::fuelConsumptionUnit(ui->CALCULATOR_DISTANCE_VALUE->text().toFloat(), ui->CALCULATOR_NEEDED_FUEL_VALUE->text().toFloat());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_FUEL_CONSUMPTION_VALUE);
        break;
        case Calculator::NEEDED_FUEL:
            result = Calculator::neededFuel(ui->CALCULATOR_DISTANCE_VALUE->text().toFloat(), ui->CALCULATOR_FUEL_CONSUMPTION_VALUE->text().toFloat());
            UIController::setLineEditValue(QString::number(result), ui->CALCULATOR_NEEDED_FUEL_VALUE);
        break;
    }
}

void MainWidget::setPage(int index) {
    UIController::setPage(*this->ui->APP_CONTENT, index);
}

