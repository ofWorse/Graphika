#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "leftwidget.h"
#include "rightwidget.h"
#include "layoutfactory.h"
#include <QMainWindow>
#include "sender.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QMainWindow* mainWindow;
    Toolbar* toolbar;
    QWidget* centralwidget;

    LeftWidget* leftWidget;
    RightWidget* rightWidget;
    QGridLayout* scrollLayout;
    QGridLayout* layout;
    SpecialBuffer buffer;
    Sender sender;

    std::vector<double> x;
    std::vector<double> y;

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout *layout );

public slots:
    void printGraph( void );
    void invokeLagrangeMethod( void );
    void invokeNewtonMethod( void );
    void invokeBerrutaMethod( void );

    void clearGraph( void );
    void resetZoom( void );

friend RightWidget;
friend LeftWidget;
};


#endif // MAINWINDOW_H
