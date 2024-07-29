#include "rightwidget.h"
#include <qstring.h>
#include <filesystem>
#include <QString>
#include <QVariant>

void RightWidget::buildWidgetForDerivativeOperations( void )
{
    graphBuilder->onClearButtonClicked();
    graphBuilder->graph2d->yAxis->setLabel( "y'" );
}

RightWidget::RightWidget( QWidget *parent )
    : QWidget{ parent }
{
    graphBar = new GraphBar( this );
    graphBuilder = new GraphBuilder( this );
    conveyor = new PythonConveyor();
    rightLayout = new QGridLayout( this );
    //modelLabel = new QLabel( "Полученная модель: ", this );
    //model = new QLineEdit( this );

    connect( graphBar->actions().at( 0 ), &QAction::triggered, this, &RightWidget::clearGraph            );
    connect( graphBar->actions().at( 1 ), &QAction::triggered, this, &RightWidget::resetZoom             );
    connect( graphBar->actions().at( 2 ), &QAction::triggered, this, &RightWidget::moveLegend            );
    connect( graphBar->actions().at( 3 ), &QAction::triggered, this, &RightWidget::showLegend            );
    connect( graphBar->actions().at( 4 ), &QAction::triggered, this, &RightWidget::stepBack              );
    connect( graphBar->actions().at( 5 ), &QAction::triggered, this, &RightWidget::stepForward           );
    connect( graphBar->actions().at( 6 ), &QAction::triggered, this, &RightWidget::zoomOut               );
    connect( graphBar->actions().at( 7 ), &QAction::triggered, this, &RightWidget::zoomIn                );
    connect( graphBar->actions().at( 8 ), &QAction::triggered, this, &RightWidget::unpinGraph            );
    connect( graphBar->actions().at( 9 ), &QAction::triggered, this, &RightWidget::savePlotAsImage       );
    connect( graphBuilder, &GraphBuilder::couldSavePlotAsImage, this, &RightWidget::couldSavePlotAsImage );

    connect( graphBuilder, &GraphBuilder::hideBarButtons, this, &RightWidget::hideBarButtons );

    rightLayout->addWidget( graphBar );
    rightLayout->addWidget( graphBuilder );
    currentLegend = "График заданной функции";
    functionText = "График заданной функции";
}

void RightWidget::updateLegend( const QString& legendText )
{
    currentLegend = legendText;
    qDebug() << "Легенда обновлена на:" << currentLegend;
}

void RightWidget::setFunctionText(const QString& text) {
    functionText = text;
}

void RightWidget::hideBarButtons( const bool& hide )
{
    // idgtf how to do it differently
    graphBar->actions().at( 1 )->setDisabled( hide );
    graphBar->actions().at( 2 )->setDisabled( hide );
    graphBar->actions().at( 3 )->setDisabled( hide );
    graphBar->actions().at( 6 )->setDisabled( hide );
    graphBar->actions().at( 7 )->setDisabled( hide );
    graphBar->actions().at( 9 )->setDisabled( hide );
}

void RightWidget::printGraph( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack )
{
    x = buffer.x;
    y = buffer.y;
    z = buffer.z;

    checkoutAxeses();

    graphBuilder->graph2d->replot();
    graphBuilder->PaintG( x, y, functionText, true, false, false, z );

    if( stack ) [[unlikely]]
    {
//        emit sendData( model, false );
//        emit sendData( *graphBuilder->graph2d, false );
    }
}

void RightWidget::printDerivationGraph( const QVector<double>& x, const QVector<double>& y, Sender& sender, const CompositeStateStack* stack  )
{
    graphBuilder->graph2d->replot();
    // TODO: исправить заглушку
    graphBuilder->PaintG( x, y, "График производной функции " + functionText + " (" + currentLegend + ")", true, false, false );

    if( stack ) [[unlikely]]
    {
//        emit sendData( *graphBuilder->graph2d, false );
    }
}


