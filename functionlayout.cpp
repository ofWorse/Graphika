#include "functionlayout.h"

FunctionLayout::FunctionLayout( QWidget *parent ) : QWidget( parent )
{
    validator = new ValidateString( this );
    connect( validator, &ValidateString::validExpression, this, &FunctionLayout::onValidateStringValid );
    connect( validator, &ValidateString::invalidExpression, this, &FunctionLayout::onValidateStringInvalid );
    parser = new StringParser( this );

    QLabel* label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );

    connect( parser, &StringParser::errorOccurred, this, &FunctionLayout::handleParserError );

    QLabel* typeOfInput = new QLabel( "Ввод значений x: ", this );

    QComboBox* typeOfVariableInput = new QComboBox( this );
    typeOfVariableInput->addItems( { "вручную", "автоматически с шагом", "автоматически с узлами" } );

    { // Переменные элементы
        countOfxLabel = new QLabel( "Число точек x = ", this );
        countOfx = new QSpinBox( this );
        setX = new QPushButton( "Ввести x", this );

        countOfx->setSingleStep( 1 );
        countOfx->setMinimum( 0 );
        countOfx->setMaximum( 100 );

        xIs = new QLabel( "x = " );
        xVariables = new QSpinBox( this );

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
    connect( expressionInput, &QLineEdit::textChanged, this, &FunctionLayout::onInputTextChanged );

    solve = new QPushButton( "Решить", this );
    solve->setEnabled( false );
    connect( solve, &QPushButton::clicked, this, &FunctionLayout::onSolveButtonClicked );

    QPushButton* clear = new QPushButton( "Очистить", this );
    connect( clear, &QPushButton::clicked, this, &FunctionLayout::clearTable );

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
    scrollLayout->addWidget( countOfxLabel, 3, 0 );
    scrollLayout->addWidget( countOfx, 3, 1 );
    scrollLayout->addWidget( xIs, 4, 0 );
    scrollLayout->addWidget( setX, 4, 1 );
    scrollLayout->addWidget( minLabel, 5, 0 );
    scrollLayout->addWidget( min, 5, 1 );
    scrollLayout->addWidget( maxLabel, 6, 0 );
    scrollLayout->addWidget( max, 6, 1 );
    scrollLayout->addWidget( stepLabel, 7, 0 );
    scrollLayout->addWidget( step, 7, 1 );
    scrollLayout->addWidget( nodesLabel, 8, 0 );
    scrollLayout->addWidget( nodes, 8, 1 );
    scrollLayout->addWidget( solve, 9, 0 );
    scrollLayout->addWidget( clear, 9, 1 );
    scrollLayout->addWidget( tableWidget, 10, 0, Qt::AlignCenter );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    hideFirstLayer();

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    connect( typeOfVariableInput, QOverload<int>::of( &QComboBox::currentIndexChanged ), this, &FunctionLayout::switchLayers );
    connect( setX, &QPushButton::clicked, this, &FunctionLayout::showXDataSetupWindow );
}

void FunctionLayout::showTable(const std::vector<double> x, const std::vector<double> y)
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

void FunctionLayout::setRange()
{
    min->setRange( -100.0, 100.0 );
    min->setSingleStep( 0.1 );
    max->setRange( -100.0, 100.0 );
    max->setSingleStep( 0.1 );
    step->setRange( 0.01, 10.0 );
    step->setSingleStep( 0.1 );
    nodes->setRange( 0.0, 5000.0 );
}

void FunctionLayout::onValidateStringValid()
{
    solve->setEnabled( true );
}

void FunctionLayout::onValidateStringInvalid()
{
    solve->setEnabled( false );
}

void FunctionLayout::handleParserError(const QString &err)
{
    couldBuildTable = false;
    errLabel->setStyleSheet( "QLabel { color : red; }" );
    errLabel->setText( err + "!" );
}

void FunctionLayout::onInputTextChanged(const QString &text)
{
    validator->validateExpression( text );
}

void FunctionLayout::onSolveButtonClicked()
{
    auto expression = this->expressionInput->text();
    auto min        = this->min->value();
    auto max        = this->max->value();
    auto step       = this->step->value();

    if( X.empty() )
    {
        for( double i = min; i <= max; i += step )
        {
            X.push_back( i );
        }
    }
    parser->setDataX( X );

    std::vector<double> Y = parser->parseExpression( expression.toStdString().c_str() );

    if( couldBuildTable )
    {
        showTable( X, Y );
    }
    couldBuildTable = true;
}

void FunctionLayout::clearTable()
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    errLabel->clear();
}

void FunctionLayout::hideFirstLayer()
{
    X.clear();

    countOfx->show();
    countOfxLabel->show();

    xIs->hide();
    nodes->hide();
    nodesLabel->hide();
    setX->show();
    minLabel->hide();
    min->hide();
    maxLabel->hide();
    max->hide();
    stepLabel->hide();
    step->hide();
}

void FunctionLayout::hideSecondLayer()
{
    X.clear();

    countOfx->hide();
    countOfxLabel->hide();
    xIs->hide();
    setX->hide();
    nodes->hide();
    nodesLabel->hide();

    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    stepLabel->show();
    step->show();
}

void FunctionLayout::hideThirdLayer()
{
    X.clear();

    countOfx->hide();
    countOfxLabel->hide();
    xIs->hide();
    setX->hide();
    stepLabel->hide();
    step->hide();

    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    nodesLabel->show();
    nodes->show();
}

void FunctionLayout::switchLayers(int index)
{
    if( index == 0 )
    {
        hideFirstLayer();
    }
    else if( index == 1 )
    {
        hideSecondLayer();
    }
    else
    {
        hideThirdLayer();
    }
}

void FunctionLayout::showXDataSetupWindow()
{
    QDialog* newXDataSetupWindow = new QDialog( this );
    //QGridLayout* layout = new QGridLayout( newXDataSetupWindow );
    QSpinBox* xData = new QSpinBox();
    QPushButton* set = new QPushButton( "Ввести", newXDataSetupWindow );
    newXDataSetupWindow->setWindowTitle( "Введите x" );
    if( countOfx->value() == 0 )
    {
        set->setDisabled( true );
    }
    spinBoxes.clear();

    int N = countOfx->value();

    for( int i = 0; i < N; ++i )
    {
        spinBoxes.append( new QSpinBox( xData ) );
        spinBoxes.at( i )->setRange( -100.0, 100.0 );
    }

    QWidget* wgt = spinBoxes.first()->parentWidget();
    QGridLayout* layout = new QGridLayout( wgt );
    wgt->setLayout( layout );

    int col = qCeil( static_cast<double>(N) / qCeil(qSqrt(N)));
    int row = qCeil( qSqrt( N ) );
    for( int i = 0; i < N; ++i )
    {
        int rowIdx = i / col;
        int colIdx = i % col;
        layout->addWidget( spinBoxes.at( i ), rowIdx, colIdx );
        connect( spinBoxes.at( i ), QOverload<int>::of( &QSpinBox::valueChanged ), this, &FunctionLayout::updateSpinBoxValues );
    }
    QMetaObject::invokeMethod( this, "spinBoxValuesChanged", Qt::QueuedConnection );
    layout->addWidget( set );
    connect( set, &QPushButton::clicked, this, &FunctionLayout::setEnteredXData );
    newXDataSetupWindow->setLayout( layout );
    newXDataSetupWindow->show();
}

// Для дебага
void FunctionLayout::setEnteredXData()
{
    if( X.empty() ) std::cout << "empty" << std::endl;
    for( const auto& x : X )
    {
        std::cout << x << " ";;
    }
    std::cout << std::endl;
}
