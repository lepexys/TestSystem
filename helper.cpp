#include "testui.h"

Helper::Helper(shared_ptr<DataStorage> strg)
    :IWidget(strg)
{
    shared_ptr<QLabel> label = make_shared<QLabel>("Справка");
    addWidget(label,QRect(0,0,200,60));
    shared_ptr<QTextEdit> txt = make_shared<QTextEdit>("Текст справки");
    txt->setReadOnly(true);
    addWidget(txt,QRect(0,0,200,240));
}
