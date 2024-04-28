#include "mainwindow.h"

// TODO: Сделать код чище
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    resize( 1150, 660 );
    setMinimumSize( 640, 380 );
    setMaximumSize( QWIDGETSIZE_MAX, QWIDGETSIZE_MAX );
    setWindowTitle( "Graphika" );

    // TODO: Подумать над реализацией соединения
    menu = new Menu( this );
    setMenuBar( menu->getMenu() );
    connect( menu, &Menu::sessionStarted, this, &MainWindow::startSession );
    connect( menu, &Menu::sessionStopped, this, &MainWindow::endSession );

    toolbar = new Toolbar( this );
    toolbar->setContextMenuPolicy( Qt::ContextMenuPolicy::PreventContextMenu );
    toolbar->setIconSize( *new QSize( 40, 40 ) );
    addToolBar( Qt::RightToolBarArea, toolbar );

    QScrollArea *scrollArea = new QScrollArea( this );
    QWidget *scrollContentWidget = new QWidget;

    layout = new QGridLayout( this );
    centralwidget = new QWidget( this );

    leftWidget = new LeftWidget( buffer, this );
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::draw );

    rightWidget = new RightWidget( this );

    centralwidget->setLayout( layout );
    setCentralWidget( centralwidget );
    scrollLayout = new QGridLayout( scrollContentWidget );

    scrollLayout->addWidget( leftWidget, 1, 0 );
    scrollLayout->addWidget( rightWidget, 1, 1 );
    connect( rightWidget, &RightWidget::sendData, &logStack, &CompositeStateStack::receiveData );
    connect( leftWidget, &LeftWidget::sendData, &logStack, &CompositeStateStack::receiveData );
    connect( rightWidget, &RightWidget::errorOccured, leftWidget, &LeftWidget::handleParserError );
    connect( rightWidget, &RightWidget::readyToSendData, leftWidget, &LeftWidget::acceptData );
    connect( rightWidget, &RightWidget::readyToSendArea, leftWidget, &LeftWidget::acceptArea );
    connect( leftWidget, &LeftWidget::readyToDraw, rightWidget, &RightWidget::drawGraph );
    //connect( leftWidget, &LeftWidget::readyToSendLinearEquationsData, rightWidget, &RightWidget::solveLinearEquations );

    connect( this, &MainWindow::buildDerivativeWidgets, rightWidget, &RightWidget::rebuildWidgets );
    connect( this, &MainWindow::buildDerivativeWidgets, leftWidget, &LeftWidget::rebuildWidgets );
    connect( this, &MainWindow::buildDefaultWidgets, leftWidget, &LeftWidget::rebuildWidgets );

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    connect( toolbar->actions().at( 0 ), &QAction::triggered, this, &MainWindow::openFunctionMenu );
    connect( toolbar->actions().at( 1 ), &QAction::triggered, this, &MainWindow::openDerivativeMenu );
    connect( toolbar->actions().at( 2 ), &QAction::triggered, this, &MainWindow::openIntegrationMenu );
    connect( toolbar->actions().at( 3 ), &QAction::triggered, this, &MainWindow::openEquationSystemMenu );
    connect( toolbar->actions().at( 5 ), &QAction::triggered, this, &MainWindow::openLagrangeMenu );
    connect( toolbar->actions().at( 6 ), &QAction::triggered, this, &MainWindow::openNewtonMenu );
    connect( toolbar->actions().at( 7 ), &QAction::triggered, this, &MainWindow::openBerrutaMenu );
    connect( toolbar->actions().at( 9 ), &QAction::triggered, this, &MainWindow::clearGraph );
    connect( toolbar->actions().at( 10 ), &QAction::triggered, this, &MainWindow::resetZoom );
    connect( toolbar->actions().at( 11 ), &QAction::triggered, this, &MainWindow::moveLegend );
    connect( toolbar->actions().at( 12 ), &QAction::triggered, this, &MainWindow::seeLegend );
}

void MainWindow::openFunctionMenu( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 0 )->setChecked( true );
    widgetState = pymodules::Modules::NIL;
    emit buildDefaultWidgets( widgetState, buffer );
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::draw );
}

void MainWindow::openDerivativeMenu( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 1 )->setChecked( true );
    widgetState = pymodules::Modules::DIFFERENTIATION;
    emit buildDerivativeWidgets( widgetState, buffer );
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::draw );
}

void MainWindow::openIntegrationMenu()
{
    toolbar->unsetChecked();
    toolbar->actions().at( 2 )->setChecked( true );
    widgetState = pymodules::Modules::INTEGRATION;
    emit buildDefaultWidgets( widgetState, buffer );
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::draw );
}

void MainWindow::openEquationSystemMenu( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 3 )->setChecked( true );
    widgetState = pymodules::Modules::EQUATIONS;
    emit buildDerivativeWidgets( widgetState, buffer );
    connect( leftWidget, &LeftWidget::readyToSendLinearEquationsData, this, &MainWindow::calculateSys);
    connect( rightWidget, &RightWidget::readyToSendSysResult, leftWidget, &LeftWidget::setEqResult);
}

void MainWindow::openLagrangeMenu( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 5 )->setChecked( true );
    widgetState = pymodules::Modules::NIL;
    emit buildDefaultWidgets( widgetState, buffer );
    methodOfInterpolation = pymodules::Methods::LAGRANGE;
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::buildPolynomeGraph );
}

