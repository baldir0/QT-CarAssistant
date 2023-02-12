#ifndef NEWFUELINGFORM_H
#define NEWFUELINGFORM_H

#include <QDialog>
#include <car.h>

namespace Ui {
class NewFuelingForm;
}

class NewFuelingForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewFuelingForm(QWidget *parent = nullptr, Car *obj = nullptr);
    ~NewFuelingForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewFuelingForm *ui;
    Car * car;
};

#endif // NEWFUELINGFORM_H
