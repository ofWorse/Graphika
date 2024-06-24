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

RESOURCES += icons.qrc \
    pymodules.qrc \
    referenceinfo.qrc

INCLUDEPATH += ./python3.11 $$HEADDIR $$HEADDIR/algs \
    $$HEADDIR/ui $$HEADDIR/ui/wgts $$HEADDIR/ui/wgts/lwgt \
    $$HEADDIR/ui/wgts/rwgt $$HEADDIR/settings $$HEADDIR/utils \
    $$HEADDIR/ui/menu

LIBS += -lpython3.11

VPATH += $$IMPLDIR $$IMPLDIR/algs \
    $$IMPLDIR/ui $$IMPLDIR/ui/wgts $$IMPLDIR/ui/wgts/lwgt \
    $$IMPLDIR/utils $$IMPLDIR/ui/wgts/rwgt \
    $IMPLDIR/ui/menu

SOURCES += \
    $$IMPLDIR/algs/compositestatestack.cpp \
    $$IMPLDIR/algs/graphbuilder.cpp \
    $$IMPLDIR/algs/pythonconveyor.cpp \
    $$IMPLDIR/algs/reportgenerator.cpp \
    $$IMPLDIR/algs/stringparser.cpp \
    $$IMPLDIR/utils/mathutils.cpp \
    $$IMPLDIR/ui/wgts/leftwidget.cpp \
    $$IMPLDIR/ui/wgts/lwgt/functionlayout.cpp \
    $$IMPLDIR/ui/wgts/lwgt/derivationlayout.cpp \
    $$IMPLDIR/ui/wgts/lwgt/integrationlayout.cpp \
    $$IMPLDIR/ui/wgts/lwgt/equationslayout.cpp \
    $$IMPLDIR/ui/wgts/lwgt/polynomialslayout.cpp \
    $$IMPLDIR/ui/wgts/lwgt/layoutInitializer.cpp \
    $$IMPLDIR/ui/wgts/lwgt/datamodel.cpp \
    $$IMPLDIR/ui/mainwindow.cpp \
    $$IMPLDIR/ui/menu.cpp \
    $$IMPLDIR/ui/wgts/rightwidget.cpp \
    $$IMPLDIR/ui/toolbar.cpp \
    $$IMPLDIR/ui/menu/sheetmenu.cpp \
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
    $$HEADDIR/algs/reportgenerator.h \
    $$HEADDIR/algs/stringparser.h \
    $$HEADDIR/settings/settings.h \
    $$HEADDIR/ui/wgts/leftwidget.h \
    $$HEADDIR/ui/wgts/lwgt/functionlayout.h \
    $$HEADDIR/ui/wgts/lwgt/derivationlayout.h \
    $$HEADDIR/ui/wgts/lwgt/integrationlayout.h \
    $$HEADDIR/ui/wgts/lwgt/equationslayout.h \
    $$HEADDIR/ui/wgts/lwgt/polynomialslayout.h \
    $$HEADDIR/ui/wgts/lwgt/layoutInitializer.h \
    $$HEADDIR/ui/wgts/lwgt/datamodel.h \
    $$HEADDIR/ui/mainwindow.h \
    $$HEADDIR/ui/menu.h \
    $$HEADDIR/ui/wgts/rightwidget.h \
    $$HEADDIR/ui/toolbar.h \
    $$HEADDIR/ui/menu/sheetmenu.h \
    $$HEADDIR/utils/buffer.h \
    $$HEADDIR/utils/errorhandler.h \
    $$HEADDIR/utils/graphInfo.h \
    $$HEADDIR/utils/sender.h \
    $$HEADDIR/utils/mathutils.h \
    $$HEADDIR/utils/validatestring.h \
    qcustomplot/qcustomplot.h \
    src/app/head/ui/wgts/lwgt/widgets.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