void MainWindow::openNewtonMenu( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 6 )->setChecked( true );
    widgetState = pymodules::Modules::NIL;
    emit buildDefaultWidgets( widgetState, buffer );
    methodOfInterpolation = pymodules::Methods::NEWTON;
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::buildPolynomeGraph );
}

void MainWindow::openBerrutaMenu( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 7 )->setChecked( true );
    widgetState = pymodules::Modules::NIL;
    emit buildDefaultWidgets( widgetState, buffer );
    methodOfInterpolation = pymodules::Methods::BERRUTA;
    connect( leftWidget->buildGraph, &QPushButton::clicked, this, &MainWindow::buildPolynomeGraph );
}

void MainWindow::draw( void )
{
    switch( widgetState )
    {
    case pymodules::Modules::NIL:
        printFunctionGraph();
        break;
    case pymodules::Modules::DIFFERENTIATION:
        printDiffGraph();
        break;
    case pymodules::Modules::POLYNOMIALS:
        buildPolynomeGraph();
        break;
    case pymodules::Modules::INTEGRATION:
        calculateIntegral();
    default:
        qDebug() << "No such method.\n";
        break;
    }
}

void MainWindow::buildPolynomeGraph( void )
{
    switch( methodOfInterpolation )
    {
    case pymodules::Methods::LAGRANGE:
        invokeLagrangeMethod();
        break;
    case pymodules::Methods::NEWTON:
        invokeNewtonMethod();
        break;
    case pymodules::Methods::BERRUTA:
        invokeBerrutaMethod();
        break;
    default:
        break;
    }
}

void MainWindow::printFunctionGraph( void )
{
    sender.setMacro( pymodules::Methods::NIL, pymodules::Modules::NIL );
    if( isSession )
    {
        rightWidget->printGraph( buffer, sender, &logStack );
        return;
    }
    rightWidget->printGraph( buffer, sender, nullptr );
}


void MainWindow::printDiffGraph( void )
{
    pymodules::Methods method = toolbar->getSelectedDiffMethod();
    sender.setMacro( method, pymodules::Modules::DIFFERENTIATION );
    if( isSession )
    {
        rightWidget->printDiffGraph( buffer, sender, &logStack );
        return;
    }
    rightWidget->printDiffGraph( buffer, sender, nullptr );
}

void MainWindow::calculateIntegral( void )
{
    pymodules::Methods method = toolbar->getSelectedIntegralMethod();
    sender.setMacro( method, pymodules::Modules::INTEGRATION );
    if( isSession )
    {
        rightWidget->calculateIntegral( buffer, sender, &logStack );
        return;
    }
    rightWidget->calculateIntegral( buffer, sender, nullptr );
}

void MainWindow::calculateSys(QVector<QVector<double>>& data)
{
    pymodules::Methods method = toolbar->getSelectedSysMethod();
    sender.setMacro(method, pymodules::Modules::EQUATIONS);
    rightWidget->sysSolve(data, sender);
}

void MainWindow::invokeLagrangeMethod( void )
{
    emit buildDefaultWidgets( pymodules::Modules::NIL, buffer );
    widgetState = pymodules::Modules::POLYNOMIALS;
    sender.setMacro( pymodules::Methods::LAGRANGE, pymodules::Modules::POLYNOMIALS );
    if( isSession )
    {
        rightWidget->buildPolynome( buffer, sender, &logStack );
        return;
    }
    rightWidget->buildPolynome( buffer, sender, nullptr );
}

void MainWindow::invokeNewtonMethod( void )
{
    emit buildDefaultWidgets( pymodules::Modules::NIL, buffer );
    widgetState = pymodules::Modules::POLYNOMIALS;
    sender.setMacro( pymodules::Methods::NEWTON, pymodules::Modules::POLYNOMIALS );
    if( isSession )
    {
        rightWidget->buildPolynome( buffer, sender, &logStack );
        return;
    }
    rightWidget->buildPolynome( buffer, sender, nullptr );
}

void MainWindow::invokeBerrutaMethod( void )
{
    emit buildDefaultWidgets( pymodules::Modules::NIL, buffer );
    widgetState = pymodules::Modules::POLYNOMIALS;
    sender.setMacro( pymodules::Methods::BERRUTA, pymodules::Modules::POLYNOMIALS );
    if( isSession )
    {
        rightWidget->buildPolynome( buffer, sender, &logStack );
        return;
    }
    rightWidget->buildPolynome( buffer, sender, nullptr );
}

void MainWindow::clearGraph( void )
{
    toolbar->unsetChecked();
    rightWidget->clearGraph();
}

void MainWindow::resetZoom( void )
{
    toolbar->unsetChecked();
    rightWidget->graphBuilder->ZoomB();
}

void MainWindow::moveLegend( void )
{
    rightWidget->moveLegend();
}

void MainWindow::seeLegend( void )
{
    rightWidget->seeLegend();
}

void MainWindow::stepBack()
{
    rightWidget->stepBack();
}

void MainWindow::startSession( void )
{
    isSession = true;
    // Временная заглушка
    QMessageBox mb;
    mb.setIcon( QMessageBox::Warning );
    mb.setWindowTitle( "Предупреждение" );
    mb.setText( "В разработке" );
    mb.setStandardButtons( QMessageBox::Ok );
    mb.exec();

    menu->getEndSessionAction()->setEnabled( true );
    menu->getStartSessionAction()->setEnabled( false );
}

void MainWindow::endSession()
{
    isSession = false;
    menu->getEndSessionAction()->setEnabled( false );
    menu->getStartSessionAction()->setEnabled( true );
}
