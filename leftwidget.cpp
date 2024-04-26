#include "leftwidget.h"

LeftWidget::LeftWidget( SpecialBuffer& buffer, QWidget *parent ) : QWidget( parent )
{
    initLabels();
    connectLabels( buffer );
    setRange();
    layout = new QGridLayout( this );
    initLayout();
    hideFirstLayer( false );
}

void LeftWidget::showTable( const std::vector<double> x, const std::vector<double> y, const std::vector<double> dY )
{
    tableWidget->clear();
    tableWidget->setRowCount( x.size() );
    QStringList labels;
    // TODO: Избавиться от данного повтора кода!
    labels << "X" << "Y";
    if( !dY.empty() )
    {
        labels << "Y'";
    }
    tableWidget->setHorizontalHeaderLabels( labels );

    for( std::size_t i{}; i < x.size(); ++i )
    {
        QTableWidgetItem* itemX = new QTableWidgetItem( QString::number( x[i] ) );
        QTableWidgetItem* itemY = new QTableWidgetItem( QString::number( y[i] ) );
        tableWidget->setItem( i, 0, itemX );
        tableWidget->setItem( i, 1, itemY );

        if( !dY.empty() )
        {
            QTableWidgetItem* itemDY = new QTableWidgetItem( QString::number( dY[i] ) );
            tableWidget->setItem( i, 2, itemDY );
        }
    }
    buildGraph->setEnabled( true );
}

void LeftWidget::setRange( void )
{
    min->setRange( -100.0, 100.0 );
    min->setSingleStep( 0.1 );
    max->setRange( -100.0, 100.0 );
    max->setSingleStep( 0.1 );
    step->setRange( 0.01, 10.0 );
    step->setSingleStep( 0.1 );
    nodes->setRange( 0.0, 1000.0 );
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
    if( derivativeLabelActive &&
        ( derivativeExpressionInput->text().isEmpty() ||
          expressionInput->text().isEmpty() )
    )
    {
        emit handleParserError( "Заполните все поля" );
        return;
    }

    clearDataTable();

    auto expression = this->expressionInput->text();
    auto min        = this->min->value();
    auto max        = this->max->value();
    auto step       = this->step->value();

    // TODO: Переместить реализацию в MathUtils
    if( !nodes->isVisible() && manualInput == false )
    {
        for( double i = min; i <= max; i += step )
        {
            X.push_back( i );
        }
        parser->setDataX( X );
        Y = parser->parseExpression( expression.toStdString().c_str() );
    }
    else if( nodes->isVisible() && manualInput == false )
    {
        setupNodes( nodes->value() );
        parser->setDataX( X );
        Y = parser->parseExpression( expression.toStdString().c_str() );
    }
    else if( manualInput )
    {
        X = fillDataFromTable( 0 );
        Y = fillDataFromTable( 1 );
    }

    if( X.size() > limits::SIZE_LIMIT )
    {
        emit handleParserError( "Предел: 1000 узлов" );
        return;
    }

    buffer.x = QVector<double>( X.begin(), X.end() );
    buffer.y = QVector<double>( Y.begin(), Y.end() );
    if( derivativeLabelActive )
    {
        dY = parser->parseExpression( derivativeExpressionInput->text().toStdString().c_str() );
        buffer.dy = QVector<double>( dY.begin(), dY.end() );
    }

    if( couldBuildTable )
    {
        showTable( X, Y, dY );
    }
    couldBuildTable = true;
    X.clear();
    Y.clear();
    dY.clear();
}

void LeftWidget::onSolveEquationButtonClicked()
{
    // TODO: в отдельный метод
    for( int row{}; row < equationsTableWidget->rowCount(); ++row )
    {
        QTableWidgetItem* firstColumnItem = equationsTableWidget->item( row, 0 );
        QTableWidgetItem* secondColumnItem = equationsTableWidget->item( row, 1 );

        if( firstColumnItem == nullptr || secondColumnItem == nullptr )
        {
            qDebug() << "There is some blank labels\n";
            continue;
        }

        QString firstCol = firstColumnItem->text();
        QString secondCol = secondColumnItem->text();

        if( !ExpressionValidator::validateTableRow( firstCol, secondCol ) )
        {
            qDebug() << "ERROR OF TYPING\n";
            return;
        }
    }

    auto data = MathUtils::formTheSystemOfEquations( *equationsTableWidget );
    emit readyToSendLinearEquationsData( data );
}

