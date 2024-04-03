QT += core gui
QT +=printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buffer.cpp \
    layoutfactory.cpp \
    leftlayout.cpp \
    main.cpp \
    mainwindow.cpp \
    rightlayout.cpp \
    stringparser.cpp \
    toolbar.cpp \
    validatestring.cpp \
    graphbuilder.cpp \
    ./qcustomplot/qcustomplot.cpp \
    pythonconveyor.cpp

LIBS += -lpython3.11

INCLUDEPATH += ./python3.11/

HEADERS += \
    buffer.h \
    expressionvalidator.h \
    layoutfactory.h \
    leftlayout.h \
    mainwindow.h \
    rightlayout.h \
    stringparser.h \
    toolbar.h \
    validatestring.h \
    graphbuilder.h \
    ./qcustomplot/qcustomplot.h \
    pythonconveyor.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
