#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include "rightwidget.h"
#include "validatestring.h"
#include "stringparser.h"
#include "buffer.h"
#include "mathutils.h"
#include "settings.h"



class LeftWidget : public QWidget
{
    Q_OBJECT
private:
    ValidateString* validator;
    StringParser* parser;
    QLabel* label;
    QLabel* errLabel;
    QLabel* xIs;
    QSpinBox* xVariables;
    QLabel* typeOfInput;
    QComboBox* typeOfVariableInput;
    QPushButton* clearTable;
    QLabel* minLabel;
    QLabel* maxLabel;
    QLabel* stepLabel;
    QLabel* nodesLabel;
    QDoubleSpinBox* nodes;
    QDoubleSpinBox* min;
    QDoubleSpinBox* max;
    QDoubleSpinBox* step;
    QLineEdit* expressionInput;
    QLabel* derivativeLabel;
    QLineEdit* derivativeExpressionInput;
    QPushButton* solve;
    QPushButton* manualTableInput;
    QTableWidget* tableWidget;
    QGridLayout* layout;

    QLabel* averError;
    QLineEdit* error;

    QLabel* oddsInputLabel;
    QTableWidget* equationsTableWidget;
    QPushButton* solveEquations;
    QPushButton* clearEquationsTable;
    QLabel* resultOfEquations;
    QLineEdit* eqResult;
    QLabel* resultDescription;
    QLineEdit* description;
    /* временная заглушка */
    bool equationOpened = false;

    QLabel* calculatedArea;
    QLineEdit* area;

    QList<QSpinBox*> spinBoxes;

    bool derivativeLabelActive = false;
    bool manualInput = false;
    bool couldBuildTable = true;
    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> dY;

public:
    QPushButton* buildGraph;

public:
    explicit LeftWidget( SpecialBuffer& buffer, QWidget* parent = nullptr );
    void showTable( const std::vector<double> x, const std::vector<double> y, const std::vector<double> dY );
    QLineEdit* getExpressionInput() const;

private:

    void initLabels( void );
    void connectLabels( SpecialBuffer& buffer );
    void setRange( void );

    void setupNodes( const double node );

    std::vector<double> fillDataFromTable( int column );
    bool tableIsEmpty( void );

    void initLayout( void );
    void buildWidgetForDerivativeOperations( SpecialBuffer& buffer );
    void buildWidgetForIntegrationOperations( SpecialBuffer& buffer );
    void buildWidgetForEquationOperations( SpecialBuffer& buffer );
    void setWidgetToDefaultStatement( SpecialBuffer& buffer );
    void hideAll( void );
    void deleteAll( void );

public slots:
    void onValidateStringValid( void );
    void onValidateStringInvalid( void );

    void handleParserError( const QString& err );

    void onInputTextChanged( const QString& text );

    void onSolveButtonClicked( SpecialBuffer& buffer );
    void onSolveEquationButtonClicked( void );

    void clearDataTable( void );
    void handleClearGraph( RightWidget& right );

    void hideFirstLayer( bool isDerivativeMenu );
    void hideSecondLayer( bool isDerivativeMenu );

    void changeLayer( int index );
    void switchLayers( int index, bool isDerivativeMenu );

    void editTable( void );
    void updateDataFromTable( SpecialBuffer& buffer );

    void acceptData( const QString& expr, const double a, const double b );
    void acceptArea( std::string& area );

    void rebuildWidgets( pymodules::Modules modules, SpecialBuffer& buffer );

signals:
    void readyToDraw( const std::vector<double> x, const std::vector<double> y );
    void sendData( QObject& data, bool toRemove );
    void readyToSendLinearEquationsData( QVector<QVector<double>>& data );
};

#endif // LEFTWIDGET_H
