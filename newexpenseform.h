#ifndef NEWEXPENSEFORM_H
#define NEWEXPENSEFORM_H

#include <QDialog>
#include "car.h"

namespace Ui {
class NewExpenseForm;
}

class NewExpenseForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewExpenseForm(QWidget *parent = nullptr, Car *obj = nullptr);
    ~NewExpenseForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewExpenseForm *ui;
    Car *car;
};

#endif // NEWEXPENSEFORM_H
