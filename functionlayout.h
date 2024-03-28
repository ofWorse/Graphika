#ifndef FUNCTIONLAYOUT_H
#define FUNCTIONLAYOUT_H

#include <QWidget>
#include "validatestring.h"
#include "stringparser.h"

class FunctionLayout : public QWidget
{
    Q_OBJECT
private:
    ValidateString* validator;
    StringParser* parser;
    QLabel* errLabel;
    QLabel* xIs;
    QSpinBox* xVariables;
    QLabel* minLabel;
    QLabel* maxLabel;
    QLabel* stepLabel;
    QLabel* nodesLabel;
    QDoubleSpinBox* nodes;
    QDoubleSpinBox* min;
    QDoubleSpinBox* max;
    QDoubleSpinBox* step;
    QLineEdit* expressionInput;
    QPushButton* solve;
    QTableWidget* tableWidget;
    QGridLayout* scrollLayout;
    QList<QSpinBox*> spinBoxes;

    QGridLayout* layout;

    bool couldBuildTable = true;
    std::vector<double> X;

public:
    explicit FunctionLayout( QWidget* parent = nullptr );
    QGridLayout* getLayout( void )
    {
        return layout;
    }
    void showTable( const std::vector<double> x, const std::vector<double> y );

private:
    void setRange( void );

    void setupNodes( const double node );

public slots:
    void onValidateStringValid( void );
    void onValidateStringInvalid( void );

    void handleParserError( const QString& err );

    void onInputTextChanged( const QString& text );

    void onSolveButtonClicked( void );

    void clearTable( void );

    void hideFirstLayer( void );
    void hideSecondLayer( void );

    void switchLayers( int index );

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
};

#endif // FUNCTIONLAYOUT_H
