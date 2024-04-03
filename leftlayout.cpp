#include "leftlayout.h"

LeftLayout::LeftLayout( SpecialBuffer& buffer, QWidget *parent ) : QWidget( parent )
{
    validator = new ValidateString( this );
    connect( validator, &ValidateString::validExpression, this, &LeftLayout::onValidateStringValid );
    connect( validator, &ValidateString::invalidExpression, this, &LeftLayout::onValidateStringInvalid );
    parser = new StringParser( this );

    QLabel* label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );

    connect( parser, &StringParser::errorOccurred, this, &LeftLayout::handleParserError );

    QLabel* typeOfInput = new QLabel( "Ввод значений x: ", this );

    QComboBox* typeOfVariableInput = new QComboBox( this );
    typeOfVariableInput->addItems( { "с шагом", "с узлами" } );

    { // Переменные элементы
        minLabel = new QLabel( "Минимальное значение x:", this );
        maxLabel = new QLabel( "Максимальное значение x:", this );
        stepLabel = new QLabel( "Шаг по x:", this );

        nodesLabel = new QLabel( "Число узлов между пределами: ", this );

        min = new QDoubleSpinBox( this );
        max = new QDoubleSpinBox( this );
        step = new QDoubleSpinBox( this );
        nodes = new QDoubleSpinBox( this );
    } // Переменные элементы

    expressionInput = new QLineEdit( this );
    connect( expressionInput, &QLineEdit::textChanged, this, &LeftLayout::onInputTextChanged );

    solve = new QPushButton( "Решить", this );
    solve->setEnabled( false );
    connect( solve, &QPushButton::clicked, [&buffer, this]()
        {
            onSolveButtonClicked( buffer );
        } );

    QPushButton* clear = new QPushButton( "Очистить", this );
    connect( clear, &QPushButton::clicked, this, &LeftLayout::clearTable );

    tableWidget = new QTableWidget( this );
    tableWidget->setColumnCount( 2 );
    QStringList labels;
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels( labels );

    setRange();

    QScrollArea *scrollArea = new QScrollArea( this );
    layout = new QGridLayout( this );
    QWidget *scrollContentWidget = new QWidget();
    scrollLayout = new QGridLayout( scrollContentWidget );
    scrollLayout->addWidget( label, 0, 0 );
    scrollLayout->addWidget( expressionInput, 0, 1 );
    scrollLayout->addWidget( errLabel, 1, 0 );
    scrollLayout->addWidget( typeOfInput, 2, 0 );
    scrollLayout->addWidget( typeOfVariableInput, 2, 1 );
    scrollLayout->addWidget( minLabel, 3, 0 );
    scrollLayout->addWidget( min, 3, 1 );
    scrollLayout->addWidget( maxLabel, 4, 0 );
    scrollLayout->addWidget( max, 4, 1 );
    scrollLayout->addWidget( stepLabel, 5, 0 );
    scrollLayout->addWidget( step, 5, 1 );
    scrollLayout->addWidget( nodesLabel, 6, 0 );
    scrollLayout->addWidget( nodes, 6, 1 );
    scrollLayout->addWidget( solve, 7, 0 );
    scrollLayout->addWidget( clear, 7, 1 );
    scrollLayout->addWidget( tableWidget, 9, 0, Qt::AlignCenter );
    scrollLayout->setColumnStretch( 1, 10 );
    scrollLayout->setColumnStretch( 0, 2 );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    hideFirstLayer();

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    connect( typeOfVariableInput, QOverload<int>::of( &QComboBox::currentIndexChanged ), this, &LeftLayout::switchLayers );
}

void LeftLayout::showTable( const std::vector<double> x, const std::vector<double> y )
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

void LeftLayout::setRange( void )
{
    min->setRange( -100.0, 100.0 );
    min->setSingleStep( 0.1 );
    max->setRange( -100.0, 100.0 );
    max->setSingleStep( 0.1 );
    step->setRange( 0.01, 10.0 );
    step->setSingleStep( 0.1 );
    nodes->setRange( 0.0, 5000.0 );
}

void LeftLayout::onValidateStringValid( void )
{
    solve->setEnabled( true );
}

void LeftLayout::onValidateStringInvalid( void )
{
    solve->setEnabled( false );
}

void LeftLayout::handleParserError( const QString &err )
{
    couldBuildTable = false;
    errLabel->setStyleSheet( "QLabel { color : red; }" );
    errLabel->setText( err + "!" );
}

void LeftLayout::onInputTextChanged( const QString &text )
{
    validator->validateExpression( text );
}

void LeftLayout::onSolveButtonClicked( SpecialBuffer& buffer )
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

void LeftLayout::clearTable()
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    errLabel->clear();
}

void LeftLayout::hideFirstLayer( void )
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

void LeftLayout::hideSecondLayer( void )
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

void LeftLayout::setupNodes( const double node )
{
    X.clear();
    auto min = this->min->value();
    auto max = this->max->value();
    for( auto delta = min; delta <= max; delta += ( abs( min ) + abs( max ) ) / ( node + 1 ) )
    {
        X.push_back( delta );
    }
}

void LeftLayout::switchLayers( int index )
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
void LeftLayout::setEnteredXData()
{
    if( X.empty() ) std::cout << "empty" << std::endl;
    for( const auto& x : X )
    {
        std::cout << x << " ";;
    }
    std::cout << std::endl;
}
