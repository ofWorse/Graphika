#include "derivationlayout.h"

void DerivationLayout::generateWidgets( Widgets& widgets )
{
    layout = new QGridLayout;
    layout->addWidget( widgets.label, 0, 0 );
    layout->addWidget( widgets.expressionInput, 0, 1, 1, 10 );
    layout->addWidget( widgets.derivativeLabel, layout->rowCount() - layout->rowCount() + 1, 0 );
    layout->addWidget( widgets.derivativeExpressionInput, layout->rowCount() - layout->rowCount() + 1, 1, 1, 10 );
    layout->addWidget( widgets.errLabel, 2, 0 );
    layout->addWidget( widgets.typeOfInput, 3, 0 );
    layout->addWidget( widgets.typeOfVariableInput, 3, 1 );
    layout->addWidget( widgets.minLabel, 4, 0 );
    layout->addWidget( widgets.min, 4, 1 );
    layout->addWidget( widgets.maxLabel, 5, 0 );
    layout->addWidget( widgets.max, 5, 1 );
    layout->addWidget( widgets.stepLabel, 6, 0 );
    layout->addWidget( widgets.step, 6, 1 );
    layout->addWidget( widgets.nodesLabel, 7, 0 );
    layout->addWidget( widgets.nodes, 7, 1 );
    layout->addWidget( widgets.solve, 8, 0 );
    layout->addWidget( widgets.clearTable, 8, 1 );
    layout->addWidget( widgets.buildGraph, 9, 0 );
    layout->addWidget( widgets.manualTableInput, 9, 1 );
    layout->addWidget( widgets.tableWidget, 10, 0, 1, 2 );
    layout->addWidget( widgets.averError, layout->rowCount(), 0 );
    layout->addWidget( widgets.error = new QLineEdit( this ), layout->rowCount() - 1, 1 );
    layout->addWidget( widgets.calculatedArea = new QLabel( "Вычисленная площадь: ", this ),
                      layout->rowCount(), 0 );
    layout->addWidget( widgets.area = new QLineEdit( this ), layout->rowCount() - 1, 1 );

    layout->setColumnStretch( 1, 10 );
    layout->setColumnStretch( 0, 2 );

    widgets.derivativeLabel->setText( "f'(x) = " );

    int currentColumnCount = widgets.tableWidget->columnCount();
    widgets.tableWidget->setColumnCount( currentColumnCount + 1 );
    auto item = new QTableWidgetItem( "Y'" );
    widgets.tableWidget->setHorizontalHeaderItem( currentColumnCount, item );

    widgets.averError->setText( "Средняя погрешность: " );
    widgets.averError->show();
    widgets.error->show();
    // УБРАТЬ ПРИ АКТИВАЦИИ
    {
        widgets.error->setDisabled( true );
        widgets.averError->setDisabled( true );
    }

    this->widgets = &widgets;
    this->hideWidgets( widgets.area, widgets.calculatedArea );
    hideFirstLayer();
}

QGridLayout *DerivationLayout::get()
{
    return layout;
}

void DerivationLayout::saveData( void )
{


}

void DerivationLayout::loadData( void )
{


}
