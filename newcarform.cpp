#include "newcarform.h"
#include "ui_newcarform.h"
#include "savemanager.h"
#include "filemanager.h"
#include "car.h"

NewCarForm::NewCarForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCarForm)
{
    ui->setupUi(this);
}

NewCarForm::~NewCarForm()
{
    delete ui;
}

void NewCarForm::on_NEW_CAR_FORM_BUTTONS_accepted()
{
    // READ DATA FROM FIELDS;


    QMap<int, QString> carList = SaveManager::load(FileManager::getSaveLocation() + "list.dat");
    if (!carList.isEmpty() && carList.values().contains(this->ui->CAR_NAME_VALUE->text()))
        return;

    Car *car = new Car(this->ui->CAR_NAME_VALUE->text(),
                       this->ui->DESCRIPTION_VALUE->text(),
                       this->ui->MODEL_VALUE->text(),
                       this->ui->BRAND_VALUE->text(),
                       this->ui->PRODUCTION_DATE_VALUE->text(),
                       this->ui->INSURANCE_DATE_VALUE->text(),
                       this->ui->OIL_CHANGE_DATE_VALUE->text(),
                       this->ui->SERVICE_DATE_VALUE->text(),
                       this->ui->TANK_CAPACITY_VALUE->text().toShort(),
                       this->ui->ENGINE_CAPACITY_VALUE->text().toFloat(),
                       Service::FuelType(this->ui->FUEL_TYPE_VALUE->currentIndex()));
    car->save();

    if (carList.isEmpty()) {
        carList.insert(0, this->ui->CAR_NAME_VALUE->text());
    } else {
        carList.insert(carList.lastKey() + 1, this->ui->CAR_NAME_VALUE->text());
    }

    SaveManager::save(FileManager::getSaveLocation() + "list.dat", carList);
}
