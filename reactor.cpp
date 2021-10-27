#include "testui.h"

Reactor::Reactor(shared_ptr<DataStorage> strg)
    :IWidget(strg)
{
    shared_ptr<QLabel> txtedit = make_shared<QLabel>("Парамеры реактора");
    addWidget(txtedit,QRect(0,0,100,60));
    addLayout(make_shared<QHBoxLayout>());
    shared_ptr<QLabel> img = make_shared<QLabel>();
    QPixmap pixmap("reactor.jpg");
    img->setPixmap(pixmap);
    addWidget(img,QRect(0,0,200,200),2);
    addLayout(make_shared<QVBoxLayout>(),2);
    shared_ptr<QLabel> labl1 = make_shared<QLabel>("Параметр 1");
    addWidget(labl1,QRect(0,0,200,60),3);
    shared_ptr<QDoubleSpinBox> spnbox1 = make_shared<QDoubleSpinBox>();
    addWidget(spnbox1,QRect(0,0,200,60),3);
    shared_ptr<QLabel> labl2 = make_shared<QLabel>("Параметр 2");
    addWidget(labl2,QRect(0,0,200,60),3);
    shared_ptr<QDoubleSpinBox> spnbox2 = make_shared<QDoubleSpinBox>();
    addWidget(spnbox2,QRect(0,0,200,60),3);
    shared_ptr<QLabel> labl3 = make_shared<QLabel>("Параметр 3");
    addWidget(labl3,QRect(0,0,200,60),3);
    shared_ptr<QDoubleSpinBox> spnbox3 = make_shared<QDoubleSpinBox>();
    addWidget(spnbox3,QRect(0,0,200,60),3);
    shared_ptr<QLabel> reactorGrpaph = make_shared<QLabel>("График");
    addWidget(reactorGrpaph,QRect(0,0,100,60));
    shared_ptr<QCustomPlot> cplot = make_shared<QCustomPlot>();
    cplot.get()->addGraph();
    cplot->graph(0)->setPen(QPen(Qt::blue));
    cplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    QVector<double> x(251), y(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = i;
      y[i] = exp(i/100)+exp((100+i)/100);
    }
    cplot->xAxis2->setVisible(true);
    cplot->yAxis2->setVisible(true);
    cplot->graph(0)->setData(x, y);
    cplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    cplot->graph(0)->rescaleAxes(true);
    cplot->setMinimumSize(QSize(300,280));
    cplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(cplot,QRect(0,0,100,60));
}
