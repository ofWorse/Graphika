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
    // TODO: Присобачить к инициализации основного слоя
    template<typename... A>
    QVBoxLayout* addLayout( QWidget* wgt, A... args )
    {
        QVBoxLayout* layout = new QVBoxLayout( wgt );
        ( ..., [args, layout]()
         {
             layout->addWidget( args );
         }
         ) ();
        return layout;
    }

public slots:
    void solve( void );
    void clearTable( void );
    void handleParserError( const QString& err );
};


#endif // MAINWINDOW_H
