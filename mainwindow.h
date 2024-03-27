#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "functionlayout.h"
#include "polynomelayout.h"
#include "graphlayout.h"
#include "layoutfactory.h"
#include <QMainWindow>

// TODO: Сделать принцип ответственности единственного объекта.
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QMainWindow* mainWindow;
    Toolbar* toolbar;
    QWidget* centralwidget;

    FunctionLayout* fLayout;
    PolynomeLayout* pLayout;
    GraphLayout* gLayout;

    QGridLayout* layout;

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout *layout );

public slots:
    void openFunctionMenuWidget( void );
    void openPolynomialMenuWidget( void );
    void openGraphMenuWidget( void );

signals:
    void spinBoxValuesChanged( const std::vector<double>& values );
};


#endif // MAINWINDOW_H
