#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "filemanager.h"
#include "car.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_SELECT_CAR_currentIndexChanged(int index);

    void on_HOME_BUTTON_clicked();

    void on_STATISTICS_BUTTON_clicked();

    void on_SERVICE_BUTTON_clicked();

    void on_CALCULATOR_BUTTON_clicked();

    void on_CALCULATOR_OPERATION_PICK_currentIndexChanged(int index);

    void on_CALCULATOR_CALCULATE_BUTTON_clicked();

    void setPage(int index);

private:
    bool loadingData = false;
    Ui::MainWidget *ui;
    FileManager *fm;
    Car *car;
};
#endif // MAINWIDGET_H
