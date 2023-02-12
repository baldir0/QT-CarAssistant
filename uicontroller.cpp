#include "uicontroller.h"

#include "savemanager.h"
#include "filemanager.h"
#include "logger.h"

void UIController::loadCarList(QComboBox *list) {
    Logger::log<UIController>("Loading Car List ...");
    QMap<int, QString> carList = SaveManager::load(FileManager::getSaveLocation() + "list.dat");
    list->clear();
    QMapIterator<int, QString> it(carList);
    while (it.hasNext()) {
        it.next();
        list->addItem(it.value());
    }
    list->addItem("Add Car");
    if (list->count() == 1) list->setCurrentIndex(-1);
    Logger::log<UIController>("Car List Loaded!");
}

void UIController::setPage(QStackedWidget & container, int pageIndex) {
    container.setCurrentIndex(pageIndex);
}

void UIController::loadStatisticsPage(Car & obj, Ui::MainWidget & ui) {
    Logger::log<UIController>("Loading Statistics Page ...");
    ui.CAR_DISPLAY_NAME_VALUE->setText(obj.getName());
    ui.CAR_ENGINE_CAPACITY_VALUE->setText(QString::number(obj.getService().getEngineCapacity()) + " l");
    ui.CAR_DESCRIPTION_VALUE->setText(obj.getDescription());
    ui.CAR_BRAND_VALUE->setText(obj.getBrand());
    ui.CAR_MODEL_VALUE->setText(obj.getModel());
    ui.CAR_TANK_CAPACITY_VALUE->setText(QString::number(obj.getService().getTankCapacity()) + " l");
    ui.CAR_PRODUCTION_DATE_VALUE->setDate(QDate::fromString(obj.getService().getProductionDate(), "dd.MM.yyyy"));
    Logger::log<UIController>("Statistics Page Loaded!");
}

void UIController::loadServicePage(Car & obj, Ui::MainWidget & ui) {
    Logger::log<UIController>("Lading Service Page ...");
    ui.SERVICE_LAST_OIL_CHANGE_DATE_VALUE->setDate(QDate::fromString(obj.getService().getOilChangeDate(), "dd.MM.yyyy"));
    ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_VALUE->setText(QString::number(obj.getService().getOilChangeMileage()));
    ui.SERVICE_DATE_VALUE->setDate(QDate::fromString(obj.getService().getServiceDate(), "dd.MM.yyyy"));
    ui.SERVICE_INSURANCE_DATE_VALUE->setDate(QDate::fromString(obj.getService().getInsuranceDate(), "dd.MM.yyyy"));
    ui.SERVICE_FUEL_TYPE_VALUE->setText(obj.getService().getFuelTypeName());
    ui.SERVICE_ENGINE_CAPACITY_VALUE->setText(QString::number(obj.getService().getEngineCapacity()) + " l");
    ui.SERVICE_TANK_CAPACITY_VALUE->setText(QString::number(obj.getService().getTankCapacity()) + " l");

    if (obj.getService().checkOilChangeDate()) {
        ui.SERVICE_LAST_OIL_CHANGE_DATE_STATUS->setText("Ok");
        ui.SERVICE_LAST_OIL_CHANGE_DATE_STATUS->setStyleSheet("color: green");
    } else {
        int days = ui.SERVICE_LAST_OIL_CHANGE_DATE_VALUE->date().daysTo(QDate::currentDate());
        ui.SERVICE_LAST_OIL_CHANGE_DATE_STATUS->setText("There is " + QString::number(days) + " day(s) from your last Oil Change");
        ui.SERVICE_LAST_OIL_CHANGE_DATE_STATUS->setStyleSheet("color: red");
    }

    if (obj.getService().checkInsuranceDate()) {
        ui.SERVICE_INSURANCE_DATE_STATUS->setText("Ok");
        ui.SERVICE_INSURANCE_DATE_STATUS->setStyleSheet("color: green");
    } else {
        int days = ui.SERVICE_INSURANCE_DATE_VALUE->date().daysTo(QDate::currentDate());
        ui.SERVICE_INSURANCE_DATE_STATUS->setText("There is " + QString::number(days) + " day(s) from your Insurance Expired");
        ui.SERVICE_INSURANCE_DATE_STATUS->setStyleSheet("color: red");
    }

    if (obj.getService().checkServiceDate()) {
        ui.SERVICE_DATE_STATUS->setText("Ok");
        ui.SERVICE_DATE_STATUS->setStyleSheet("color: green");
    } else {
        int days = ui.SERVICE_DATE_VALUE->date().daysTo(QDate::currentDate());
        ui.SERVICE_DATE_STATUS->setText("There is " + QString::number(days) + " day(s) from your last Service Check");
        ui.SERVICE_DATE_STATUS->setStyleSheet("color: red");
    }

    if (obj.getService().checkOilChangeMileage()) {
        ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_STATUS->setText("Ok");
        ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_STATUS->setStyleSheet("color: green");
    } else {
        int km = ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_VALUE->text().toInt();
        ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_STATUS->setText("There is " + QString::number(km) + " km(s) from your last oil change!");
        ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_STATUS->setStyleSheet("color: red");
    }

    Logger::log<UIController>("Service Page Loaded!");
}

