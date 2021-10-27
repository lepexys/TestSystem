QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport axcontainer

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonFunctions.cpp \
    correlator.cpp \
    dataStorage.cpp \
    helper.cpp \
    interpolator.cpp \
    main.cpp \
    qcustomplot.cpp \
    reactor.cpp \
    testui.cpp \
    visualisation.cpp

HEADERS += \
    qcustomplot.h \
    testui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
