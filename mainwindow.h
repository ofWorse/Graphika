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
    QLabel* errLabel;
    QVBoxLayout* layout;
    QTableWidget* tableWidget;

    QLineEdit* expressionInput;
    QDoubleSpinBox* min;
    QDoubleSpinBox* max;
    QDoubleSpinBox* step;

public:
    MainWindow( QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y );

private:
    template<typename... A>
    void createLayout( QVBoxLayout& layout, QWidget* wgt, A... args )
    {
        ( layout.addWidget( args ), ... );
    }

public slots:
    void solve( void );
    void clearTable( void );
    void handleParserError( const QString& err );
};


#endif // MAINWINDOW_H
