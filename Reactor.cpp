#include "Reactor.h"

Reactor::Reactor(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> parametersLabel = make_shared<QLabel>("Парамеры реактора");
    addWidget(parametersLabel, QRect(0, 0, 100, 60));

    addLayout(make_shared<QHBoxLayout>());
    addLayout(make_shared<QVBoxLayout>(), 2);

    shared_ptr<QLabel> aParamLabel = make_shared<QLabel>("A");
    addWidget(aParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QDoubleSpinBox> aParamCounter = make_shared<QDoubleSpinBox>();
    aParamCounter->setRange(0.004, 0.0045);
    aParamCounter->setSingleStep(0.0001);
    connect(aParamCounter.get(), &QDoubleSpinBox::valueChanged, this, &Reactor::aParamChanged);
    addWidget(aParamCounter, QRect(0, 0, 200, 60), 3);

    shared_ptr<QLabel> hParamLabel = make_shared<QLabel>("H");
    addWidget(hParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QSpinBox> hParamCounter = make_shared<QSpinBox>();
    hParamCounter->setRange(300, 350);
    hParamCounter->setSingleStep(5);
    connect(hParamCounter.get(), &QSpinBox::valueChanged, this, &Reactor::hParamChanged);
    addWidget(hParamCounter, QRect(0, 0, 200, 60), 3);

    shared_ptr<QLabel> mParamLabel = make_shared<QLabel>("M");
    addWidget(mParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QSpinBox> mParamCounter = make_shared<QSpinBox>();
    mParamCounter->setRange(10, 30);
    mParamCounter->setSingleStep(2);
    connect(mParamCounter.get(), &QSpinBox::valueChanged, this, &Reactor::mParamChanged);
    addWidget(mParamCounter, QRect(0, 0, 200, 60), 3);

    shared_ptr<QLabel> dParamLabel = make_shared<QLabel>("D");
    addWidget(dParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QSpinBox> dParamCounter = make_shared<QSpinBox>();
    dParamCounter->setRange(0, 100);
    dParamCounter->setSingleStep(5);
    connect(dParamCounter.get(), &QSpinBox::valueChanged, this, &Reactor::dParamChanged);
    addWidget(dParamCounter, QRect(0, 0, 200, 60), 3);

    reactorPlot->addGraph();
    reactorPlot->graph(0)->setPen(QPen(Qt::red));
    reactorPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    reactorPlot->graph(0)->rescaleAxes(true);
    reactorPlot->xAxis2->setVisible(true);
    reactorPlot->yAxis2->setVisible(true);
    reactorPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    reactorPlot->setMinimumSize(QSize(300, 280));
    reactorPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(reactorPlot, QRect(0, 0, 100, 60));

    draw();
}

void Reactor::draw() {
    int limit = *hParam + *dParam;
    QVector<double> x(limit), y(limit);
    std::iota(x.begin(), x.end(), 0);
    std::transform(x.begin(), x.end(), y.begin(), [=](double x) { return reactorFunction(x); });
    reactorPlot->graph(0)->setData(x, y);
    reactorPlot->rescaleAxes();
}

double Reactor::reactorFunction(double x) {
    if (x < *hParam) {
        return std::cos(*aParam * x);
    } else {
        return std::cos(*aParam * *hParam)
               * std::sinh((*hParam + *dParam - x) / *mParam)
               / std::sinh(*dParam / *mParam);
    }
}

void Reactor::aParamChanged(double newValue) {
    *aParam = newValue;
    draw();
}

void Reactor::hParamChanged(int newValue) {
    *hParam = newValue;
    draw();
}

void Reactor::mParamChanged(int newValue) {
    *mParam = newValue;
    draw();
}

void Reactor::dParamChanged(int newValue) {
    *dParam = newValue;
    draw();
}