void LeftWidget::clearDataTable()
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    equationsTableWidget->clearContents();
    errLabel->clear();
    manualInput = false;
    X.clear();
    Y.clear();
    dY.clear();
    buildGraph->setEnabled( false );
}

void LeftWidget::handleClearGraph( RightWidget &right )
{
    right.clearGraph();
}

void LeftWidget::hideFirstLayer( bool isDerivativeMenu )
{
    X.clear();

    nodes->hide();
    nodesLabel->hide();
    error->hide();
    calculatedArea->hide();
    area->hide();
    if( isDerivativeMenu == false )
    {
        derivativeLabel->hide();
        derivativeExpressionInput->hide();
    }
    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    stepLabel->show();
    step->show();
}

void LeftWidget::hideSecondLayer( bool isDerivativeMenu )
{
    X.clear();

    stepLabel->hide();
    step->hide();
    error->hide();
    calculatedArea->hide();
    area->hide();
    if( isDerivativeMenu == false )
    {
        derivativeLabel->hide();
        derivativeExpressionInput->hide();
    }
    minLabel->show();
    min->show();
    maxLabel->show();
    max->show();
    nodesLabel->show();
    nodes->show();
}

void LeftWidget::changeLayer( int index )
{
    switchLayers( index, false );
}

void LeftWidget::setupNodes( const double node )
{
    X.clear();
    MathUtils::setupNodes( X, node, this->min->value(), this->max->value() );
}

std::vector<double> LeftWidget::fillDataFromTable( int column )
{
    std::vector<double> data;
    for( int row{}; row < tableWidget->rowCount(); ++row )
    {
        QTableWidgetItem* item = tableWidget->item( row, column );
        if( item != nullptr )
        {
            bool ok;
            double value = item->text().toDouble( &ok );
            if( ok )
            {
                data.push_back( value );
            }
            else
            {
                emit handleParserError( QString::asprintf( "Некорректное значение в таблице. Строка: %d", row+1 ) );
            }
        }
        else
        {
            emit handleParserError( QString::asprintf( "Пустая ячейка в строке: %d", row+1 ) );
        }
    }
    return data;
}

void LeftWidget::initLayout()
{
    layout->addWidget( label, 0, 0 );
    layout->addWidget( expressionInput, 0, 1, 1, 10 );
    layout->addWidget( derivativeLabel, layout->rowCount() - layout->rowCount() + 1, 0 );
    layout->addWidget( derivativeExpressionInput, layout->rowCount() - layout->rowCount() + 1, 1, 1, 10 );
    layout->addWidget( errLabel, 2, 0 );
    layout->addWidget( typeOfInput, 3, 0 );
    layout->addWidget( typeOfVariableInput, 3, 1 );
    layout->addWidget( minLabel, 4, 0 );
    layout->addWidget( min, 4, 1 );
    layout->addWidget( maxLabel, 5, 0 );
    layout->addWidget( max, 5, 1 );
    layout->addWidget( stepLabel, 6, 0 );
    layout->addWidget( step, 6, 1 );
    layout->addWidget( nodesLabel, 7, 0 );
    layout->addWidget( nodes, 7, 1 );
    layout->addWidget( solve, 8, 0 );
    layout->addWidget( clearTable, 8, 1 );
    layout->addWidget( buildGraph, 9, 0 );
    layout->addWidget( manualTableInput, 9, 1 );
    layout->addWidget( tableWidget, 10, 0, 1, 2 );
    layout->addWidget( averError, layout->rowCount(), 0 );
    layout->addWidget( error = new QLineEdit( this ), layout->rowCount() - 1, 1 );
    layout->addWidget( calculatedArea = new QLabel( "Вычисленная площадь: ", this ), layout->rowCount(), 0 );
    layout->addWidget( area = new QLineEdit( this ), layout->rowCount() - 1, 1 );

    layout->setColumnStretch( 1, 10 );
    layout->setColumnStretch( 0, 2 );
}

void LeftWidget::buildWidgetForDerivativeOperations( SpecialBuffer& buffer )
{
    equationOpened = false;
    hideAll();
    deleteAll();
    initLabels();
    connectLabels( buffer );
    setRange();
    initLayout();
    hideFirstLayer( true );

    derivativeLabel->setText( "f'(x) = " );

    int currentColumnCount = tableWidget->columnCount();
    tableWidget->setColumnCount( currentColumnCount + 1 );
    auto item = new QTableWidgetItem( "Y'" );
    tableWidget->setHorizontalHeaderItem( currentColumnCount, item );

    averError->setText( "Средняя погрешность: " );
    averError->show();
    error->show();
}

