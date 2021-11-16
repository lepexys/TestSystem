#include "testui.h"

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

Interpolator::Interpolator(shared_ptr<DataStorage> storage) : IWidget(storage) {}

Helper::Helper(shared_ptr<DataStorage> storage) : IWidget(storage) {
    shared_ptr<QLabel> helpLabel = make_shared<QLabel>("Справка");
    addWidget(helpLabel, QRect(0, 0, 200, 60));
    shared_ptr<QTextEdit> helpText = make_shared<QTextEdit>("Текст справки");
    helpText->setReadOnly(true);
    addWidget(helpText, QRect(0, 0, 200, 240));
}

Correlator::Correlator(shared_ptr<DataStorage> storage) : IWidget(storage) {}
