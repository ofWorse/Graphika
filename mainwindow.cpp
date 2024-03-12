#include "mainwindow.h"
//#include "ui_mainwindow.h"

// TODO: Сделать дефакто код чище
MainWindow::MainWindow( QWidget* parent ) : QWidget( parent )
{
    QLabel* label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );
    QLabel* minLabel = new QLabel( "Минимальное значение x:", this );
    QLabel* maxLabel = new QLabel( "Максимальное значение x:", this );
    QLabel* stepLabel = new QLabel( "Шаг по x:", this );
    expressionInput = new QLineEdit( this );
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

    layout = new QVBoxLayout( this );
    createLayout( *layout, this, label, expressionInput, errLabel,
                 minLabel, min, maxLabel, max, stepLabel,
                 step, solve, clear, tableWidget );
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

    std::vector<double> X;
    std::vector<double> Y;

    for( double x = min; x <= max; x += step )
    {
        parser = new StringParser( expression.toStdString().c_str(), x );
        connect( parser, &StringParser::errorOccurred, this, &MainWindow::handleParserError );

        auto parsed = parser->parseExpression();
        auto y = parser->eval( parsed, x );

        X.push_back( x );
        Y.push_back( y );
    }

    showTable( X, Y );
}

void MainWindow::clearTable( void )
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    errLabel->clear();
}

// TODO: Добавить очистку таблицы (clearTable() - не работает)
void MainWindow::handleParserError( const QString& err )
{
    errLabel->setStyleSheet( "QLabel { color : red; }" );
    errLabel->setText( err + "!" );
}

