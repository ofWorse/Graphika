#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include "rightwidget.h"
#include "validatestring.h"
#include "stringparser.h"
#include "buffer.h"

class LeftWidget : public QWidget
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
    QGridLayout* layout;
    QList<QSpinBox*> spinBoxes;

    bool couldBuildTable = true;
    std::vector<double> X;

public:
    explicit LeftWidget( SpecialBuffer& buffer, QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y );

private:
    void setRange( void );

    void setupNodes( const double node );

public slots:
    void onValidateStringValid( void );
    void onValidateStringInvalid( void );

    void handleParserError( const QString& err );

    void onInputTextChanged( const QString& text );

    void onSolveButtonClicked( SpecialBuffer& buffer );

    void clearTable( void );
    void handleClearGraph( RightWidget& right );

    void hideFirstLayer( void );
    void hideSecondLayer( void );

    void switchLayers( int index );

    void setEnteredXData( void );
};

#endif // LEFTWIDGET_H
