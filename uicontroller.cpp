#include "uicontroller.h"

#include "savemanager.h"
#include "filemanager.h"

void UIController::loadCarList(QComboBox *list) {
    QMap<int, QString> carList = SaveManager::load(FileManager::getSaveLocation() + "list.dat");
    list->clear();
    QMapIterator<int, QString> it(carList);
    while (it.hasNext()) {
        it.next();
        list->addItem(it.value());
    }
    list->addItem("Add Car");
    if (list->count() == 1) list->setCurrentIndex(-1);
}

void UIController::setPage(QStackedWidget & container, int pageIndex) {
    container.setCurrentIndex(pageIndex);
}

void UIController::loadStatisticsPage(Car & obj, Ui::MainWidget & ui) {
    ui.CAR_DISPLAY_NAME_VALUE->setText(obj.getName());
    ui.CAR_ENGINE_CAPACITY_VALUE->setText(QString::number(obj.getService().getEngineCapacity()) + " l");
    ui.CAR_DESCRIPTION_VALUE->setText(obj.getDescription());
    ui.CAR_BRAND_VALUE->setText(obj.getBrand());
    ui.CAR_MODEL_VALUE->setText(obj.getModel());
    ui.CAR_TANK_CAPACITY_VALUE->setText(QString::number(obj.getService().getTankCapacity()) + " l");
    ui.CAR_PRODUCTION_DATE_VALUE->setDate(QDate::fromString(obj.getService().getProductionDate(), "dd.MM.yyyy"));
}

void UIController::loadServicePage(Car & obj, Ui::MainWidget & ui) {
    ui.SERVICE_LAST_OIL_CHANGE_DATE_VALUE->setDate(QDate::fromString(obj.getService().getOilChangeDate(), "dd.MM.yyyy"));
    ui.SERVICE_LAST_OIL_CHANGE_MILEAGE_VALUE->setText(0);
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
}

void UIController::switchActiveCalculationFields(Calculator::CalculationType calculationType, Ui::MainWidget & ui) {
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
