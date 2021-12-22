#ifndef TESTSYSTEM_SOLVER_H
#define TESTSYSTEM_SOLVER_H

#include "DataStorage.h"
#include "IWidget.h"
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

class Solver : public IWidget {
    std::shared_ptr<QPushButton> button = std::make_shared<QPushButton>("Решить");
    std::shared_ptr<QLabel> aLabel = std::make_shared<QLabel>("");
    unique_ptr<int> hParam = make_unique<int>(325);
    unique_ptr<int> mParam = make_unique<int>(20);
    unique_ptr<int> dParam = make_unique<int>(50);

public:
    explicit Solver(shared_ptr<DataStorage>);

    void solve();

    void hParamChanged(int newValue);

    void mParamChanged(int newValue);

    void dParamChanged(int newValue);
};

#endif //TESTSYSTEM_SOLVER_H