void LeftWidget::buildWidgetForIntegrationOperations( SpecialBuffer &buffer )
{
    equationOpened = false;
    hideAll();
    deleteAll();
    initLabels();
    connectLabels( buffer );
    setRange();
    initLayout();
    hideFirstLayer( false );

    calculatedArea->show();
    area->show();
    buildGraph->setText( "Вычислить площадь" );
}

void LeftWidget::buildWidgetForEquationOperations( SpecialBuffer& buffer )
{
    if( equationOpened )
    {
        return;
    }
    equationOpened = true;
    hideAll();
    deleteAll();

    oddsInputLabel->setText( QString::asprintf( "Введите через пробел \nкоэффициенты уравнений" ) );
    QStringList labels;
    labels << "C1 C2 ... Cn" << "X0";
    equationsTableWidget->setColumnCount( 2 );
    equationsTableWidget->setRowCount( 10 );
    for( int row{}; row < equationsTableWidget->rowCount(); ++row )
    {
        QRadioButton* button = new QRadioButton;
        equationsTableWidget->setCellWidget( row, 2, button );
    }
    equationsTableWidget->setHorizontalHeaderLabels( labels );
    solveEquations->setText( "Решить" );
    clearEquationsTable->setText( "Очистить Таблицу" );
    resultOfEquations->setText( "Результат вычислений: " );
    resultDescription->setText( "Описание: " );

    layout->addWidget( oddsInputLabel, 0, 0 );
    layout->addWidget( equationsTableWidget, 1, 0, 1, 2 );
    layout->addWidget( solveEquations, 2, 0 );
    layout->addWidget( clearEquationsTable, 2, 1 );
    layout->addWidget( resultOfEquations, 3, 0 );
    layout->addWidget( eqResult, 4, 0 );
    layout->addWidget( resultDescription, 5, 0 );
    layout->addWidget( description, 6, 0 );

    connect( solveEquations, &QPushButton::clicked, this, &LeftWidget::onSolveEquationButtonClicked );
    connect( clearEquationsTable, &QPushButton::clicked, this, &LeftWidget::clearDataTable );
}

void LeftWidget::setWidgetToDefaultStatement( SpecialBuffer& buffer )
{
    equationOpened = false;
    hideAll();
    deleteAll();
    initLabels();
    connectLabels( buffer );
    setRange();
    initLayout();
    hideFirstLayer( false );
}

void LeftWidget::hideAll( void )
{
    for( int i{}; i < layout->count(); ++i )
    {
        QLayoutItem* item = layout->itemAt( i );
        if( item && item->widget() )
        {
            item->widget()->hide();
        }
    }
}

void LeftWidget::deleteAll( void )
{
    if( layout->count() > 0 )
    {
        QLayoutItem* item;
        while( ( item = layout->takeAt( 0 ) ) != nullptr )
        {
            layout->removeItem( item );
            delete item;
        }
    }
}

void LeftWidget::switchLayers( int index, bool isDerivativeMenu )
{
    if( index == 0 )
    {
        hideFirstLayer( isDerivativeMenu );
    }
    else if( index == 1 )
    {
        hideSecondLayer( isDerivativeMenu );
    }
}

void LeftWidget::editTable()
{
    clearDataTable();
    tableWidget->setColumnCount( 2 );
    tableWidget->setRowCount( 10 );
    for( int row{}; row < tableWidget->rowCount(); ++row )
    {
        QRadioButton* button = new QRadioButton;
        tableWidget->setCellWidget( row, 2, button );
    }
    manualInput = true;
    solve->setEnabled( true );
    solve->setStyleSheet( "background-color: lightgreen;" );
    buildGraph->setEnabled( true );
}

void LeftWidget::updateDataFromTable( SpecialBuffer& buffer )
{
    X.clear();
    Y.clear();
    dY.clear();
    for( int row{}; row < tableWidget->rowCount(); ++row )
    {
        QTableWidgetItem* itemX = tableWidget->item( row, 0 );
        QTableWidgetItem* itemY = tableWidget->item( row, 1 );

        if( itemX && itemY )
        {
            X.push_back( itemX->text().toDouble() );
            Y.push_back( itemY->text().toDouble() );
        }
    }
    buffer.x = QVector<double>( X.begin(), X.end() );
    buffer.y = QVector<double>( Y.begin(), Y.end() );
}

