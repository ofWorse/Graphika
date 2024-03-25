#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stringparser.h"
#include "validatestring.h"
#include <QMainWindow>
#include <QScrollArea>

// TODO: Сделать принцип ответственности единственного объекта.
class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QMainWindow* mainWindow;
    QMenu *menu;
    QMenuBar* menuBar;
    QAction* functionMenu;
    QAction* derivateMenu;
    QAction* polinomeMenu;
    QAction* graphMenu;

    QString expression;
    ValidateString* validator;
    StringParser* parser;
    QLabel* errLabel;
    QGridLayout* layout;
    QGridLayout* scrollLayout;
    QWidget* widget;
    QGridLayout* widgetlayout;
    QTableWidget* tableWidget;

    QLineEdit* expressionInput;
    QDoubleSpinBox* min;
    QDoubleSpinBox* max;
    QDoubleSpinBox* step;
    QPushButton* solve;
    QPushButton* setX;
    QLabel* xIs;
    QLabel* countOfxLabel;
    QSpinBox* countOfx;
    QSpinBox* xVariables;
    QLabel* minLabel;
    QLabel* maxLabel;
    QLabel* stepLabel;
    QList<QSpinBox*> spinBoxes;

    bool couldBuildTable = true;
    std::vector<double> X;

public:
    MainWindow( QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y );

private:
    void setRange( void );
    void changeXSpinBoxes( int value );

    void hideFirstLayer( void );
    void hideSecondLayer( void );

    void updateLayoutCondition( void );

public slots:
    void openFunctionMenuWidget( void );
    void openDerivativeMenuWidget( void );
    void openPolynomialMenuWidget( void );
    void openGraphMenuWidget( void );

    void onSolveButtonClicked( void );
    void clearTable( void );
    void handleParserError( const QString& err );

    void onInputTextChanged( const QString& text );
    void onValidateStringValid();
    void onValidateStringInvalid();

    void switchLayers( int index );

    void showXDataSetupWindow( void );
    void setEnteredXData( void );

    void updateSpinBoxValues( void )
    {
        X.clear();
        std::cout << spinBoxes.size() << std::endl;
        for( const auto& spinBox : spinBoxes )
        {
            double value = spinBox->value();
            if( spinBox->text().isEmpty() )
            {
                value = 0;
            }
            X.push_back( value );
        }
    }

signals:
    void spinBoxValuesChanged( const std::vector<double>& values );
};


#endif // MAINWINDOW_H
