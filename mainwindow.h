#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "leftlayout.h"
#include "rightlayout.h"
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

    LeftLayout* leftLayout;
    RightLayout* rightLayout;
    RightLayout* tempLayout;
    QGridLayout* layout;
    SpecialBuffer buffer;

    std::vector<double> x;
    std::vector<double> y;

public:
    explicit MainWindow( QWidget* parent = nullptr );

private:
    void clearLayout( QLayout *layout );

private slots:
    void openRightMenuWidget( void );
    void openLeftMenuWidget( void );

friend LeftLayout;
};


#endif // MAINWINDOW_H