// МЕТОД ДЛЯ ОТРИСОВКИ ГРАФИКА ПО ДИСКРЕТНО ЗАДАННЫМ ВЕЛИЧИНАМ
void LeftWidget::acceptData( const QString &expr, const double a, const double b )
{
    auto x = MathUtils::multipyPoints( a, b );
    parser->setDataX( x );
    std::vector<double> y = parser->parseExpression( expr.toStdString().c_str() );
    emit readyToDraw( x, y );
}

void LeftWidget::acceptArea( std::string& area )
{
    this->area->setText( QString::fromStdString( area ) );
}

void LeftWidget::rebuildWidgets( pymodules::Modules modules, SpecialBuffer& buffer )
{
    switch( modules )
    {
    case pymodules::Modules::DIFFERENTIATION:
        derivativeLabelActive = true;
        buildWidgetForDerivativeOperations( buffer );
        break;
    case pymodules::Modules::INTEGRATION:
        derivativeLabelActive = false;
        buildWidgetForIntegrationOperations( buffer );
        break;
    case pymodules::Modules::EQUATIONS:
        derivativeLabelActive = false;
        buildWidgetForEquationOperations( buffer );
        break;
    case pymodules::Modules::NIL:
        derivativeLabelActive = false;
        setWidgetToDefaultStatement( buffer );
        break;
    default:
        break;
    };
}

QLineEdit* LeftWidget::getExpressionInput() const
{
    return expressionInput;
}

void LeftWidget::initLabels( void )
{
    validator = new ValidateString( this );

    parser = new StringParser( this );

    label = new QLabel( "f(x) = ", this );
    errLabel = new QLabel( "", this );

    typeOfInput = new QLabel( "Ввод значений x: ", this );

    typeOfVariableInput = new QComboBox( this );
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

        derivativeLabel = new QLabel();
        averError = new QLabel();

        oddsInputLabel = new QLabel();
        equationsTableWidget = new QTableWidget();
        solveEquations = new QPushButton();
        clearEquationsTable = new QPushButton();
        resultOfEquations = new QLabel();
        eqResult = new QLineEdit();
        resultDescription = new QLabel();
        description = new QLineEdit();
    } // Переменные элементы

    derivativeExpressionInput = new QLineEdit( this );
    expressionInput = new QLineEdit( this );

    manualTableInput = new QPushButton( "Ручной ввод", this );
    solve = new QPushButton( "Решить", this );
    solve->setStyleSheet( "background-color: tomato;" );
    solve->setEnabled( false );

    clearTable = new QPushButton( "Очистить таблицу", this );
    buildGraph = new QPushButton( "Построить график", this );
    buildGraph->setEnabled( false );

    tableWidget = new QTableWidget( this );
    tableWidget->setColumnCount( 2 );
    QStringList labels;
    labels << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels( labels );
}

void LeftWidget::connectLabels( SpecialBuffer &buffer )
{
    connect( validator, &ValidateString::validExpression, this, &LeftWidget::onValidateStringValid );
    connect( validator, &ValidateString::invalidExpression, this, &LeftWidget::onValidateStringInvalid );
    connect( parser, &StringParser::errorOccurred, this, &LeftWidget::handleParserError );
    connect( expressionInput, &QLineEdit::textChanged, this, &LeftWidget::onInputTextChanged );
    connect( derivativeExpressionInput, &QLineEdit::textChanged, this, &LeftWidget::onInputTextChanged );
    connect( manualTableInput, &QPushButton::clicked, this, &LeftWidget::editTable );
    connect( solve, &QPushButton::clicked, [ &buffer, this ]()
            {
                onSolveButtonClicked( buffer );
            }
    );
    connect( clearTable, &QPushButton::clicked, this, &LeftWidget::clearDataTable );
    connect( tableWidget, &QTableWidget::itemChanged, this, [ &buffer, this ]()
            {
                updateDataFromTable( buffer );
            }
    );
    connect( typeOfVariableInput, QOverload<int>::of( &QComboBox::currentIndexChanged ), this, &LeftWidget::changeLayer );
}
