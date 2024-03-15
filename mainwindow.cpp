#include "mainwindow.h"
//#include "ui_mainwindow.h"

// TODO: Сделать дефакто код чище
MainWindow::MainWindow( QWidget* parent ) : QWidget( parent )
{
    validator = new ValidateString( this );
    connect( validator, &ValidateString::validExpression, this, &MainWindow::onValidateStringValid );
    connect( validator, &ValidateString::invalidExpression, this, &MainWindow::onValidateStringInvalid );
    parser = new StringParser( this );


    QLabel* label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );

    connect( parser, &StringParser::errorOccurred, this, &MainWindow::handleParserError );

    QLabel* minLabel = new QLabel( "Минимальное значение x:", this );
    QLabel* maxLabel = new QLabel( "Максимальное значение x:", this );
    QLabel* stepLabel = new QLabel( "Шаг по x:", this );

    expressionInput = new QLineEdit( this );
    connect( expressionInput, &QLineEdit::textChanged, this, &MainWindow::onInputTextChanged );

    min = new QDoubleSpinBox( this );
    max = new QDoubleSpinBox( this );
    step = new QDoubleSpinBox( this );

    solve = new QPushButton( "Решить", this );
    solve->setEnabled( false );
    connect( solve, &QPushButton::clicked, this, &MainWindow::onSolveButtonClicked );

    QPushButton* clear = new QPushButton( "Очистить", this );
    connect( clear, &QPushButton::clicked, this, &MainWindow::clearTable );

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

    //connect( solve, &QPushButton::clicked, this, &MainWindow::solve );
}

void MainWindow::showTable( const std::vector<double> x, const std::vector<double> y )
{
    tableWidget->clear();
    tableWidget->setRowCount( x.size() );
    QStringList labels;
    // TODO: Избавиться от данного повтора кода!
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels( labels );

    for( std::size_t i{}; i < x.size(); ++i )
    {
        QTableWidgetItem* itemX = new QTableWidgetItem( QString::number( x[i] ) );
        QTableWidgetItem* itemY = new QTableWidgetItem( QString::number( y[i] ) );
        tableWidget->setItem( i, 0, itemX );
        tableWidget->setItem( i, 1, itemY );
    }
}

void MainWindow::onSolveButtonClicked( void )
{
    auto expression = this->expressionInput->text();
    auto min        = this->min->value();
    auto max        = this->max->value();
    auto step       = this->step->value();

    std::vector<double> X;
    for( double i = min; i <= max; i += step )
    {
        X.push_back( i );
    }

    parser->setDataX( X );

    std::vector<double> Y = parser->parseExpression( expression.toStdString().c_str() );


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

void MainWindow::onInputTextChanged( const QString &text )
{
    validator->validateExpression( text );
}

void MainWindow::onValidateStringValid()
{
    solve->setEnabled( true );
}

void MainWindow::onValidateStringInvalid()
{
    solve->setEnabled( false );
}
