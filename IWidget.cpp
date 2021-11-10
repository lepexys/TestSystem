#include "IWidget.h"

void IWidget::addLayout(const shared_ptr<QLayout> &layout, int layInd) {
    dynamic_cast<QBoxLayout *>(layouts[layInd].get())->addLayout(layout.get());
    layouts.append(layout);
}
void IWidget::addLayout(const shared_ptr<QLayout> &layout, int row, int col, int layInd) {
    dynamic_cast<QGridLayout *>(layouts[layInd].get())->addLayout(layout.get(),row,col);
    layouts.append(layout);
}

void IWidget::addWidget(const shared_ptr<QWidget> &widget, QRect rect, int row, int col, int layInd) {
    widget->setGeometry(rect);
    dynamic_cast<QGridLayout *>(layouts[layInd].get())->addWidget(widget.get(), row, col);
    widgets.append(widget);
}

void IWidget::addWidget(const shared_ptr<QWidget> &widget, QRect rect, int layInd) {
    widget->setGeometry(rect);
    layouts[layInd]->addWidget(widget.get());
    widgets.append(widget);
}

void IWidget::addButton(QRect rect, const QString &text, ButtonAct act, int layInd) {
    std::shared_ptr<QPushButton> button = std::make_shared<QPushButton>(text);
    button->setGeometry(rect);
    connect(button.get(), &QPushButton::pressed, [=]() { act(this, storage); });
    layouts[layInd]->addWidget(button.get());
    buttons.append(button);
}
void IWidget::addButton(QRect rect, const QString &text, ButtonAct act, int row, int col, int layInd) {
    std::shared_ptr<QPushButton> button = std::make_shared<QPushButton>(text);
    button->setGeometry(rect);
    connect(button.get(), &QPushButton::pressed, [=]() { act(this, storage); });
    dynamic_cast<QGridLayout *>(layouts[layInd].get())->addWidget(button.get(), row, col);
    buttons.append(button);
}

IWidget::IWidget(std::shared_ptr<DataStorage> dataStorage, QWidget *parent) : QWidget(parent) {
    setMinimumSize(640,480);
    QFont fnt;
    fnt.setPointSize(14);
    fnt.setFamily("Helvetica");
    fnt.setWeight(QFont::Light);
    setFont(fnt);
    storage = dataStorage;
    layouts.append(std::make_shared<QVBoxLayout>(this));
    layouts[0]->setAlignment(Qt::AlignCenter);
    addLayout(std::make_shared<QVBoxLayout>());
    layouts[1]->setAlignment(Qt::AlignLeft);
}
