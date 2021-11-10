#ifndef TESTSYSTEM_VISUALISATION_H
#define TESTSYSTEM_VISUALISATION_H


#include "qcustomplot.h"
#include "DataStorage.h"
#include "IWidget.h"

class Visualisation : public IWidget {
    shared_ptr<QCustomPlot> cplot;
public:
    explicit Visualisation(shared_ptr<DataStorage>);

    static void funcAutocorrelation(QWidget *, shared_ptr<DataStorage>);

    static void funcCorrelation(QWidget *, shared_ptr<DataStorage>);
};


#endif //TESTSYSTEM_VISUALISATION_H