void RightWidget::printDiffGraph( SpecialBuffer &buffer, Sender &sender, const CompositeStateStack* stack )
{
    x = buffer.x;
    y = buffer.y;

    buildWidgetForDerivativeOperations();
    graphBuilder->graph2d->replot();

    differentiationSolve( x, y, sender );

    if( stack ) [[unlikely]]
    {
//        emit sendData( *graphBuilder->graph2d, false );
    }
}

void RightWidget::calculateIntegral( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack )
{
    x = buffer.x;
    y = buffer.y;

    checkoutAxeses();

    integrationSolve( x, y, sender );
    graphBuilder->graph2d->replot();
    graphBuilder->PaintG( x, y, "Площадь функции " + functionText  + " (" + currentLegend + ")", true, false, true );

    if( stack ) [[unlikely]]
    {
//        emit sendData( *new QLineEdit( area.c_str() ), false );
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

    checkoutAxeses();

    graphBuilder->graph2d->replot();
    graphBuilder->PaintG( x, y, "Точки интерполяции", false, true, false );
    std::vector<double> _x(std::begin(x), std::end(x));
    std::vector<double> _y(std::begin(y), std::end(y));
    interpolationSolve( _x, _y, sender );
  
    QString str = QString::fromUtf8( resultModel.c_str() );
    emit readyToSendData( str, x[0], x.back() );

    if( stack ) [[unlikely]]
    {
//        emit sendData( *model, false );
//        emit sendData( *graphBuilder->graph2d, false );
    }
}

void RightWidget::interpolationSolve( const std::vector<double> &x, const std::vector<double> &y, Sender& sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );
    conveyor->setData( &PythonConveyor::xVector, x );
    conveyor->setData( &PythonConveyor::yVector, y );

    conveyor->sendArraysToPythonFunction();
    QString str = conveyor->getData( &PythonConveyor::resultString );
    resultModel = str.toStdString();
}

void RightWidget::integrationSolve( const QVector<double>& x, const QVector<double>& y, Sender &sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );

    std::vector<double> _x(std::begin(x), std::end(x));
    std::vector<double> _y(std::begin(y), std::end(y));
    conveyor->setData( &PythonConveyor::xVector, _x );
    conveyor->setData( &PythonConveyor::yVector, _y );

    conveyor->sendDataToIntegration();
    QString resultStr = conveyor->getData( &PythonConveyor::resultString );
    area = resultStr.toStdString();
    emit readyToSendArea( area );
}

