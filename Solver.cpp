#include "Solver.h"


Solver::Solver(shared_ptr<DataStorage> storage) : IWidget(storage) {
    auto imageData = "iVBORw0KGgoAAAANSUhEUgAAALkAAAA2CAYAAACbSzhRAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAA7DAAAOwwHHb6hkAAAIW0lEQVR4nO2cz2sTzxvH3/nyvaps05OISBcPoiLUVcFfoIckeFIUUvEieIp68ZJKpScvpgi91fTgUZKgBxEijQcFs4raCl2o9KC7hx487bS0/gHzPfQ742yym0z8bJp81ucFgUm6M/vs7HuemeeZ3aY45xwEkWD+M2gDCKLfkMiJxEMiJxIPiZxIPCRyIvGQyInEQyInEk/PInccB7lcDqlUCqlUCrlcDoyxfthGELHQk8gdx8GFCxfAGIPv+yiVSmg0Gnj69Gm/7COIf0xPIp+cnMTGxgZmZ2eRTqexZ8+eftlFELGR0t3WZ4xhdHQUpmnix48fYIwhl8vBdV18//4d6XS637YSxB+h7ck/f/4MAMhkMpifn8fBgweRyWRI4MTQoy3ylZUVAMD58+dx7do1ZDIZ1Go1bG5u9s04gogDbZG/ffsWAHDo0CGk02mMj4/DdV28ePGib8YRRBxoi7zRaMAwDBw7dgwAyIP/AYwx2LYNz/MGbUrPDJvtvdijJXLHcQAAIyMjYIzBcRw8efIEAHD69Ol/YOrfwYMHD5BKpTA6Oopz587hy5cvgzZJm7htdxwHExMTGBkZCey1vH79Wqu+2KMR9vz8+bN7Ja5BpVLhALhlWdwwDFmu1+s61QnOuWVZHAAHwH3fH7Q5PRGX7UJHhmHwZrPJOec8n8/LtpeXl3u2RwctT/7+/XsAwOzsLNbX18E5x+LiIi5duqQ1+nYC27alZxiWKVVFZKAsyxqqbBRjTHrVarUaekwctnueh+vXrwMA7t+/j7NnzwIAxsfH5TGNRkOrLdd1pT06aIl8cXERwHbQOYx4nod79+4BAEzTxNjY2IAtakfcwEwmM2BLfsMYw/T0NDY2NgAAJ0+eDD0uDtsfP34sy7du3ZJlNbY7cuRI13Y8z5P2njhxQu/kOu4eADdNU2tqiBvXdXmhUOCmacopSl0qZbNZ+bv6MQwjtL16vR6oY5omL5fL3DRNXiqVtGyqVCqBKXNqaopzznmpVAqdepeXl+XvlUqFl0oleT3ZbHYgyxfV1tZP3Lb7vi/byOfzgd9FW5ZlhdZt7Wu1XKlUtK5Vb1ETEwDkWkyHSqUiY4BKpcJ935ff1XbK5bK88E5xQqFQCKwJfd/vudPEALEsi7uuy13XlXXFDSsUCoE6qn3ZbJY3m03ebDbbBslOowo4yoY4bK/X6/L4crkszy36Pmyw+L7f1tfqYGkdjJ3ou8inpqZ4qVSSo5bzbS+ijugwXNeVglZFIy5c7RQ1eHFdN7Q9taNVMatePaquei1hx2azWSlw0zTbbpgYXOogVAXWrS847+x5wz46s5Iq4KgBHoftar81m035XQ1AO9VRxSzuV9RMHcaOePJ6vc7z+Tw3TZNbliVF3wm1c7uJTxVYr8fodlrUlKu2ETVThZ1bHXS6y6S40enjOGxX+4fz30tQ0W6rRxazY1hfq7OKLlqBp8hadPuEwRjDysqKjIjT6TT279/f9Zwi0u8WSHqe1zXadhxHHpPP5wN/E3nfbkGVurN7+fLlwN/E8/T5fF5mDdS/hZ37w4cPsqwTcPWDN2/eAAAMwwjt47hsF4FrNpsFAIyNjWFubg7AdqZkcnIycLyai1f7Ws2aXbx4set5RU5dS+R82+N3/YQxPT0NAFhYWAAAPHv2DGtra7hz507k+RzHkRF0N/GpHaKmo1Q+ffoky0ePHpVlNVKPqqvaJFCzEJ7nYWlpCQBw9+7dtnriwbbWcwuBAcCpU6c6nrsfqM4hKqsSh+22bcvy8ePHQ49pTR2KlDUQzOip91pnE3JhYQGc8/6//jY3N4disYh0Og3XdbG6uopisRiZkwWAX79+yfKBAwc6tr+2tibLUReupqn27dsny6p37tZpqhdRvV63Z3dUryduGGNMDgzd3PPMzIz2jJpKpTAzM9OxPXWnMMorxmH7t2/fZPnMmTOhxxiGEfiu9rV4jAQAXr582WaPDv/VPjIGorx9K3v37tVuUzw4BvR24YwxPHr06I/qChzHCbQRxtevX2VZ3LDV1VX5m27uuVgsolgs9mxjFB8/fpTlqCVHHLa/e/dOlnfv3i3LqpObmJjo2o5t26jVagC2l7C9bEoN5YvMY2Njcv32/PlzMMbAGMP8/DxyuVzbsYLNzU3Yto1cLhfwBqqX3tragud5uHHjhrxJOp125coVWXYcB47j4OrVq4GbuLW1hWq1GvCiretRANi1a1egbfHe7E6ixkWiTyYmJgLPkMRhu/D6wO+BZds2bt++DWC77x8+fBioo/a153mwbRs3b96UMZdhGPKlHa3dbe0QdYfxfT+QGjRNkxcKhbYsgJpPxf+j8bAMh5qSyufz3HVdmadtzWtH2aNmYlRbxO9iQ0lkjjrlk1vt0c35xolqg2VZgTRiHLarWRKRWVO/R2XZwvra931er9f/6NmpoRV5XJRKJW5ZVltnqjdAd+eM6I2wTaBBMJTLlbioVqvy5evW5cjU1BSA7alPZ01I9I4auB4+fHhgdiRa5IL19XWZAmSMYWZmBrVaDYZh4NWrVwO2LrmogWvr/sGO0ovbb304R0z5vew+7TTlcrntIa6o9T0RL6K/B60PbZGLYEMEaZZl8Ww2yw3DILEQQ43W/13xPA+macr/uQJsb5k2Gg3U6/WhenmCIFrRWpOL7VT1+QXGGCzLIoETQ4+WyMXWudiWtW0bS0tLQ/UaF0FE0VN2ZWtrC47jBLaEbdvu+BwKQQwcnYW767oyqyJ2v0QgOqi3WghCF+1/+EkQ/1b+is0g4u+GRE4kHhI5kXhI5ETiIZETiYdETiQeEjmReEjkROIhkROJh0ROJB4SOZF4SORE4iGRE4nnf7nSzMl3M5VVAAAAAElFTkSuQmCC";

    auto image = new QPixmap();
    image->loadFromData(QByteArray::fromBase64(imageData));
    shared_ptr<QLabel> imageLabel = make_shared<QLabel>();
    imageLabel->setPixmap(*image);
    addWidget(imageLabel, QRect(0, 0, 200, 60));

    shared_ptr<QLabel> parametersLabel = make_shared<QLabel>("Парамеры функции");
    addWidget(parametersLabel, QRect(0, 0, 100, 60));

    addLayout(make_shared<QHBoxLayout>());
    addLayout(make_shared<QVBoxLayout>(), 2);

    shared_ptr<QLabel> hParamLabel = make_shared<QLabel>("H");
    addWidget(hParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QSpinBox> hParamCounter = make_shared<QSpinBox>();
    hParamCounter->setRange(300, 350);
    hParamCounter->setSingleStep(5);
    hParamCounter->setValue(*hParam);
    connect(hParamCounter.get(), qOverload<int>(&QSpinBox::valueChanged), this, &Solver::hParamChanged);
    addWidget(hParamCounter, QRect(0, 0, 200, 60), 3);

    shared_ptr<QLabel> mParamLabel = make_shared<QLabel>("M");
    addWidget(mParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QSpinBox> mParamCounter = make_shared<QSpinBox>();
    mParamCounter->setRange(10, 30);
    mParamCounter->setSingleStep(2);
    mParamCounter->setValue(*mParam);
    connect(mParamCounter.get(), qOverload<int>(&QSpinBox::valueChanged), this, &Solver::mParamChanged);
    addWidget(mParamCounter, QRect(0, 0, 200, 60), 3);

    shared_ptr<QLabel> dParamLabel = make_shared<QLabel>("D");
    addWidget(dParamLabel, QRect(0, 0, 200, 60), 3);

    shared_ptr<QSpinBox> dParamCounter = make_shared<QSpinBox>();
    dParamCounter->setRange(0, 100);
    dParamCounter->setSingleStep(5);
    dParamCounter->setValue(*dParam);
    connect(dParamCounter.get(), qOverload<int>(&QSpinBox::valueChanged), this, &Solver::dParamChanged);
    addWidget(dParamCounter, QRect(0, 0, 200, 60), 3);

    button->setGeometry(QRect(0, 0, 100, 60));
    connect(button.get(), &QPushButton::pressed, this, &Solver::solve);
    addWidget(button, QRect(0, 0, 200, 60), 3);
    addWidget(aLabel, QRect(0, 0, 200, 60), 3);

    solve();
}

struct functionParams {
    int h, m, d;
};

double functionBody(double a, void *params) {
    auto *p = (struct functionParams *) params;

    double h = p->h;
    double m = p->m;
    double d = p->d;

    return 1 / std::tan(a * h) / m - a * std::tanh(d / m);
}

double functionDerivativeBody(double a, void *params) {
    auto *p = (struct functionParams *) params;

    double h = p->h;
    double m = p->m;
    double d = p->d;

    return -(h / m / std::pow(std::sin(a * h), 2)) - std::tanh(d / m);
}

void functionBodyAndDerivativeBody(double a, void *params, double *f, double *df) {
    *f = functionBody(a, params);
    *df = functionDerivativeBody(a, params);
}

void Solver::solve() {
    int status;
    int iter = 0, max_iter = 100;
    const gsl_root_fdfsolver_type *T;
    gsl_root_fdfsolver *s;
    double x0, x = M_PI / *hParam / 2;
    gsl_function_fdf FDF;
    struct functionParams params = {*hParam, *mParam, *dParam};

    FDF.f = &functionBody;
    FDF.df = &functionDerivativeBody;
    FDF.fdf = &functionBodyAndDerivativeBody;
    FDF.params = &params;

    T = gsl_root_fdfsolver_newton;
    s = gsl_root_fdfsolver_alloc(T);
    gsl_root_fdfsolver_set(s, &FDF, x);

    printf("using %s method\n", gsl_root_fdfsolver_name(s));

    printf("%-5s %10s %10s %10s\n", "iter", "root", "err", "err(est)");
    do {
        iter++;
        aLabel->setText(QString::number(x));
        status = gsl_root_fdfsolver_iterate(s);
        x0 = x;
        x = gsl_root_fdfsolver_root(s);
        status = gsl_root_test_delta(x, x0, 0, 1e-3);

        if (status == GSL_SUCCESS)
            printf("Converged:\n");

        printf("%5d %10.7f %10.7f\n", iter, x, x - x0);
    } while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fdfsolver_free(s);
}

void Solver::hParamChanged(int newValue) {
    *hParam = newValue;
}

void Solver::mParamChanged(int newValue) {
    *mParam = newValue;
}

void Solver::dParamChanged(int newValue) {
    *dParam = newValue;
}
