#include "mainwindow.h"
//#include "ui_mainwindow.h"

// TODO: Сделать дефакто код чище, возможно стоит избавиться от таких членов класса как векторы.
MainWindow::MainWindow( QWidget* parent ) : QWidget( parent )
{
    QLabel* label = new QLabel( "f(x) = ", this );
    expressionInput = new QLineEdit( this );
    QLabel* rangeLabel = new QLabel( "Значения для x:", this );
    min = new QDoubleSpinBox( this );
    max = new QDoubleSpinBox( this );
    step = new QDoubleSpinBox( this );
    QPushButton* solve = new QPushButton( "Решить", this );
    QPushButton* clear = new QPushButton( "Очистить", this );

    tableWidget = new QTableWidget( this );
    tableWidget->setColumnCount( 2 );
    QStringList labels;
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels( labels );

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
    layout->addWidget( clear );
    layout->addWidget( tableWidget );
    setLayout( layout );

    connect( solve, &QPushButton::clicked, this, &MainWindow::solve );
    connect( clear, &QPushButton::clicked, this, &MainWindow::clearTable );
}

void MainWindow::showTable( const std::vector<double> x, const std::vector<double> y )
{
    tableWidget->clear();
    tableWidget->setRowCount( x.size() );
    QStringList labels;
    // TODO: Избавиться от данного повтора кода!
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels( labels );

    for( int i{}; i < x.size(); ++i )
    {
        QTableWidgetItem* itemX = new QTableWidgetItem( QString::number( x[i] ) );
        QTableWidgetItem* itemY = new QTableWidgetItem( QString::number( y[i] ) );
        tableWidget->setItem( i, 0, itemX );
        tableWidget->setItem( i, 1, itemY );
    }
}

void MainWindow::solve( void )
{
    auto expression = this->expressionInput->text();
    auto min        = this->min->value();
    auto max        = this->max->value();
    auto step       = this->step->value();

    for( double x = min; x <= max; x += step )
    {
        auto y = eval(
            (new StringParser(
                 expression.toStdString().c_str(), x )
             )->parseExpression(),
            x
        );

        this->x.push_back( x );
        this->y.push_back( y );
    }

    showTable( x, y );
    x.clear();
    y.clear();
}

void MainWindow::clearTable( void )
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
}
