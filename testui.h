#ifndef TESTUI_H
#define TESTUI_H

#include "IWidget.h"

using namespace std;

class Visualisation : public IWidget {
    shared_ptr<QCustomPlot> cplot;
    static int getDay(const QStringList &i);
    static double getValue(const QStringList &i);

public:
    explicit Visualisation(shared_ptr<DataStorage>);
    static void funcAutocorrelation(QWidget *, shared_ptr<DataStorage>);
    static void funcCorrelation(QWidget *, shared_ptr<DataStorage>);
};

class Correlator : public IWidget {
public:
    explicit Correlator(shared_ptr<DataStorage>);
};

class Interpolator : public IWidget {
public:
    explicit Interpolator(shared_ptr<DataStorage>);
};

class Tester : public IWidget {
public:
    explicit Tester(shared_ptr<DataStorage> = make_shared<DataStorage>());
};

class Reactor : public IWidget {
public:
    explicit Reactor(shared_ptr<DataStorage> = make_shared<DataStorage>());
};

class Helper : public IWidget {
public:
    explicit Helper(shared_ptr<DataStorage> = make_shared<DataStorage>());
};

#endif // TESTUI_H
