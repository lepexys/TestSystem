#ifndef TESTSYSTEM_IWIDGET_H
#define TESTSYSTEM_IWIDGET_H

#include <qcustomplot.h>
#include "DataStorage.h"

using namespace std;

typedef void (*ButtonAct)(QWidget *, shared_ptr<DataStorage>);

class IWidget : public QWidget {
Q_OBJECT
public:
    shared_ptr<DataStorage> storage;
    QList<shared_ptr<QLayout>> layouts;
    QList<shared_ptr<QPushButton>> buttons;
    QList<shared_ptr<QWidget>> widgets;

    explicit IWidget(shared_ptr<DataStorage> dataStorage = make_shared<DataStorage>(), QWidget *parent = nullptr);

    void addButton(QRect rect, const QString &text, ButtonAct act, int layInd = 0);

    void addWidget(const shared_ptr<QWidget> &widget, QRect rect, int layInd = 0);

    void addWidget(const shared_ptr<QWidget> &widget, QRect rect, int row, int col, int layInd = 0);

    void addLayout(const shared_ptr<QLayout> &layout, int layInd = 0);
};

#endif //TESTSYSTEM_IWIDGET_H
