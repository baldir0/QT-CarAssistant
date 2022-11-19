#include "menu.h"

Menu::Menu()
{

}

void Menu::setState(MenuStates state) {
    this->currentState = state;
}

void Menu::update() {
    switch(currentState) {
        case mainMenu:
            MainMenuUI();
        break;
        case expenses:
            ExpensesUI();
        break;
        case statistics:
            StatisticsUI();
        break;
        case calculator:
            CalculatorUI();
        break;
    }
    return;
}

