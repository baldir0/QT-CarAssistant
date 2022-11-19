#ifndef MENU_H
#define MENU_H

class Menu
{
    private:
        int currentState = 0;
        enum MenuStates{
            mainMenu = 0,
            expenses = 1,
            statistics = 2,
            calculator = 4
        };
    public:
        Menu();

        void setState(MenuStates state);
        void update();
};

#endif // MENU_H
