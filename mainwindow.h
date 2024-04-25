#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "leftwidget.h"
#include "rightwidget.h"
#include "layoutfactory.h"
#include "sender.h"
#include "compositestatestack.h"
#include "menu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Menu* menu;
    QMainWindow* mainWindow;
    Toolbar* toolbar;
    QWidget* centralwidget;

    LeftWidget* leftWidget;
    RightWidget* rightWidget;
    QGridLayout* scrollLayout;
    QGridLayout* layout;
    SpecialBuffer buffer;
    CompositeStateStack logStack;
    Sender sender;

    std::vector<double> x;
    std::vector<double> y;

    pymodules::Modules widgetState = pymodules::Modules::NIL;
    pymodules::Methods methodOfInterpolation;

    bool isSession{ false };

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout* layout );
    void printDiffGraph( void );
    void buildPolynomeGraph( void );
    void invokeLagrangeMethod( void );
    void invokeNewtonMethod( void );
    void invokeBerrutaMethod( void );

public slots:
    void openFunctionMenu( void );
    void printFunctionGraph( void );
    void openDerivativeMenu( void );
    void openIntegrationMenu( void );
    void openEquationSystemMenu( void );
    void openLagrangeMenu( void );
    void openNewtonMenu( void );
    void openBerrutaMenu( void );

    void clearGraph( void );
    void resetZoom( void );
    void moveLegend( void );
    void seeLegend( void );
    void stepBack( void );

    void startSession( void );
    void endSession( void );

    void draw( void );

signals:
    void buildDerivativeWidgets( pymodules::Modules module, SpecialBuffer& buffer );
    void buildDefaultWidgets( pymodules::Modules module, SpecialBuffer& buffer );

friend RightWidget;
friend LeftWidget;
};


#endif // MAINWINDOW_H
