#ifndef OILCHANGE_H
#define OILCHANGE_H

#include <QDialog>
#include "service.h"

namespace Ui {
class OilChange;
}

class OilChange : public QDialog
{
    Q_OBJECT

public:
    explicit OilChange(QWidget *parent = nullptr, Service * service = nullptr);
    ~OilChange();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OilChange *ui;
    Service * service;
};

#endif // OILCHANGE_H
