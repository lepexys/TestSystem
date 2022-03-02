#include "Visualisation.h"
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_histogram.h>

double getValue(const QStringList &i) { return (i[0] + '.' + i[1]).toDouble(); }

int getDay(const QStringList &i) {
    return QDate(i[2].toInt(), i[1].toInt(), i[0].toInt()).dayOfYear();
}

gsl_histogram *createHistogram(QVector<double> &data) {
    gsl_histogram *histogram = gsl_histogram_alloc(9);
    const double *min = std::min_element(data.constBegin(), data.constEnd());
    const double *max = std::max_element(data.constBegin(), data.constEnd());
    gsl_histogram_set_ranges_uniform(histogram, *min, *max);
    for (auto i: data) {
        gsl_histogram_increment(histogram, i);
    }
    return histogram;
}

void getHistogram(QVector<double> &data, QVector<double> &hist_x, QVector<double> &hist_y) {
    gsl_histogram *histogram = createHistogram(data);
    size_t bins = gsl_histogram_bins(histogram);
    for (size_t i = 0; i < bins; i++) {
        double min = 0, max = 0;
        gsl_histogram_get_range(histogram, i, &min, &max);
        hist_x.append(min);
        hist_y.append(histogram->bin[i] / data.size());
        hist_x.append(max);
        hist_y.append(histogram->bin[i] / data.size());
    }
}

void createGraph(const shared_ptr<QCustomPlot> &plot, QVector<double> &x, QVector<double> &y) {
    plot->clearGraphs();
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));
    plot->graph(0)->setBrush(QBrush(QColor(220, 20, 60, 20)));
    plot->graph(0)->setData(x, y);
    plot->graph(0)->rescaleAxes(true);
    plot->xAxis2->setVisible(false);
    plot->yAxis2->setVisible(false);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->setMinimumSize(QSize(300, 280));
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot->rescaleAxes();
    plot->replot();
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
    shared_ptr<QLabel> txtedit = make_shared<QLabel>("Данные анализа:");
    addWidget(txtedit, QRect(0, 0, 100, 60));
    addLayout(make_shared<QGridLayout>());
    QVector<double> days, data_value, histo_x, histo_y;
    for (auto &i: storage->data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            days.append(getDay(i.first));
            data_value.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            data_value.append(getValue(i.first));
            days.append(getDay(i.second));
        }
    }

    cplot = make_shared<QCustomPlot>();
    getHistogram(data_value, histo_x, histo_y);
    createGraph(cplot, histo_x, histo_y);
    addWidget(cplot, QRect(0, 0, 100, 60), 2, 0, 2);
    addLayout(make_shared<QGridLayout>(), 2, 1, 2);
    addButton(QRect(0, 0, 100, 60), "Автокорреляция", funcAutocorrelation, 0, 0, 3);
    addButton(QRect(0, 0, 100, 60), "Корреляция", funcCorrelation, 1, 0, 3);
    addButton(QRect(0, 0, 100, 60), "Сохранить данные", saveData, 1, 1, 3);
    addButton(QRect(0, 0, 100, 60), "Гистограмма", histogramView, 0, 1, 3);
    addButton(QRect(0, 0, 100, 60), "Ньютон", interpolationNewton, 2, 0, 3);
    addButton(QRect(0, 0, 100, 60), "Сплайны", interpolationSplines, 2, 1, 3);
    addButton(QRect(0, 0, 100, 60), "МНК", interpolationLSM, 2, 2, 3);

    shared_ptr<QLabel> statsLabel1 = make_shared<QLabel>(getStatsString1(data_value.size(), data_value.data()));
    addWidget(statsLabel1, QRect(0, 0, 200, 60), 0, 1, 2);
    shared_ptr<QLabel> statsLabel2 = make_shared<QLabel>(getStatsString2(data_value.size(), data_value.data()));
    addWidget(statsLabel2, QRect(0, 0, 200, 60), 1, 1, 2);
}

void Visualisation::funcAutocorrelation(QWidget *widget, shared_ptr<DataStorage> strg) {

    QVector<double> days, data_values, step, corr;
    for (auto &i: strg->data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            days.append(getDay(i.first));
            data_values.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            data_values.append(getValue(i.first));
            days.append(getDay(i.second));
        }
    }
    double expval = 0;
    for (double i: data_values) {
        expval = expval + i;
    }
    expval = expval / data_values.size();
    for (int i = 1; i < 20; ++i) {
        double cor = (data_values[0] - expval) * (data_values[i] - expval);
        for (int j = 1; j < data_values.length() - i; j++) {
            cor = ((data_values[j] - expval) * (data_values[j + i] - expval) + cor * j) / (j + 1);
        }
        corr.append(cor);
        step.append(i);
    }
    createGraph(dynamic_cast<Visualisation *>(widget)->cplot, step, corr);
}

void Visualisation::funcCorrelation(QWidget *widget, shared_ptr<DataStorage> strg) {
    QVector<double> days1, data_values1;
    QList<pair<QStringList, QStringList>> reserve_data = strg->data;
    for (auto &i: strg->data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            days1.append(getDay(i.first));
            data_values1.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            data_values1.append(getValue(i.first));
            days1.append(getDay(i.second));
        }
    }

    QList<pair<QStringList, QStringList>> data =
            strg->Load(QFileDialog::getOpenFileName(widget, tr("Open File"), QDir::current().path(),
                                                    tr("Files (*.xlsx)")));
    QVector<double> days2, data_values2;
    for (auto &i: data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            days2.append(getDay(i.first));
            data_values2.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            data_values2.append(getValue(i.first));
            days2.append(getDay(i.second));
        }
    }
    dynamic_cast<Visualisation *>(widget)->cplot->clearGraphs();
    QCPGraph *points_only = dynamic_cast<Visualisation *>(widget)->cplot->addGraph();
    points_only->setData(data_values1, data_values2);
    points_only->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    points_only->setPen(Qt::NoPen);
    dynamic_cast<Visualisation *>(widget)->cplot->rescaleAxes();
    dynamic_cast<Visualisation *>(widget)->cplot->replot();
    strg->data=reserve_data;
}

void Visualisation::saveData(QWidget *widget, shared_ptr<DataStorage> strg) {

}

void Visualisation::interpolationNewton(QWidget *widget, shared_ptr<DataStorage> strg) {

}

void Visualisation::interpolationSplines(QWidget *widget, shared_ptr<DataStorage> strg) {

}

void Visualisation::interpolationLSM(QWidget *widget, shared_ptr<DataStorage> strg) {

}

void Visualisation::histogramView(QWidget *widget, shared_ptr<DataStorage> strg) {
    QVector<double> days, data_values, x, y;
    for (auto &i: strg->data) {
        if (i.first.length() == 6 && i.second.length() == 2) {
            days.append(getDay(i.first));
            data_values.append(getValue(i.second));
        } else if (i.first.length() == 2 && i.second.length() == 6) {
            data_values.append(getValue(i.first));
            days.append(getDay(i.second));
        }
    }
    getHistogram(data_values, x, y);
    createGraph(dynamic_cast<Visualisation *>(widget)->cplot, x, y);
}
