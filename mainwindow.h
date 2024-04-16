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

    bool isSession{ false };

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout *layout );
    QAction* action( const QString& name, Menu* menu );

public slots:
    void printGraph( void );
    void printDiffGraph( void );
    void invokeLagrangeMethod( void );
    void invokeNewtonMethod( void );
    void invokeBerrutaMethod( void );

    void clearGraph( void );
    void resetZoom( void );

    void startSession( void );
    void endSession( void );

friend RightWidget;
friend LeftWidget;
};


#endif // MAINWINDOW_H
