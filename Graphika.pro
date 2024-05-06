QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 compat

SRCDIR = $$PWD/src/app
HEADDIR = $$SRCDIR/head
IMPLDIR = $$SRCDIR/impl

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += ./resources/icons.qrc \
    pymodules.qrc \
    ./resources/pymodules/pymodules.qrc

INCLUDEPATH += ./python3.11 $${HEADDIR} $${HEADDIR}/algs \
    $${HEADDIR}/ui $${HEADDIR}/settings $${HEADDIR}/utils

LIBS += -lpython3.11

VPATH += $$IMPLDIR $$IMPLDIR/algs \
    $$IMPLDIR/ui $$IMPLDIR/utils

SOURCES += \
    $$IMPLDIR/algs/compositestatestack.cpp \
    $$IMPLDIR/algs/graphbuilder.cpp \
    $$IMPLDIR/algs/pythonconveyor.cpp \
    $$IMPLDIR/algs/reportpdfgenerator.cpp \
    $$IMPLDIR/algs/stringparser.cpp \
    $$IMPLDIR/utils/mathutils.cpp \
    $$IMPLDIR/ui/leftwidget.cpp \
    $$IMPLDIR/ui/mainwindow.cpp \
    $$IMPLDIR/ui/menu.cpp \
    $$IMPLDIR/ui/rightwidget.cpp \
    $$IMPLDIR/ui/toolbar.cpp \
    $$IMPLDIR/utils/buffer.cpp \
    $$IMPLDIR/utils/sender.cpp \
    $$IMPLDIR/utils/validatestring.cpp \
    $$IMPLDIR/main.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS += \
    $$HEADDIR/algs/compositestatestack.h \
    $$HEADDIR/algs/expressionvalidator.h \
    $$HEADDIR/algs/graphbuilder.h \
    $$HEADDIR/algs/pythonconveyor.h \
    $$HEADDIR/algs/reportpdfgenerator.h \
    $$HEADDIR/algs/stringparser.h \
    $$HEADDIR/settings/settings.h \
    $$HEADDIR/ui/leftwidget.h \
    $$HEADDIR/ui/mainwindow.h \
    $$HEADDIR/ui/menu.h \
    $$HEADDIR/ui/rightwidget.h \
    $$HEADDIR/ui/toolbar.h \
    $$HEADDIR/utils/buffer.h \
    $$HEADDIR/utils/errorhandler.h \
    $$HEADDIR/utils/graphInfo.h \
    $$HEADDIR/utils/sender.h \
    $$HEADDIR/utils/mathutils.h \
    $$HEADDIR/utils/validatestring.h \
    qcustomplot/qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    pymodules.qrc
