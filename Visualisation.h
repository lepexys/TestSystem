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

    static void saveData(QWidget *, shared_ptr<DataStorage>);

    static void interpolationNewton(QWidget *, shared_ptr<DataStorage>);

    static void interpolationSplines(QWidget *, shared_ptr<DataStorage>);

    static void interpolationLSM(QWidget *, shared_ptr<DataStorage>);

    static void histogramView(QWidget *, shared_ptr<DataStorage>);

};


#endif //TESTSYSTEM_VISUALISATION_H
//QVector<double> &data, const shared_ptr<QCustomPlot> &plot
