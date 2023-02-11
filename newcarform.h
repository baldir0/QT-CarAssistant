#ifndef NEWCARFORM_H
#define NEWCARFORM_H

#include <QDialog>

namespace Ui {
class NewCarForm;
}

class NewCarForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewCarForm(QWidget *parent = nullptr);
    ~NewCarForm();

private slots:
    void on_NEW_CAR_FORM_BUTTONS_accepted();

private:
    Ui::NewCarForm *ui;
};

#endif // NEWCARFORM_H
