#include_next "rightwidget.h"
#include <qstring.h>
#include <filesystem>

void RightWidget::buildWidgetForDerivativeOperations( void )
{
    graphBuilder->on_clearButton_clicked();
    graphBuilder->wGraphic->yAxis->setLabel( "y'" );
}

RightWidget::RightWidget( QWidget *parent )
    : QWidget{ parent }
{
    graphBuilder = new GraphBuilder( this );
    conveyor = new PythonConveyor();
    rightLayout = new QGridLayout( this );
    modelLabel = new QLabel( "Полученная модель: ", this );
    model = new QLineEdit( this );
    rightLayout->addWidget( modelLabel );
    rightLayout->addWidget( model );
    rightLayout->addWidget( graphBuilder );

}

void RightWidget::printGraph( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack )
{
    x = buffer.x;
    y = buffer.y;

    if( graphBuilder->wGraphic->yAxis->label() == "y'" )
    {
        graphBuilder->on_clearButton_clicked();
        graphBuilder->wGraphic->yAxis->setLabel( "y" );
    }
    graphBuilder->wGraphic->replot();
    // TODO: исправить заглушку
    graphBuilder->PaintG( x, y, sender.functionName == nullptr ? "График заданной функции" : sender.functionName, true, false );

    QString str = QString::fromUtf8( resultModel.c_str() );
    model->setText( str );

    if( stack )
    {
       // emit sendData( *model, false );
       // emit sendData( *graphBuilder->wGraphic, false );
    }
}

void RightWidget::printFunctionGraph( std::vector<double>& x, std::vector<double>& y )
{
    if( graphBuilder->wGraphic->yAxis->label() == "y'" )
    {
        graphBuilder->on_clearButton_clicked();
        graphBuilder->wGraphic->yAxis->setLabel( "y" );
    }
    graphBuilder->wGraphic->replot();
    // TODO: исправить заглушку
    auto placeholder = QVector<double>::fromStdVector( x );
    auto placeholder1 = QVector<double>::fromStdVector( y );
    graphBuilder->PaintG( placeholder, placeholder1, "График заданной функции", true, false );
}

void RightWidget::printDerivationGraph( const QVector<double>& x, const QVector<double>& y, Sender& sender, const CompositeStateStack* stack  )
{
    graphBuilder->wGraphic->replot();
    // TODO: исправить заглушку
    graphBuilder->PaintG( x, y, "График производной функции", true, false );

    if( stack )
    {
       // emit sendData( *graphBuilder->wGraphic, false );
    }
}


void RightWidget::printDiffGraph( SpecialBuffer &buffer, Sender &sender, const CompositeStateStack* stack )
{
    x = buffer.x;
    y = buffer.y;

    buildWidgetForDerivativeOperations();
    graphBuilder->wGraphic->replot();

    differentiationSolve( x, y, sender );

    if( stack )
    {
       // emit sendData( *graphBuilder->wGraphic, false );
    }
}

void RightWidget::calculateIntegral( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack )
{
    x = buffer.x;
    y = buffer.y;

    integrationSolve( x, y, sender );

    if( stack )
    {
       // emit sendData( x.data(), false );
       // emit sendData( y.data(), false );
    }
}

void RightWidget::buildPolynome( SpecialBuffer &buffer, Sender &sender, const CompositeStateStack* stack  )
{
    x = buffer.x;
    y = buffer.y;

    if( x.size() > limits::NODES_LIMIT )
    {
        emit errorOccured( "Не больше 10 узлов" );
        return;
    }
    if( x.back() < x.first() )
    {
        emit errorOccured( "Введите значения x по возрастанию" );
        return;
    }
    // TODO: В отдельный метод
    if( graphBuilder->wGraphic->yAxis->label() == "y'" )
    {
        graphBuilder->on_clearButton_clicked();
        graphBuilder->wGraphic->yAxis->setLabel( "y" );
    }

    graphBuilder->wGraphic->replot();
    graphBuilder->PaintG( x, y, "Точки интерполяции", false, true );
    interpolationSolve( x.toStdVector(), y.toStdVector(), sender );
    QString str = QString::fromUtf8( resultModel.c_str() );
    model->setText( str );
    emit readyToSendData( model->text(), x[0], x.back() );

    if( stack )
    {
       // emit sendData( *model, false );
       // emit sendData( *graphBuilder->wGraphic, false );
    }
}

void RightWidget::interpolationSolve( const std::vector<double> &x, const std::vector<double> &y, Sender& sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );
    conveyor->setData( &PythonConveyor::xVector, x );
    conveyor->setData (&PythonConveyor::yVector, y );


    conveyor->sendArraysToPythonFunction();
    QString str = conveyor->getData( &PythonConveyor::resultString );
    resultModel = str.toStdString();
}

void RightWidget::integrationSolve( const QVector<double>& x, const QVector<double>& y, Sender &sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );

    conveyor->setData( &PythonConveyor::xVector, x.toStdVector() );
    conveyor->setData( &PythonConveyor::yVector, y.toStdVector() );

    conveyor->sendDataToIntegration();
    QString resultStr = conveyor->getData( &PythonConveyor::resultString );
    area = resultStr.toStdString();
    emit readyToSendArea( area );
}

void RightWidget::differentiationSolve( const QVector<double>& x, const QVector<double>& y, Sender& sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );

    conveyor->setData( &PythonConveyor::xVector, x.toStdVector() );
    conveyor->setData( &PythonConveyor::yVector, y.toStdVector() );

    conveyor->sendDataToDifferentiation();
    QVector<double> resultX = conveyor->getData( &PythonConveyor::resultDiff_XVector );
    QVector<double> resultY = conveyor->getData( &PythonConveyor::resultDiff_YVector );
    printDerivationGraph( resultX, resultY, sender, nullptr );
}

void RightWidget::sysSolve( QVector<QVector<double>>& data, Sender &sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );

    conveyor->setData( &PythonConveyor::sys, data );

    conveyor->sendDataToSolveSys();
    QVector<double> resultSysVector = conveyor->getData( &PythonConveyor::resultSys_Vector );
    QString resultSysStr = conveyor->getData( &PythonConveyor::resultString );
    emit readyToSendSysResult( resultSysStr );
    qDebug() << resultSysStr;
}

void RightWidget::clearGraph( void )
{
    graphBuilder->on_clearButton_clicked();
}

void RightWidget::drawInterpolationGraph( const std::vector<double> x, const std::vector<double> y )
{
    QVector<double> X = QVector<double>::fromStdVector( x );
    QVector<double> Y = QVector<double>::fromStdVector( y );
    graphBuilder->PaintG( X, Y, "График интерполяции", true, false );
}

void RightWidget::moveLegend(void)
{
    graphBuilder->moveLegend();
}

void RightWidget::showLegend()
{
    graphBuilder->showLegend();
}

void RightWidget::hideLegend()
{
    graphBuilder->hideLegend();
}

void RightWidget::stepBack()
{
    graphBuilder->GoBack();
}

void RightWidget::stepForward()
{
    graphBuilder->GoFront();
}

void RightWidget::zoomIn()
{
    graphBuilder->zoomIn();
}

void RightWidget::zoomOut()
{
    graphBuilder->zoomOut();
}

void RightWidget::savePlotAsImage()
{
    graphBuilder->savePlotAsImage();
}

void RightWidget::rebuildWidgets( pymodules::Modules modules )
{
    switch( modules )
    {
    case pymodules::Modules::DIFFERENTIATION:
        buildWidgetForDerivativeOperations();
        break;
    };
}
