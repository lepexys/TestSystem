#ifndef TESTSYSTEM_MAINMENU_H
#define TESTSYSTEM_MAINMENU_H

#include "IWidget.h"
#include "Visualisation.h"
#include "testui.h"
#include "Reactor.h"
#include "Solver.h"

class MainMenu : public IWidget {
public:
    MainMenu();

public slots:

    static void funcTest(QWidget *, shared_ptr<DataStorage>);

    static void funcVisual(QWidget *, shared_ptr<DataStorage>);

    static void funcReactor(QWidget *, shared_ptr<DataStorage>);

    static void funcSolver(QWidget *, shared_ptr<DataStorage>);

    static void funcHelp(QWidget *, shared_ptr<DataStorage>);

    static void funcExit(QWidget *, shared_ptr<DataStorage>);
};

#endif //TESTSYSTEM_MAINMENU_H
