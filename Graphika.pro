QT += core gui opengl printsupport #webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 compat console_build

SRCDIR = $$PWD/src/app
HEADDIR = $$SRCDIR/head
IMPLDIR = $$SRCDIR/impl

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += icons.qrc \
    pymodules.qrc \
    referenceinfo.qrc \
    resources/web/web.qrc \

INCLUDEPATH += ./python3.11 $$HEADDIR $$HEADDIR/algs \
    $$HEADDIR/ui $$HEADDIR/ui/wgts $$HEADDIR/ui/wgts/lwgt \
    $$HEADDIR/ui/wgts/rwgt $$HEADDIR/settings $$HEADDIR/utils \
    $$HEADDIR/ui/menu $$HEADDIR/console $$HEADDIR/algs/graphbuilder

LIBS += -lpython3.11

VPATH += $$IMPLDIR $$IMPLDIR/algs \
    $$IMPLDIR/ui $$IMPLDIR/ui/wgts $$IMPLDIR/ui/wgts/lwgt \
    $$IMPLDIR/utils $$IMPLDIR/ui/wgts/rwgt \
    $$IMPLDIR/ui/menu $$IMPLDIR/console $$IMPLDIR/algs/graphbuilder

SOURCES += \
    $$IMPLDIR/algs/compositestatestack.cpp \
    $$IMPLDIR/algs/graphbuilder/graphbuilder.cpp \
    $$IMPLDIR/algs/graphbuilder/gl3dgraphbuilder.cpp \
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
    $$IMPLDIR/ui/mainwindow.cpp \
    $$IMPLDIR/ui/menu.cpp \
    $$IMPLDIR/ui/wgts/rightwidget.cpp \
    $$IMPLDIR/ui/graphbar.cpp \
    $$IMPLDIR/ui/menubar.cpp \
    $$IMPLDIR/ui/menu/referencemenu.cpp \
    $$IMPLDIR/utils/buffer.cpp \
    $$IMPLDIR/utils/sender.cpp \
    $$IMPLDIR/utils/validatestring.cpp \
    $$IMPLDIR/main.cpp \
    $$IMPLDIR/console/consoleapplication.cpp \
    programmerdialog.cpp \
    qcustomplot/qcustomplot.cpp \
    $$IMPLDIR/console/commandhandler.cpp \
    $$IMPLDIR/console/commandcompleter.cpp

HEADERS += \
    $$HEADDIR/algs/compositestatestack.h \
    $$HEADDIR/algs/expressionvalidator.h \
    $$HEADDIR/algs/graphbuilder/graphbuilder.h \
    $$HEADDIR/algs/graphbuilder/gl3dgraphbuilder.h \
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
    $$HEADDIR/ui/mainwindow.h \
    $$HEADDIR/ui/menu.h \
    $$HEADDIR/ui/wgts/rightwidget.h \
    $$HEADDIR/ui/menubar.h \
    $$HEADDIR/ui/graphbar.h \
    $$HEADDIR/ui/menu/referencemenu.h \
    $$HEADDIR/utils/buffer.h \
    $$HEADDIR/utils/errorhandler.h \
    $$HEADDIR/utils/graphInfo.h \
    $$HEADDIR/utils/sender.h \
    $$HEADDIR/utils/mathutils.h \
    $$HEADDIR/console/consoleapplication.h \
    $$HEADDIR/utils/validatestring.h \
    programmerSettings.h \
    programmerdialog.h \
    qcustomplot/qcustomplot.h \
    $$HEADDIR/console/commandhandler.h \
    $$HEADDIR/console/commandcompleter.h \
    src/app/head/console/commands.h \
    src/app/head/settings/config.h \
    src/app/head/ui/wgts/lwgt/widgets.h \
    src/app/head/utils/programmerSettings.h \
    src/app/head/utils/programmerdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

