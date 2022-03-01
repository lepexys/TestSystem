#ifndef TESTSYSTEM_REACTOR_H
#define TESTSYSTEM_REACTOR_H

#include "qcustomplot.h"
#include "DataStorage.h"
#include "IWidget.h"

class Reactor : public IWidget {
    shared_ptr<QCustomPlot> reactorPlot = make_shared<QCustomPlot>();
    unique_ptr<double> aParam = make_unique<double>(0.0042);
    unique_ptr<int> hParam = make_unique<int>(325);
    unique_ptr<int> mParam = make_unique<int>(20);
    unique_ptr<int> dParam = make_unique<int>(50);

    void draw();

    double reactorFunction(double x);

public:
    explicit Reactor(shared_ptr<DataStorage>);

    void aParamChanged(double newValue);

    void hParamChanged(int newValue);

    void mParamChanged(int newValue);

    void dParamChanged(int newValue);
};

#endif //TESTSYSTEM_REACTOR_H
