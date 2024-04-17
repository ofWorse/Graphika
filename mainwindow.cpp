#include "mainwindow.h"

// TODO: Сделать код чище
//       Подумать над неймингом объектов.
//       Сделать вертикальное меню
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    resize( 1020, 600 );
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
    addToolBar( Qt::RightToolBarArea, toolbar );

    QScrollArea *scrollArea = new QScrollArea( this );
    QWidget *scrollContentWidget = new QWidget;

    layout = new QGridLayout( this );
    centralwidget = new QWidget( this );
    leftWidget = new LeftWidget( buffer, this );
    rightWidget = new RightWidget( this );

    centralwidget->setLayout( layout );
    setCentralWidget( centralwidget );
    scrollLayout = new QGridLayout( scrollContentWidget );

    //scrollLayout->addWidget( menu->get(), 0, 0, 1, 2 );
    scrollLayout->addWidget( leftWidget, 1, 0 );
    scrollLayout->addWidget( rightWidget, 1, 1 );
    connect( rightWidget, &RightWidget::sendData, &logStack, &CompositeStateStack::receiveData );
    connect( leftWidget, &LeftWidget::sendData, &logStack, &CompositeStateStack::receiveData );
    connect( rightWidget, &RightWidget::errorOccured, leftWidget, &LeftWidget::handleParserError );
    connect( rightWidget, &RightWidget::readyToSendData, leftWidget, &LeftWidget::acceptData );
    connect( leftWidget, &LeftWidget::readyToDraw, rightWidget, &RightWidget::drawGraph );

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    connect( toolbar->actions().at( 0 ), &QAction::triggered, this, &MainWindow::printGraph );
    connect( toolbar->actions().at( 1 ), &QAction::triggered, this, &MainWindow::printDiffGraph );
    connect( toolbar->actions().at( 3 ), &QAction::triggered, this, &MainWindow::invokeLagrangeMethod );
    connect( toolbar->actions().at( 4 ), &QAction::triggered, this, &MainWindow::invokeNewtonMethod );
    connect( toolbar->actions().at( 5 ), &QAction::triggered, this, &MainWindow::invokeBerrutaMethod );
    connect( toolbar->actions().at( 7 ), &QAction::triggered, this, &MainWindow::clearGraph );
    connect( toolbar->actions().at( 8 ), &QAction::triggered, this, &MainWindow::resetZoom );
}

void MainWindow::printGraph()
{
    sender.setMacro( pymodules::Methods::NIL, pymodules::Modules::NIL );
    if( isSession )
    {
        rightWidget->printGraph( buffer, sender, &logStack );
        return;
    }
    rightWidget->printGraph( buffer, sender, nullptr );
}

void MainWindow::printDiffGraph()
{
    sender.setMacro( pymodules::Methods::DIFF_3P, pymodules::Modules::DIFFERENTIATION );
    QString expression = leftWidget->getExpressionInput()->text();
    if( isSession )
    {
        rightWidget->printDiffGraph( buffer, sender, expression, &logStack );
        return;
    }
    rightWidget->printDiffGraph( buffer, sender, expression, nullptr );
}


void MainWindow::invokeLagrangeMethod( void )
{
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
    rightWidget->clearGraph();
}

void MainWindow::resetZoom( void )
{
    rightWidget->graphBuilder->ZoomB();
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
