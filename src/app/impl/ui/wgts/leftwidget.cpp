#include "leftwidget.h"
#include <QLineEdit>
#include <QString>

LeftWidget::LeftWidget( SpecialBuffer& buffer, QWidget *parent ) : QWidget( parent )
{
    layout = new QGridLayout( this );
    widgets = new Widgets( this );
    functionLayout = new FunctionLayout;
    derivationLayout = new DerivationLayout;
    integrationLayout = new IntegrationLayout;
    equationsLayout = new EquationsLayout;
    polynomialsLayout = new PolynomialsLayout;
}

void LeftWidget::initLayout( SpecialBuffer& buffer, pymodules::Modules module )
{
    switch( module )
    {
    case pymodules::Modules::NIL:
        currentLayout = functionLayout;
        break;
    case pymodules::Modules::DIFFERENTIATION:
        currentLayout = derivationLayout;
        break;
    case pymodules::Modules::INTEGRATION:
        currentLayout = integrationLayout;
        break;
    case pymodules::Modules::EQUATIONS:
        currentLayout = equationsLayout;
        break;
    case pymodules::Modules::POLYNOMIALS:
        currentLayout = polynomialsLayout;
        break;
    }

    hideAllWidgets( layout );
    widgets->initWidgets();
    currentLayout->generateWidgets( *widgets );
    connectLabels( buffer );
    layout->addLayout( currentLayout->get(), 0, 0 );
}

void LeftWidget::hideAllWidgets( QLayout* layout )
{
    if ( !layout )
    {
        return;
    }

    if ( QGridLayout* gridLayout = qobject_cast<QGridLayout*>( layout ) )
    {
        for( int i = 0; i < gridLayout->count(); ++i )
        {
            QLayoutItem* item = gridLayout->itemAt( i );
            if ( item->widget() )
            {
                item->widget()->hide();
            }
            else if ( item->layout() )
            {
                hideAllWidgets( item->layout() );
            }
        }
    }
}

void LeftWidget::connectLabels( SpecialBuffer& buffer )
{
    connect( currentLayout->widgets->validator, &ValidateString::validExpression, currentLayout, &LayoutInitializer::onValidateDataValid );
    connect( currentLayout->widgets->validator, &ValidateString::invalidExpression, currentLayout, &LayoutInitializer::onValidateDataInvalid );
    connect( currentLayout->widgets->expressionInput, &QLineEdit::textChanged, currentLayout, &LayoutInitializer::onInputTextChanged );
    connect( currentLayout->widgets->derivativeExpressionInput, &QLineEdit::textChanged, currentLayout, &LayoutInitializer::onInputTextChanged );
    connect( currentLayout->widgets->parser, &StringParser::errorOccurred, currentLayout, &LayoutInitializer::handleParserError );
    connect( currentLayout->widgets->manualTableInput, &QPushButton::clicked, currentLayout, &LayoutInitializer::editTable );
    connect( currentLayout->widgets->clearTable, &QPushButton::clicked, currentLayout, &LayoutInitializer::clearDataTable );
    connect( currentLayout->widgets->typeOfVariableInput, QOverload<int>::of( &QComboBox::currentIndexChanged ), currentLayout, &LayoutInitializer::changeLayer );
    connect( currentLayout->widgets->solve, &QPushButton::clicked, [ &buffer, this ]()
            {
                currentLayout->onSolveButtonClicked( buffer );
            }
    );
    connect( currentLayout->widgets->solveEquations, &QPushButton::clicked, currentLayout, &LayoutInitializer::onSolveEquationsButtonClicked );
    connect( currentLayout->widgets->clearEquationsTable, &QPushButton::clicked, currentLayout, &LayoutInitializer::clearDataTable );
    connect( currentLayout->widgets->tableWidget, &QTableWidget::itemChanged, this, [ &buffer, this ]()
            {
                currentLayout->updateDataFromTable( buffer );
            }
    );
}
