#include "Visualisation.h"
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_histogram.h>

double getValue(const QStringList &i) { return (i[0] + '.' + i[1]).toDouble(); }

int getDay(const QStringList &i) {
    return QDate(i[2].toInt(), i[1].toInt(), i[0].toInt()).dayOfYear();
}

gsl_histogram *createHistogram(QVector<double> &data) {
    gsl_histogram *histogram = gsl_histogram_alloc(10);
    const double *min = std::min_element(data.constBegin(), data.constEnd());
    const double *max = std::max_element(data.constBegin(), data.constEnd());
    gsl_histogram_set_ranges_uniform(histogram, *min, *max);
    for (auto i: data) {
        gsl_histogram_increment(histogram, i);
    }
    return histogram;
}


void createHistogramPlot(QVector<double> &data, const shared_ptr<QCustomPlot> &plot) {
    gsl_histogram *histogram = createHistogram(data);
    size_t bins = gsl_histogram_bins(histogram);
    QVector<double> px, py;
    for (size_t i = 0; i < bins; i++) {
        double min = 0, max = 0;
        gsl_histogram_get_range(histogram, i, &min, &max);
        px.append((min + max) / 2);
        py.append(histogram->bin[i] / data.size());
    }
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));
    plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(0)->setData(px, py);
    plot->graph(0)->rescaleAxes(true);
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->setMinimumSize(QSize(300, 280));
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot->rescaleAxes();
}

QString getStatsString1(const size_t n, double *data) {
    return "Мат. ожидание: "
           + QString::number(gsl_stats_mean(data, 1, n))
           + " Дисперсия: "
           + QString::number(gsl_stats_variance(data, 1, n))
           + " Среднеквадратичное отклонение: "
           + QString::number(gsl_stats_sd(data, 1, n));
}

QString getStatsString2(const size_t n, double *data) {
    return "К-т асимметрии: "
           + QString::number(gsl_stats_skew(data, 1, n))
           + " К-т эксцесса: "
           + QString::number(gsl_stats_kurtosis(data, 1, n));
}

Visualisation::Visualisation(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> txtedit = make_shared<QLabel>("График считанных данных");
    addWidget(txtedit, QRect(0, 0, 100, 60));
    addLayout(make_shared<QGridLayout>());

    QVector<double> x, y;
    for (auto &i: storage->data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            x.append(getDay(i.first));
            y.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            x.append(getValue(i.first));
            y.append(getDay(i.second));
        }
    }
    cplot = make_shared<QCustomPlot>();
    createHistogramPlot(y, cplot);
    addWidget(cplot, QRect(0, 0, 100, 60), 2, 0, 2);

    addLayout(make_shared<QGridLayout>(), 2, 1, 2);
    addButton(QRect(0, 0, 100, 60), "Автокорреляция", funcAutocorrelation, 0, 0, 3);
    addButton(QRect(0, 0, 100, 60), "Корреляция", funcCorrelation, 1, 0, 3);

    shared_ptr<QLabel> statsLabel1 = make_shared<QLabel>(getStatsString1(y.size(), y.data()));
    addWidget(statsLabel1, QRect(0, 0, 200, 60), 0, 1, 2);
    shared_ptr<QLabel> statsLabel2 = make_shared<QLabel>(getStatsString2(y.size(), y.data()));
    addWidget(statsLabel2, QRect(0, 0, 200, 60), 1, 1, 2);
}

void Visualisation::funcAutocorrelation(QWidget *widget, shared_ptr<DataStorage> strg) {
    QList<pair<QStringList, QStringList>> data =
            strg->Load(QFileDialog::getOpenFileName(widget, tr("Open File"), QDir::current().path(),
                                                    tr("Files (*.xlsx)")));
    QVector<double> x, y;
    QVector<double> step, corr;
    for (auto &i: data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            x.append(getDay(i.first));
            y.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            x.append(getValue(i.first));
            y.append(getDay(i.second));
        }
    }
    double expval = 0;
    for (double i: y) {
        expval = expval + i;
    }
    expval = expval / y.size();
    for (int i = 1; i < 20; ++i) {
        double cor = (y[0] - expval) * (y[i] - expval);
        for (int j = 1; j < x.length() - i; j++) {
            cor = ((y[j] - expval) * (y[j + i] - expval) + cor * j) / j + 1;
        }
        corr.append(cor);
        step.append(i);
    }
    dynamic_cast<Visualisation *>(widget)->cplot->graph(0)->setData(step, corr);
    dynamic_cast<Visualisation *>(widget)->cplot->graph(0)->rescaleAxes(true);
    dynamic_cast<Visualisation *>(widget)->cplot->rescaleAxes();
    dynamic_cast<Visualisation *>(widget)->cplot->update(); //Can't update
}

void Visualisation::funcCorrelation(QWidget *, shared_ptr<DataStorage>) {

}
