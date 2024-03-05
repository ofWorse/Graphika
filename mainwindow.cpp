#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget* parent ) : QWidget( parent )
{
    QLabel* label = new QLabel( "f(x) = ", this );
    QLineEdit* expressionInput = new QLineEdit( this );
    QLabel* rangeLabel = new QLabel( "Значения для x:", this );
    QDoubleSpinBox* min = new QDoubleSpinBox( this );
    QDoubleSpinBox* max = new QDoubleSpinBox( this );
    QDoubleSpinBox* step = new QDoubleSpinBox( this );
    QPushButton* solve = new QPushButton( "Решить", this );

    min->setRange( -100.0, 100.0 );
    min->setSingleStep( 0.1 );
    max->setRange( -100.0, 100.0 );
    max->setSingleStep( 0.1 );
    step->setRange( 0.1, 10.0 );
    step->setSingleStep( 0.1 );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( label );
    layout->addWidget( expressionInput );
    layout->addWidget( rangeLabel );
    layout->addWidget( min );
    layout->addWidget( max );
    layout->addWidget( step );
    layout->addWidget( solve );
    setLayout( layout );

    connect( solve, &QPushButton::clicked, this, [=]()
            {
        this->expression = expressionInput->text();
        this->min = min->value();
        this->max = max->value();
        this->step = step->value();

        for( double x = this->min; x <= this->max; x += this->step )
        {
            auto y = eval(
                (new StringParser(
                     expression.toStdString().c_str(), x )
                )->parseExpression(),
                x );

            this->x.push_back( x );
            this->y.push_back( y );
        }

        showTable( x, y );
    });
}

void MainWindow::showTable( const std::vector<double> x, const std::vector<double> y )
{
    QTableWidget* tableWidget = new QTableWidget( this );
    tableWidget->setRowCount( x.size() );
    tableWidget->setColumnCount( 2 );
    QStringList labels;
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels(labels);

    for( int i{}; i < x.size(); ++i )
    {
        QTableWidgetItem* itemX = new QTableWidgetItem( QString::number( x[i] ) );
        QTableWidgetItem* itemY = new QTableWidgetItem( QString::number( y[i] ) );

        tableWidget->setItem( i, 0, itemX );
        tableWidget->setItem( i, 1, itemY );
    }

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( tableWidget );
    setLayout( layout );
}
