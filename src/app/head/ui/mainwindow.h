#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "leftwidget.h"
#include "rightwidget.h"
#include "sender.h"
#include "compositestatestack.h"
#include "menu.h"
#include "sheetmenu.h"

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

    QMap<QAction*, std::function<void()>> menuSlots;
    QList<QWidget*> widgets;

    bool isSession{ false };
    bool unpinned{ false };
    bool legendEnabled{ false };

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout* layout );
    void buildSpecificWidget( int index );
    void printDiffGraph( void );
    void calculateIntegral( void );
    void buildPolynomeGraph( void );
    void invokePolynomeMethod( pymodules::Methods method );

public slots:
    void openMenu( int index, pymodules::Modules module );
    void printFunctionGraph( void );
    void calculateSys( QVector<QVector<double>>& data );

    void clearGraph( void );
    void resetZoom( void );
    void moveLegend( void );
    void showLegend( void );
    void stepBack( void );
    void stepForward( void );
    void zoomIn( void );
    void zoomOut( void );
    void unpinGraph( void );

    void startSession( void );
    void endSession( void );
    void openAboutMenu( void );
    void openLicenseMenu( void );

    void draw( void );
    void deleteWidgets( void );

signals:
    void buildDerivativeWidgets( pymodules::Modules module, SpecialBuffer& buffer );
    void buildDefaultWidgets( pymodules::Modules module, SpecialBuffer& buffer );

friend RightWidget;
friend LeftWidget;
};


#endif // MAINWINDOW_H
