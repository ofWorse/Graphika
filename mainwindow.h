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
    QTableWidget* tableWidget;

    QLineEdit* expressionInput;
    QDoubleSpinBox* min;
    QDoubleSpinBox* max;
    QDoubleSpinBox* step;

    std::vector<double> x;
    std::vector<double> y;

public:
    MainWindow( QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y );

public slots:
    void solve( void );
    void clearTable( void );
};


#endif // MAINWINDOW_H
