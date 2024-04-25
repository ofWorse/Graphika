QT += core gui
QT +=printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 compat

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += ./resources/icons.qrc \
    pymodules.qrc \
    ./resources/pymodules/pymodules.qrc

SOURCES += \
    buffer.cpp \
    compositestatestack.cpp \
    leftwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    plotlayout.cpp \
    pythonconveyor.cpp \
    reportpdfgenerator.cpp \
    rightwidget.cpp \
    sender.cpp \
    stringparser.cpp \
    toolbar.cpp \
    validatestring.cpp \
    graphbuilder.cpp \
    ./qcustomplot/qcustomplot.cpp

LIBS += -lpython3.11

INCLUDEPATH += ./python3.11/

HEADERS += \
    buffer.h \
    compositestatestack.h \
    drawable.h \
    expressionvalidator.h \
    leftwidget.h \
    mainwindow.h \
    menu.h \
    plotlayout.h \
    pythonconveyor.h \
    reportpdfgenerator.h \
    rightwidget.h \
    sender.h \
    settings.h \
    stringparser.h \
    toolbar.h \
    validatestring.h \
    graphbuilder.h \
    ./qcustomplot/qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    pymodules.qrc