void UIController::loadHomePage(Car & obj, Ui::MainWidget & ui) {
    Logger::log<UIController>("Loading Home Page ...");

    QVector<Expense*> expensesList = obj.getExpenses();
    QVectorIterator<Expense*> expense(expensesList);
    ui.EXPENSES_LIST->clear();
    ui.PETROL_LIST->clear();
    while (expense.hasNext()) {
        Expense *ex = expense.next();
        ui.EXPENSES_LIST->addItem(new QListWidgetItem(ex->getName() + "-" + ex->getDate() + "-" + QString::number(ex->getExpense())));
        if (ex->getExpenseType() == Expense::REFUELING)
            ui.PETROL_LIST->addItem(new QListWidgetItem(ex->getName() + "-" + ex->getDate() + "-" + QString::number(ex->getExpense())));
    }


    Logger::log<UIController>("Home Page Loaded!");
}

void UIController::switchActiveCalculationFields(Calculator::CalculationType calculationType, Ui::MainWidget & ui) {
    Logger::log<UIController>("Switching calculator fields ...");
    switch (calculationType) {
    case Calculator::TRIP_PRICE:
        setEnableCalculatorField(ui.CALCULATOR_DISTANCE_LABEL, ui.CALCULATOR_DISTANCE_VALUE, ui.CALCULATOR_DISTANCE_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_CONSUMPTION_LABEL, ui.CALCULATOR_FUEL_CONSUMPTION_VALUE, ui.CALCULATOR_FUEL_CONSUMPTION_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_PRICE_LABEL, ui.CALCULATOR_FUEL_PRICE_VALUE, ui.CALCULATOR_FUEL_PRICE_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_NEEDED_FUEL_LABEL, ui.CALCULATOR_NEEDED_FUEL_VALUE, ui.CALCULATOR_NEEDED_FUEL_UNIT_LABEL, false);
        setEnableCalculatorField(ui.CALCULATOR_RIDE_PRICE_LABEL, ui.CALCULATOR_RIDE_PRICE_VALUE, ui.CALCULATOR_RIDE_PRICE_UNIT_LABEL, true, true);
        break;
    case Calculator::DISTANCE:
        setEnableCalculatorField(ui.CALCULATOR_DISTANCE_LABEL, ui.CALCULATOR_DISTANCE_VALUE, ui.CALCULATOR_DISTANCE_UNIT_LABEL, true, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_CONSUMPTION_LABEL, ui.CALCULATOR_FUEL_CONSUMPTION_VALUE, ui.CALCULATOR_FUEL_CONSUMPTION_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_PRICE_LABEL, ui.CALCULATOR_FUEL_PRICE_VALUE, ui.CALCULATOR_FUEL_PRICE_UNIT_LABEL, false);
        setEnableCalculatorField(ui.CALCULATOR_NEEDED_FUEL_LABEL, ui.CALCULATOR_NEEDED_FUEL_VALUE, ui.CALCULATOR_NEEDED_FUEL_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_RIDE_PRICE_LABEL, ui.CALCULATOR_RIDE_PRICE_VALUE, ui.CALCULATOR_RIDE_PRICE_UNIT_LABEL, false);
        break;
    case Calculator::FUEL_CONSUMPTION:
        setEnableCalculatorField(ui.CALCULATOR_DISTANCE_LABEL, ui.CALCULATOR_DISTANCE_VALUE, ui.CALCULATOR_DISTANCE_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_CONSUMPTION_LABEL, ui.CALCULATOR_FUEL_CONSUMPTION_VALUE, ui.CALCULATOR_FUEL_CONSUMPTION_UNIT_LABEL, true, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_PRICE_LABEL, ui.CALCULATOR_FUEL_PRICE_VALUE, ui.CALCULATOR_FUEL_PRICE_UNIT_LABEL, false);
        setEnableCalculatorField(ui.CALCULATOR_NEEDED_FUEL_LABEL, ui.CALCULATOR_NEEDED_FUEL_VALUE, ui.CALCULATOR_NEEDED_FUEL_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_RIDE_PRICE_LABEL, ui.CALCULATOR_RIDE_PRICE_VALUE, ui.CALCULATOR_RIDE_PRICE_UNIT_LABEL, false);
        break;
    case Calculator::NEEDED_FUEL:
        setEnableCalculatorField(ui.CALCULATOR_DISTANCE_LABEL, ui.CALCULATOR_DISTANCE_VALUE, ui.CALCULATOR_DISTANCE_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_CONSUMPTION_LABEL, ui.CALCULATOR_FUEL_CONSUMPTION_VALUE, ui.CALCULATOR_FUEL_CONSUMPTION_UNIT_LABEL, true);
        setEnableCalculatorField(ui.CALCULATOR_FUEL_PRICE_LABEL, ui.CALCULATOR_FUEL_PRICE_VALUE, ui.CALCULATOR_FUEL_PRICE_UNIT_LABEL, false);
        setEnableCalculatorField(ui.CALCULATOR_NEEDED_FUEL_LABEL, ui.CALCULATOR_NEEDED_FUEL_VALUE, ui.CALCULATOR_NEEDED_FUEL_UNIT_LABEL, true, true);
        setEnableCalculatorField(ui.CALCULATOR_RIDE_PRICE_LABEL, ui.CALCULATOR_RIDE_PRICE_VALUE, ui.CALCULATOR_RIDE_PRICE_UNIT_LABEL, false);
        break;
    }
    Logger::log<UIController>("Calculator fields switched!");
}

void UIController::setEnableCalculatorField(QLabel *label, QLineEdit *input, QLabel *unitLabel, bool enabled, bool readOnly)
{
    label->setEnabled(enabled);
    input->setEnabled(enabled);
    input->setReadOnly(readOnly);
    unitLabel->setEnabled(enabled);
}

void UIController::setLineEditValue(QString value, QLineEdit *input) {
    input->setText(value);
}
