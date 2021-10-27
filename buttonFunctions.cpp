#include "testui.h"

void IWidget::funcTest(QWidget*,shared_ptr<DataStorage> strg)
{
    Tester *tester = new Tester(strg);
    tester->show();
}
void IWidget::funcVisual(QWidget*,shared_ptr<DataStorage> strg)
{
    Visualisation *visual = new Visualisation(strg);
    visual->show();
}
void IWidget::funcReactor(QWidget*,shared_ptr<DataStorage> strg)
{
    Reactor *react = new Reactor(strg);
    react->show();
}
void IWidget::funcHelp(QWidget*,shared_ptr<DataStorage> strg)
{
    Helper *help = new Helper(strg);
    help->show();
}
void IWidget::funcExit(QWidget*widget,shared_ptr<DataStorage> strg)
{
    strg->Save();
    widget->close();
}
