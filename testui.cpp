#include "testui.h"

Reactor::Reactor(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> parametersLabel = make_shared<QLabel>("Парамеры реактора");
    addWidget(parametersLabel, QRect(0, 0, 100, 60));
    addLayout(make_shared<QHBoxLayout>());
    shared_ptr<QLabel> img = make_shared<QLabel>();
    QPixmap pixmap("reactor.jpg");
    img->setPixmap(pixmap);
    addWidget(img, QRect(0, 0, 200, 200), 2);
    addLayout(make_shared<QVBoxLayout>(), 2);
    shared_ptr<QLabel> firstParamLabel = make_shared<QLabel>("Параметр 1");
    addWidget(firstParamLabel, QRect(0, 0, 200, 60), 3);
    shared_ptr<QDoubleSpinBox> firstParamCounter = make_shared<QDoubleSpinBox>();
    addWidget(firstParamCounter, QRect(0, 0, 200, 60), 3);
    shared_ptr<QLabel> secondParamLabel = make_shared<QLabel>("Параметр 2");
    addWidget(secondParamLabel, QRect(0, 0, 200, 60), 3);
    shared_ptr<QDoubleSpinBox> secondParamCounter = make_shared<QDoubleSpinBox>();
    addWidget(secondParamCounter, QRect(0, 0, 200, 60), 3);
    shared_ptr<QLabel> thirdParamLabel = make_shared<QLabel>("Параметр 3");
    addWidget(thirdParamLabel, QRect(0, 0, 200, 60), 3);
    shared_ptr<QDoubleSpinBox> thirdParamCounter = make_shared<QDoubleSpinBox>();
    addWidget(thirdParamCounter, QRect(0, 0, 200, 60), 3);
    shared_ptr<QLabel> graphLabel = make_shared<QLabel>("График");
    addWidget(graphLabel, QRect(0, 0, 100, 60));
    shared_ptr<QCustomPlot> plot = make_shared<QCustomPlot>();
    plot.get()->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    QVector<double> x(251), y(251);
    for (int i = 0; i < 251; ++i) {
        x[i] = i;
        y[i] = exp(i / 100) + exp((100 + i) / 100);
    }
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->graph(0)->setData(x, y);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->graph(0)->rescaleAxes(true);
    plot->setMinimumSize(QSize(300, 280));
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(plot, QRect(0, 0, 100, 60));
}

Tester::Tester(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> label = make_shared<QLabel>("Вопрос: Вопрос?");
    addWidget(label, QRect(0, 0, 100, 60));
    addLayout(make_shared<QGridLayout>());
    shared_ptr<QCheckBox> check1 = make_shared<QCheckBox>("Ответ А");
    addWidget(check1, QRect(0, 0, 100, 60), 0, 0, 2);
    shared_ptr<QCheckBox> check2 = make_shared<QCheckBox>("Ответ Б");
    addWidget(check2, QRect(0, 0, 100, 60), 0, 1, 2);
    shared_ptr<QCheckBox> check3 = make_shared<QCheckBox>("Ответ В");
    addWidget(check3, QRect(0, 0, 100, 60), 1, 0, 2);
    shared_ptr<QCheckBox> check4 = make_shared<QCheckBox>("Ответ Г");
    addWidget(check4, QRect(0, 0, 100, 60), 1, 1, 2);
}

Visualisation::Visualisation(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> txtedit = make_shared<QLabel>("График считанных данных");
    addWidget(txtedit,QRect(0,0,100,60));
    addLayout(make_shared<QGridLayout>());
    shared_ptr<QCustomPlot> cplot = make_shared<QCustomPlot>();
    cplot.get()->addGraph();
    cplot->graph(0)->setPen(QPen(Qt::red));
    cplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    QVector<double> x, y;
    for (auto &i: storage.get()->data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            x.append(getDay(i.first));
            y.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            x.append(getValue(i.first));
            y.append(getDay(i.second));
        }
    }
    double expval = 0, expval2 = 0, disp, stdev, a = y[0], b = y[0], n = 0;
    QVector<double>  px, py;
    for (int i=0; i<y.size(); i++)
    {
        expval = expval + y[i];
        expval2 = expval2 + pow(y[i],2);
    }
    expval = expval/y.size();
    expval2 = expval2/y.size();
    disp = (expval2 - pow(expval,2))*y.size()/(y.size()-1);
    stdev = sqrt(disp);
    for (int i = 0; i<y.size(); i++)
    {
        if (a > y[i])
            a = y[i];
        if (b < y[i])
            b = y[i];
    }
    n=(b-a)/100;
    for (int i=0; i < 8*stdev/n; i++)
    {
        if (px.size() == 0)
            px.append(expval-4*stdev);
        else
            px.append(px[i-1]+n);
    }
    for (int i=0; i<px.size(); i++)
        py.append(1/stdev/sqrt(2*M_PI)*exp((-0.5)*pow(((px[i]-expval)/stdev),2)));
    cplot->xAxis2->setVisible(true);
    cplot->yAxis2->setVisible(true);
    cplot->graph(0)->setData(px, py);
    cplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    cplot->graph(0)->rescaleAxes(true);
    cplot->setMinimumSize(QSize(300,280));
    cplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cplot->rescaleAxes();
    addWidget(cplot,QRect(0,0,100,60),2,0,2);


    shared_ptr<QLabel> lblev = make_shared<QLabel>("Мат. ожидание: " + QString::number(expval));
    addWidget(lblev,QRect(0,0,200,60),0,1,2);
    shared_ptr<QLabel> lbld = make_shared<QLabel>("Дисперсия: " + QString::number(disp));
    addWidget(lbld,QRect(0,0,200,60),0,2,2);
    shared_ptr<QLabel> lblsd = make_shared<QLabel>("Среднеквадратичное отклонение: " + QString::number(stdev));
    addWidget(lblsd,QRect(0,0,200,60),0,3,2);
    double m3 = 0, m4 = 0, skewness = 0, kurtosis = 0;
    for (int i=0; i<y.size(); i++)
    {
        m3 = m3 + pow((y[i]-expval),3);
        m4 = m4 + pow((y[i]-expval),4);
    }
    skewness = m3/y.size()/pow(stdev,3);
    kurtosis = m4/y.size()/pow(stdev,4) - 3;
    shared_ptr<QLabel> lblskwnss = make_shared<QLabel>("К-т асимметрии: " + QString::number(skewness));
    addWidget(lblskwnss,QRect(0,0,200,60),1,1,2);
    shared_ptr<QLabel> lblkrtss = make_shared<QLabel>("К-т эксцесса: " + QString::number(kurtosis));
    addWidget(lblkrtss,QRect(0,0,200,60),1,2,2);
}

double Visualisation::getValue(const QStringList &i) { return (i[0] + '.' + i[1]).toDouble(); }

int Visualisation::getDay(const QStringList &i) {
    return QDate(i[2].toInt(), i[1].toInt(), i[0].toInt()).dayOfYear();
}

Interpolator::Interpolator(shared_ptr<DataStorage> storage) : IWidget(storage) {}

Helper::Helper(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> helpLabel = make_shared<QLabel>("Справка");
    addWidget(helpLabel, QRect(0, 0, 200, 60));
    shared_ptr<QTextEdit> helpText = make_shared<QTextEdit>("Текст справки");
    helpText->setReadOnly(true);
    addWidget(helpText, QRect(0, 0, 200, 240));
}

Correlator::Correlator(shared_ptr<DataStorage> storage) : IWidget(storage) {}
