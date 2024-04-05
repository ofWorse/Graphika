#include "leftwidget.h"

LeftWidget::LeftWidget( SpecialBuffer& buffer, QWidget *parent ) : QWidget( parent )
{
    validator = new ValidateString( this );
    connect( validator, &ValidateString::validExpression, this, &LeftWidget::onValidateStringValid );
    connect( validator, &ValidateString::invalidExpression, this, &LeftWidget::onValidateStringInvalid );
    parser = new StringParser( this );

    QLabel* label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );

    connect( parser, &StringParser::errorOccurred, this, &LeftWidget::handleParserError );

    QLabel* typeOfInput = new QLabel( "Ввод значений x: ", this );

    QComboBox* typeOfVariableInput = new QComboBox( this );
    typeOfVariableInput->addItems( { "с шагом", "с узлами" } );

    { // Переменные элементы
        minLabel = new QLabel( "Минимальное значение x:", this );
        maxLabel = new QLabel( "Максимальное значение x:", this );
        stepLabel = new QLabel( "Шаг по x:", this );

        nodesLabel = new QLabel( "Кол-во узлов: ", this );

        min = new QDoubleSpinBox( this );
        max = new QDoubleSpinBox( this );
        step = new QDoubleSpinBox( this );
        nodes = new QDoubleSpinBox( this );
    } // Переменные элементы

    expressionInput = new QLineEdit( this );
    connect( expressionInput, &QLineEdit::textChanged, this, &LeftWidget::onInputTextChanged );

    solve = new QPushButton( "Решить", this );
    solve->setStyleSheet( "background-color: tomato;" );
    solve->setEnabled( false );
    connect( solve, &QPushButton::clicked, [&buffer, this]()
        {
            onSolveButtonClicked( buffer );
        } );

    QPushButton* clearTable = new QPushButton( "Очистить таблицу", this );
    connect( clearTable, &QPushButton::clicked, this, &LeftWidget::clearTable );

    tableWidget = new QTableWidget( this );
    tableWidget->setColumnCount( 2 );
    QStringList labels;
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels( labels );

    setRange();

    layout = new QGridLayout( this );
    layout->addWidget( label, 0, 0 );
    layout->addWidget( expressionInput, 0, 1 );
    layout->addWidget( errLabel, 1, 0 );
    layout->addWidget( typeOfInput, 2, 0 );
    layout->addWidget( typeOfVariableInput, 2, 1 );
    layout->addWidget( minLabel, 3, 0 );
    layout->addWidget( min, 3, 1 );
    layout->addWidget( maxLabel, 4, 0 );
    layout->addWidget( max, 4, 1 );
    layout->addWidget( stepLabel, 5, 0 );
    layout->addWidget( step, 5, 1 );
    layout->addWidget( nodesLabel, 6, 0 );
    layout->addWidget( nodes, 6, 1 );
    layout->addWidget( solve, 7, 0 );
    layout->addWidget( clearTable, 7, 1 );
    layout->addWidget( tableWidget, 8, 0, Qt::AlignCenter );
    layout->setColumnStretch( 1, 10 );
    layout->setColumnStretch( 0, 2 );
    hideFirstLayer();

    connect( typeOfVariableInput, QOverload<int>::of( &QComboBox::currentIndexChanged ), this, &LeftWidget::switchLayers );
}

void LeftWidget::showTable( const std::vector<double> x, const std::vector<double> y )
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

void LeftWidget::setRange( void )
{
    min->setRange( -100.0, 100.0 );
    min->setSingleStep( 0.1 );
    max->setRange( -100.0, 100.0 );
    max->setSingleStep( 0.1 );
    step->setRange( 0.01, 10.0 );
    step->setSingleStep( 0.1 );
    nodes->setRange( 0.0, 5000.0 );
}

void LeftWidget::onValidateStringValid( void )
{
    solve->setEnabled( true );
    solve->setStyleSheet( "background-color: lightgreen;" );
}

void LeftWidget::onValidateStringInvalid( void )
{
    solve->setEnabled( false );
    solve->setStyleSheet( "background-color: tomato;" );
}

void LeftWidget::handleParserError( const QString &err )
{
    couldBuildTable = false;
    errLabel->setStyleSheet( "QLabel { color : red; }" );
    errLabel->setText( err + "!" );
}

void LeftWidget::onInputTextChanged( const QString &text )
{
    validator->validateExpression( text );
}

void LeftWidget::onSolveButtonClicked( SpecialBuffer& buffer )
{
    auto expression = this->expressionInput->text();
    auto min        = this->min->value();
    auto max        = this->max->value();
    auto step       = this->step->value();

    // TODO: Это отдельный метод и подумать над реализацией
    if( !nodes->isVisible() )
    {
        for( double i = min; i <= max; i += step )
        {
            X.push_back( i );
        }
    }
    else
    {
        setupNodes( nodes->value() );
    }

    parser->setDataX( X );
    std::vector<double> Y = parser->parseExpression( expression.toStdString().c_str() );
    buffer.x = QVector<double>( X.begin(), X.end() );
    buffer.y = QVector<double>( Y.begin(), Y.end() );

    if( couldBuildTable )
    {
        showTable( X, Y );
    }
    couldBuildTable = true;
    X.clear();
}

void LeftWidget::clearTable()
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    errLabel->clear();
}

void LeftWidget::handleClearGraph( RightWidget &right )
{
    right.clearGraph();
}

void LeftWidget::hideFirstLayer( void )
{
    X.clear();

    nodes->hide();
    nodesLabel->hide();

    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    stepLabel->show();
    step->show();
}

void LeftWidget::hideSecondLayer( void )
{
    X.clear();

    stepLabel->hide();
    step->hide();

    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    nodesLabel->show();
    nodes->show();
}

void LeftWidget::setupNodes( const double node )
{
    X.clear();
    auto min = this->min->value();
    auto max = this->max->value();
    for( auto delta = min; delta <= max; delta += ( abs( min ) + abs( max ) ) / ( node + 1 ) )
    {
        X.push_back( delta );
    }
}

void LeftWidget::switchLayers( int index )
{
    if( index == 0 )
    {
        hideFirstLayer();
    }
    else if( index == 1 )
    {
        hideSecondLayer();
    }
}

// Для дебага
void LeftWidget::setEnteredXData()
{
    if( X.empty() ) std::cout << "empty" << std::endl;
    for( const auto& x : X )
    {
        std::cout << x << " ";;
    }
    std::cout << std::endl;
}
