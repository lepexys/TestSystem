#ifndef TESTUI_H
#define TESTUI_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QAction>
#include <QTextEdit>
#include <QXmlReader>
#include <QCheckBox>
#include <QAxObject>
#include <qcustomplot.h>
#include <memory>
using namespace std;

class Loader
{
    QString path = "C:/Users/lepex/Desktop/Study/MathModelsPhisicalPrecesses/file.xlsx";
public:
    Loader(){}
    ~Loader(){}
    QMap<int,pair<QStringList,QStringList>> Load();
};

class Saver
{
    QString path = "file.xlsx";
public:
    Saver(){}
    ~Saver(){}
    void Save();
};

class DataStorage : public Loader, public Saver
{
public:
    QMap<int,pair<QStringList,QStringList>> data;
    DataStorage();
    ~DataStorage(){}
};
typedef void (*ButtonAct)(QWidget*,shared_ptr<DataStorage>);

class IWidget : public QWidget
{
    Q_OBJECT
public:
    shared_ptr<DataStorage> storage;
    QList<shared_ptr<QLayout>> layouts;
    QList<shared_ptr<QPushButton>> buttons;
    QList<shared_ptr<QWidget>> widgets;
    IWidget(shared_ptr<DataStorage> strg = make_shared<DataStorage>(),QWidget *parent = nullptr): QWidget(parent)
    {
        storage = strg;
        layouts.append(make_shared<QVBoxLayout>(this));
        layouts[0]->setAlignment(Qt::AlignmentFlag::AlignCenter);
        addLayout(make_shared<QVBoxLayout>());
        layouts[1]->setAlignment(Qt::AlignmentFlag::AlignLeft);
    }
    ~IWidget(){}
    void addButton(QRect rect,QString text,ButtonAct act,int layInd = 0)
    {
        shared_ptr<QPushButton> butn = make_shared<QPushButton>(text);
        butn->setGeometry(rect);
        QObject::connect(butn.get(),&QPushButton::pressed,[=](){act(this,storage);});
        layouts[layInd]->addWidget(butn.get());
        buttons.append(butn);
    }
    void addWidget(shared_ptr<QWidget> widget,QRect rect,int layInd = 0)
    {
        widget->setGeometry(rect);
        layouts[layInd]->addWidget(widget.get());
        widgets.append(widget);
    }
    void addWidget(shared_ptr<QWidget> widget,QRect rect,int row,int col,int layInd = 0)
    {
        widget->setGeometry(rect);
        static_cast<QGridLayout*>(layouts[layInd].get())->addWidget(widget.get(),row,col);
        widgets.append(widget);
    }
    void addLayout(shared_ptr<QLayout> layout,int layInd = 0)
    {
        static_cast<QBoxLayout*>(layouts[layInd].get())->addLayout(layout.get());
        layouts.append(layout);
    }
public slots:
    static void funcTest(QWidget*,shared_ptr<DataStorage>);
    static void funcVisual(QWidget*,shared_ptr<DataStorage>);
    static void funcReactor(QWidget*,shared_ptr<DataStorage>);
    static void funcHelp(QWidget*,shared_ptr<DataStorage>);
    static void funcExit(QWidget*,shared_ptr<DataStorage>);
};

class Visualisation:public IWidget
{
public:
    Visualisation(shared_ptr<DataStorage>);
    ~Visualisation(){}
};
class Correlator:public IWidget
{
public:
    Correlator(shared_ptr<DataStorage>);
    ~Correlator(){}
};
class Interpolator:public IWidget
{
public:
    Interpolator(shared_ptr<DataStorage>);
    ~Interpolator(){}
};
class Tester:public IWidget
{
public:
    Tester(shared_ptr<DataStorage> = make_shared<DataStorage>());
    ~Tester(){}
};

class Reactor:public IWidget
{
public:
    Reactor(shared_ptr<DataStorage> = make_shared<DataStorage>());
    ~Reactor(){}
};

class Helper:public IWidget
{
public:
    Helper(shared_ptr<DataStorage> = make_shared<DataStorage>());
    ~Helper(){}
};

class MainMenu:public IWidget
{
public:
    MainMenu():IWidget()
    {
        addButton(QRect(0,0,100,60),"Тестирование",funcTest);
        addButton(QRect(0,0,100,60),"Статистика",funcVisual);
        addButton(QRect(0,0,100,60),"Реактор",funcReactor);
        addButton(QRect(0,0,100,60),"Справка",funcHelp);
        addButton(QRect(0,0,100,60),"Выход",funcExit);
    }
    ~MainMenu(){}
};

#endif // TESTUI_H
