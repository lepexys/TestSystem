#include "MainMenu.h"

MainMenu::MainMenu() : IWidget() {
    addButton(QRect(0, 0, 100, 60), "Тестирование", funcTest);
    addButton(QRect(0, 0, 100, 60), "Статистика", funcVisual);
    addButton(QRect(0, 0, 100, 60), "Реактор", funcReactor);
    addButton(QRect(0, 0, 100, 60), "Решатель", funcSolver);
    addButton(QRect(0, 0, 100, 60), "Справка", funcHelp);
    addButton(QRect(0, 0, 100, 60), "Выход", funcExit);
}

void MainMenu::funcTest(QWidget *, shared_ptr<DataStorage> storage) {
    Tester *tester = new Tester(storage);
    tester->show();
}

void MainMenu::funcVisual(QWidget *, shared_ptr<DataStorage> storage) {
    Visualisation *visual = new Visualisation(storage);
    visual->show();
}

void MainMenu::funcReactor(QWidget *, shared_ptr<DataStorage> storage) {
    Reactor *reactor = new Reactor(storage);
    reactor->show();
}

void MainMenu::funcSolver(QWidget *, shared_ptr<DataStorage> storage) {
    Solver *solver = new Solver(storage);
    solver->show();
}

void MainMenu::funcHelp(QWidget *, shared_ptr<DataStorage> storage) {
    Helper *help = new Helper(storage);
    help->show();
}

void MainMenu::funcExit(QWidget *widget, shared_ptr<DataStorage> storage) {
    storage->Save(QDir::current().path() + "newFile.xlsx");
    widget->close();
}

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainMenu mainMenu;
    mainMenu.show();
    return application.exec();
}
