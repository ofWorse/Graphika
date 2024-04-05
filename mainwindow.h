#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "leftwidget.h"
#include "rightwidget.h"
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

    LeftWidget* leftWidget;
    RightWidget* rightWidget;
    QGridLayout* scrollLayout;
    QGridLayout* layout;
    SpecialBuffer buffer;

    std::vector<double> x;
    std::vector<double> y;

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout *layout );

public slots:
    void sendAction( void );
    void clearGraph( void );

friend RightWidget;
friend LeftWidget;
};


#endif // MAINWINDOW_H
