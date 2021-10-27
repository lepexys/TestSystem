#include "testui.h"

Visualisation::Visualisation(shared_ptr<DataStorage> strg)
    :IWidget(strg)
{
    shared_ptr<QLabel> txtedit = make_shared<QLabel>("График считанных данных");
    addWidget(txtedit,QRect(0,0,100,60));
    addLayout(make_shared<QGridLayout>());
    shared_ptr<QCustomPlot> cplot = make_shared<QCustomPlot>();
    cplot.get()->addGraph();
    cplot->graph(0)->setPen(QPen(Qt::blue));
    cplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    QVector<double> x, y;
    for (int i=0; i<storage.get()->data.size(); ++i)
    {
        if(storage.get()->data[i].first.length() == 6)
            x.append(QDate(storage.get()->data[i].first[2].toInt(),storage.get()->data[i].first[1].toInt(),storage.get()->data[i].first[0].toInt()).dayOfYear());
        if(storage.get()->data[i].first.length() == 2)
            x.append((storage.get()->data[i].first[0]+'.'+storage.get()->data[i].first[1]).toDouble());
        if(storage.get()->data[i].second.length() == 6)
            y.append(QDate(storage.get()->data[i].second[2].toInt(),storage.get()->data[i].second[1].toInt(),storage.get()->data[i].second[0].toInt()).dayOfYear());
        if(storage.get()->data[i].second.length() == 2)
            y.append((storage.get()->data[i].second[0]+'.'+storage.get()->data[i].second[1]).toDouble());
    }
    cplot->xAxis2->setVisible(true);
    cplot->yAxis2->setVisible(true);
    cplot->graph(0)->setData(x, y);
    cplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    cplot->graph(0)->rescaleAxes(true);
    cplot->setMinimumSize(QSize(300,280));
    cplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(cplot,QRect(0,0,100,60),0,0,2);
}
