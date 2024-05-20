#include "equationslayout.h"

void EquationsLayout::generateWidgets( Widgets& widgets )
{
    layout = new QGridLayout;
    widgets.oddsInputLabel->setText( QString::asprintf( "Введите через пробел коэффициенты \n линейных уравнений и свободный член" ) );
    QStringList labels;
    labels << "C1 C2 ... Cn" << "X0";
    widgets.equationsTableWidget->setColumnCount( 2 );
    widgets.equationsTableWidget->setRowCount( 10 );
    for( int row{}; row < widgets.equationsTableWidget->rowCount(); ++row )
    {
        QRadioButton* button = new QRadioButton;
        widgets.equationsTableWidget->setCellWidget( row, 2, button );
    }
    widgets.equationsTableWidget->setHorizontalHeaderLabels( labels );
    widgets.solveEquations->setText( "Решить" );
    widgets.clearEquationsTable->setText( "Очистить Таблицу" );
    widgets.resultOfEquations->setText( "Результат вычислений: " );
    widgets.resultDescription->setText( "Описание: " );

    layout->addWidget( widgets.oddsInputLabel, 0, 0 );
    layout->addWidget( widgets.equationsTableWidget, 1, 0, 1, 2 );
    layout->addWidget( widgets.solveEquations, 2, 0 );
    layout->addWidget( widgets.clearEquationsTable, 2, 1 );
    layout->addWidget( widgets.resultOfEquations, 3, 0 );
    layout->addWidget( widgets.eqResult, 4, 0 );
    layout->addWidget( widgets.resultDescription, 5, 0 );
    layout->addWidget( widgets.description, 6, 0 );

    // ВРЕМЕННО ЗАКРОЕМ ДОСТУП К ДАННЫМ ПУНКТАМ
    {
        widgets.resultDescription->setDisabled( true );
        widgets.description->setDisabled( true );
    }
    this->widgets = &widgets;
}

QGridLayout *EquationsLayout::get()
{
    return layout;
}