void RightWidget::differentiationSolve( const QVector<double>& x, const QVector<double>& y, Sender& sender )
{
    conveyor->setData( &PythonConveyor::functionName, sender.functionName );
    conveyor->setData( &PythonConveyor::pythonFilePath, sender.moduleName );

    std::vector<double> _x(std::begin(x), std::end(x));
    std::vector<double> _y(std::begin(y), std::end(y));

    conveyor->setData( &PythonConveyor::xVector, _x );
    conveyor->setData( &PythonConveyor::yVector, _y );

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

void RightWidget::checkoutAxeses( void )
{
    if( graphBuilder->graph2d->yAxis->label() == "y'" )
    {
        graphBuilder->onClearButtonClicked();
        graphBuilder->graph2d->yAxis->setLabel( "y" );
    }
}

void RightWidget::clearGraph( void )
{
    if( graphBuilder->graph2d->isVisible() )
    {
        graphBuilder->onClearButtonClicked();
        return;
    }
    graphBuilder->graph3d->onClearButtonClicked();
}

void RightWidget::drawInterpolationGraph( const std::vector<double> x, const std::vector<double> y )
{
    QVector<double> X = QVector<double>( x.begin(), x.end() );
    QVector<double> Y = QVector<double>( y.begin(), y.end() );
    graphBuilder->PaintG( X, Y, "График интерполяции (" + currentLegend + ")", true, false, false );
}

void RightWidget::moveLegend( void )
{
    graphBuilder->moveLegend();
}

void RightWidget::showLegend( void )
{
    graphBuilder->showLegend();
    if( !graphBar->legendEnabled )
    {
        graphBar->actions().at( 3 )->setIcon( QIcon( ":/toolbaricons/resources/hideLegend.PNG" ) );
        graphBuilder->showLegend();
        graphBar->legendEnabled = true;
        return;
    }
    graphBar->actions().at( 3 )->setIcon( QIcon( ":/toolbaricons/resources/showLegend.PNG" ) );
    graphBuilder->hideLegend();
    graphBar->legendEnabled = false;
}

void RightWidget::hideLegend( void )
{
    graphBuilder->hideLegend();
}

void RightWidget::stepBack( void )
{
    if( graphBuilder->graph2d->isVisible() )
    {
        graphBuilder->GoBack();
        return;
    }
    graphBuilder->graph3d->stepBack();
}

void RightWidget::stepForward( void )
{
    if( graphBuilder->graph2d->isVisible() )
    {
        graphBuilder->GoFront();
        return;
    }
    graphBuilder->graph3d->stepForward();
}

void RightWidget::zoomIn( void )
{
    if( graphBuilder->graph2d->isVisible() ) [[likely]]
    {
        graphBuilder->zoomIn();
        return;
    }
    graphBuilder->graph3d->zoomIn();
}

void RightWidget::zoomOut( void )
{
    if( graphBuilder->graph2d->isVisible() ) [[likely]]
    {
        graphBuilder->zoomOut();
        return;
    }
    graphBuilder->graph3d->zoomOut();
}

void RightWidget::resetZoom( void )
{
    if( graphBuilder->graph2d->isVisible() ) [[likely]]
    {
        graphBuilder->resetZoom();
        return;
    }
    //graphBuilder->graph3d->resetZoom();
}


void RightWidget::couldSavePlotAsImage( bool couldSave )
{
    graphBar->actions().at( 9 )->setEnabled( couldSave );
}

void RightWidget::unpinGraph( void )
{
    //graphBar->unsetChecked();
    graphBar->actions().at( 8 )->setChecked( true );

    if( unpinned )
    {
        graphBar->actions().at( 8 )->setChecked( false );
        return;
    }
    graphBar->actions().at( 8 )->setEnabled( false );

    graphBarWidth = graphBar->width();
    graph2dHeight = graphBuilder->graph2d->height();
    graph3dHeight = graphBuilder->graph3d->height();

    QDialog* dialog = new QDialog;
    dialog->setWindowFlags( dialog->windowFlags() & ~Qt::WindowSystemMenuHint );
    dialog->setWindowTitle( "Unpinned plot" );
    QVBoxLayout* layout = new QVBoxLayout( dialog );

    layout->addWidget( this->graphBar );
    layout->addWidget( graphBuilder->graph2d );
    layout->addWidget( graphBuilder->graph3d );
    dialog->setLayout( layout );

    connect( dialog, &QDialog::finished, this, [=]( int result )
        {
            Q_UNUSED( result );
            rightLayout->addWidget( graphBar );
            rightLayout->addWidget( graphBuilder->graph2d );
            rightLayout->addWidget( graphBuilder->graph3d );
            graphBar->setFixedWidth( graphBarWidth );
            graphBuilder->graph2d->setFixedHeight( graph2dHeight );
            graphBuilder->graph3d->setFixedHeight( graph3dHeight );
            graphBar->actions().at( 8 )->setEnabled( true );
            dialog->deleteLater();
            unpinned = false;
        }
    );

    dialog->show();
    unpinned = true;
    graphBar->actions().at( 8 )->setChecked( false );
}

void RightWidget::savePlotAsImage()
{
    if( graphBuilder->graph2d->isVisible() )
    {
        graphBuilder->savePlotAsImage();
        return;
    }
    graphBuilder->graph3d->savePlotAsImage();
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

