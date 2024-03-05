#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stringparser.h"
#include <QMainWindow>

using namespace parser;

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QString expression;
    StringParser* parser;

    double min;
    double max;
    double step;

std::vector<double> x;
std::vector<double> y;

public:
    MainWindow( QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y );
};


#endif // MAINWINDOW_H
