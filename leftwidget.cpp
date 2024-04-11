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

    manualTableInput = new QPushButton( "Ручной ввод", this );
    connect( manualTableInput, &QPushButton::clicked, this, &LeftWidget::editTable );
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
    connect( tableWidget, &QTableWidget::itemChanged, this, [ this, &buffer ]()
        {
            updateDataFromTable( buffer );
        }
    );

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
    layout->addWidget( manualTableInput, 8, 1 );
    layout->addWidget( tableWidget, 9, 0, Qt::AlignCenter );
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
    clearTable();

    auto expression = this->expressionInput->text();
    auto min        = this->min->value();
    auto max        = this->max->value();
    auto step       = this->step->value();

    // TODO: Это отдельный метод и подумать над реализацией
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

    buffer.x = QVector<double>( X.begin(), X.end() );
    buffer.y = QVector<double>( Y.begin(), Y.end() );
    buffer.print();

    if( couldBuildTable )
    {
        showTable( X, Y );
    }
    couldBuildTable = true;
    X.clear();
    Y.clear();
}

void LeftWidget::clearTable()
{
    tableWidget->clearContents();
    tableWidget->setRowCount( 0 );
    errLabel->clear();
    manualInput = false;
    X.clear();
    Y.clear();
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

void LeftWidget::editTable()
{
    clearTable();
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
}

void LeftWidget::updateDataFromTable( SpecialBuffer& buffer )
{
    X.clear();
    Y.clear();
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
    buffer.print();
}

// МЕТОД ДЛЯ ОТРИСОВКИ ГРАФИКА ПО ДИСКРЕТНО ЗАДАННЫМ ВЕЛИЧИНАМ
void LeftWidget::acceptData( const QString &expr, const double a, const double b )
{
    std::vector<double> x;
    for( double i = a; i <= b; i += 0.1 )
    {
        x.push_back( i );
    }
    parser->setDataX( x );
    std::vector<double> y = parser->parseExpression( expr.toStdString().c_str() );
    emit readyToDraw( x, y );
}

QLineEdit* LeftWidget::getExpressionInput() const {
    return expressionInput;
}
