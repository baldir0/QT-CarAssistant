#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QComboBox>
#include <QStackedWidget>

#include "calculator.h"
#include "car.h"
#include "ui_mainwidget.h"

class UIController
{
    public:
        static void loadCarList(QComboBox *list);
        static void setPage(QStackedWidget & container, int pageIndex);

        static void loadStatisticsPage(Car & obj, Ui::MainWidget & ui);
        static void loadServicePage(Car & obj, Ui::MainWidget & ui);
        static void loadHomePage(Car & obj, Ui::MainWidget & ui);
        static void switchActiveCalculationFields(Calculator::CalculationType calculationType, Ui::MainWidget & ui);
        static void setLineEditValue(QString value, QDoubleSpinBox *input);

public slots:

private:
        static void setEnableCalculatorField(QLabel *label, QDoubleSpinBox *input, bool enabled = false, bool readOnly = false);
};

#endif // UICONTROLLER_H
