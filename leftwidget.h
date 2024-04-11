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
    QPushButton* manualTableInput;
    QTableWidget* tableWidget;
    QGridLayout* layout;
    QList<QSpinBox*> spinBoxes;

    bool manualInput = false;
    bool couldBuildTable = true;
    std::vector<double> X;
    std::vector<double> Y;

public:
    explicit LeftWidget( SpecialBuffer& buffer, QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y );

private:
    void setRange( void );

    void setupNodes( const double node );

    std::vector<double> fillDataFromTable( int column );
    bool tableIsEmpty( void );

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

    void editTable( void );
    void updateDataFromTable( SpecialBuffer& buffer );

    void acceptData( const QString& expr, const double a, const double b );

signals:
    void readyToDraw( const std::vector<double> x, const std::vector<double> y );
};

#endif // LEFTWIDGET_H
