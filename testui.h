#ifndef TESTUI_H
#define TESTUI_H

#include "IWidget.h"

using namespace std;

class Correlator : public IWidget {
public:
    explicit Correlator(shared_ptr<DataStorage>);
};

class Interpolator : public IWidget {
public:
    explicit Interpolator(shared_ptr<DataStorage>);
};

class Tester : public IWidget {
public:
    explicit Tester(shared_ptr<DataStorage> = make_shared<DataStorage>());
};

class Helper : public IWidget {
public:
    explicit Helper(shared_ptr<DataStorage> = make_shared<DataStorage>());
};

#endif // TESTUI_H
