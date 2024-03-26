#include "mainwindow.h"

// TODO: Сделать код чище
//       Подумать над неймингом объектов.
//       Сделать вертикальное меню
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    setFixedSize( 500, 300 );
    setWindowTitle( "Graphika" );

    toolbar = new Toolbar( this );
    addToolBar( toolbar );

    layout = new QGridLayout( this );
    centralwidget = new QWidget( this );

    centralwidget->setLayout( layout );
    setCentralWidget( centralwidget );

    connect( toolbar->actions().at( 0 ), &QAction::triggered, this, &MainWindow::openFunctionMenuWidget );
    connect( toolbar->actions().at( 1 ), &QAction::triggered, this, &MainWindow::openDerivativeMenuWidget );
    connect( toolbar->actions().at( 2 ), &QAction::triggered, this, &MainWindow::openPolynomialMenuWidget );
    connect( toolbar->actions().at( 3 ), &QAction::triggered, this, &MainWindow::openGraphMenuWidget );
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

void MainWindow::setRange()
{
    min->setRange( -100.0, 100.0 );
    min->setSingleStep( 0.1 );
    max->setRange( -100.0, 100.0 );
    max->setSingleStep( 0.1 );
    step->setRange( 0.01, 10.0 );
    step->setSingleStep( 0.1 );
}

void MainWindow::onSolveButtonClicked( void )
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

void MainWindow::clearTable( void )
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    errLabel->clear();
}

void MainWindow::handleParserError( const QString& err )
{
    couldBuildTable = false;
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

void MainWindow::hideFirstLayer()
{
    X.clear();

    countOfx->show();
    countOfxLabel->show();

    xIs->hide();
    setX->show();
    minLabel->hide();
    min->hide();
    maxLabel->hide();
    max->hide();
    stepLabel->hide();
    step->hide();
}

void MainWindow::hideSecondLayer()
{
    X.clear();

    countOfx->hide();
    countOfxLabel->hide();
    xIs->hide();

    setX->hide();
    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    stepLabel->show();
    step->show();
}

void MainWindow::clearLayout( QLayout *layout )
{
    if ( layout == NULL )
    {
        return;
    }
    QLayoutItem *item;
    while( ( item = layout->takeAt( 0 ) ) )
    {
        if ( item->layout() )
        {
            clearLayout( item->layout() );
            delete item->layout();
        }
        if ( item->widget() )
        {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::openFunctionMenuWidget()
{
    clearLayout( layout );

    validator = new ValidateString( this );
    connect( validator, &ValidateString::validExpression, this, &MainWindow::onValidateStringValid );
    connect( validator, &ValidateString::invalidExpression, this, &MainWindow::onValidateStringInvalid );
    parser = new StringParser( this );

    QLabel* label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );

    connect( parser, &StringParser::errorOccurred, this, &MainWindow::handleParserError );

    QLabel* typeOfInput = new QLabel( "Ввод значений x: ", this );

    QComboBox* typeOfVariableInput = new QComboBox( this );
    typeOfVariableInput->addItems( { "вручную", "автоматически" } );

    { // Переменные элементы
        countOfxLabel = new QLabel( "Число точек x = ", this );
        countOfx = new QSpinBox( this );
        setX = new QPushButton( "Ввести x", this );

        countOfx->setSingleStep( 1 );
        countOfx->setMinimum( 0 );
        countOfx->setMaximum( 10 );

        xIs = new QLabel( "x = " );
        xVariables = new QSpinBox( this );

        minLabel = new QLabel( "Минимальное значение x:", this );
        maxLabel = new QLabel( "Максимальное значение x:", this );
        stepLabel = new QLabel( "Шаг по x:", this );

        min = new QDoubleSpinBox( this );
        max = new QDoubleSpinBox( this );
        step = new QDoubleSpinBox( this );
    } // Переменные элементы

    expressionInput = new QLineEdit( this );
    connect( expressionInput, &QLineEdit::textChanged, this, &MainWindow::onInputTextChanged );

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

    setRange();
    setFixedSize( 500, 300 );

    QScrollArea *scrollArea = new QScrollArea( this );

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
    scrollLayout->addWidget( solve, 8, 0 );
    scrollLayout->addWidget( clear, 8, 1 );
    scrollLayout->addWidget( tableWidget, 9, 0, Qt::AlignCenter );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    hideFirstLayer();

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    connect( typeOfVariableInput, QOverload<int>::of( &QComboBox::currentIndexChanged ), this, &MainWindow::switchLayers );
    connect( setX, &QPushButton::clicked, this, &MainWindow::showXDataSetupWindow );

    centralwidget->setLayout( layout );
    setCentralWidget( centralwidget );
}

void MainWindow::openDerivativeMenuWidget()
{
    clearLayout( layout );
    QLabel* soon = new QLabel( "скоро", this );
    layout->addWidget( soon, 0, 0 );
}

void MainWindow::openPolynomialMenuWidget()
{
    clearLayout( layout );
    QLabel* soon = new QLabel( "скоро", this );
    layout->addWidget( soon, 0, 0 );
}

void MainWindow::openGraphMenuWidget()
{
    clearLayout( layout );
    QLabel* soon = new QLabel( "скоро", this );
    layout->addWidget( soon, 0, 0 );
}

void MainWindow::switchLayers( int index )
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

void MainWindow::showXDataSetupWindow()
{
    QDialog* newXDataSetupWindow = new QDialog( this );
    QGridLayout* layout = new QGridLayout( newXDataSetupWindow );
    QSpinBox* xData = new QSpinBox();
    QPushButton* set = new QPushButton( "Ввести", newXDataSetupWindow );
    newXDataSetupWindow->setWindowTitle( "Введите x" );
    newXDataSetupWindow->setFixedSize( 250, 250 );
    if( countOfx->value() == 0 )
    {
        set->setDisabled( true );
    }
    spinBoxes.clear();
    for( int i = 1; i <= countOfx->value(); ++i )
    {
        spinBoxes.append( new QSpinBox( xData ) );
        spinBoxes.at( i - 1 )->setRange( -100.0, 100.0 );
        layout->addWidget( spinBoxes.at( i - 1 ) );
        connect( spinBoxes.at( i - 1 ), QOverload<int>::of( &QSpinBox::valueChanged ), this, &MainWindow::updateSpinBoxValues );
    }
    QMetaObject::invokeMethod( this, "spinBoxValuesChanged", Qt::QueuedConnection );
    layout->addWidget( set );
    connect( set, &QPushButton::clicked, this, &MainWindow::setEnteredXData );
    newXDataSetupWindow->setLayout( layout );
    newXDataSetupWindow->show();
}

// Для дебага - потом убрать можно
void MainWindow::setEnteredXData()
{
    if( X.empty() ) std::cout << "empty" << std::endl;
    for( const auto& x : X )
    {
        std::cout << x << " ";;
    }
    std::cout << std::endl;
}
