#include "oilchange.h"
#include "ui_oilchange.h"

OilChange::OilChange(QWidget *parent, Service * service) :
    QDialog(parent),
    ui(new Ui::OilChange)
{
    ui->setupUi(this);
    this->service = service;
}

OilChange::~OilChange()
{
    delete ui;
}

void OilChange::on_buttonBox_accepted()
{
    this->service->setOilChangeDate(ui->DATE->text());
    this->service->setOilChangeMileage(ui->MILEAGE->value());
}

