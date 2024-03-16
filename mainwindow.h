#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stringparser.h"
#include "validatestring.h"
#include <QMainWindow>


class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QString expression;
    ValidateString* validator;
    StringParser* parser;
    QLabel* errLabel;
    QVBoxLayout* layout;
    QTableWidget* tableWidget;

    QLineEdit* expressionInput;
    QDoubleSpinBox* min;
    QDoubleSpinBox* max;
    QDoubleSpinBox* step;
    QPushButton* solve;

    bool couldBuildTable = true;

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
    void onSolveButtonClicked( void );
    void clearTable( void );
    void handleParserError( const QString& err );

    void onInputTextChanged( const QString& text );
    void onValidateStringValid();
    void onValidateStringInvalid();
};


#endif // MAINWINDOW_H
