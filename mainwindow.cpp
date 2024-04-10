#include "mainwindow.h"

// TODO: Сделать код чище
//       Подумать над неймингом объектов.
//       Сделать вертикальное меню
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    setFixedSize( 1020, 540 );
    setWindowTitle( "Graphika" );

    toolbar = new Toolbar( this );
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

    scrollLayout->addWidget( leftWidget, 0, 0 );
    scrollLayout->addWidget( rightWidget, 0, 1 );
    connect( rightWidget, &RightWidget::errorOccured, leftWidget, &LeftWidget::handleParserError );

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
    rightWidget->printGraph( buffer, sender );
}

void MainWindow::printDiffGraph()
{
    sender.setMacro( pymodules::Methods::DIFF_3P, pymodules::Modules::DIFFERENTIATION );
    rightWidget->printGraph( buffer, sender );
}


void MainWindow::invokeLagrangeMethod( void )
{
    sender.setMacro( pymodules::Methods::LAGRANGE, pymodules::Modules::POLYNOMIALS );
    rightWidget->printGraph( buffer, sender );
}

void MainWindow::invokeNewtonMethod( void )
{
    sender.setMacro( pymodules::Methods::NEWTON, pymodules::Modules::POLYNOMIALS );
    rightWidget->printGraph( buffer, sender );
}

void MainWindow::invokeBerrutaMethod( void )
{
    sender.setMacro( pymodules::Methods::BERRUTA, pymodules::Modules::POLYNOMIALS );
    rightWidget->printGraph( buffer, sender );
}

void MainWindow::clearGraph( void )
{
    rightWidget->clearGraph();
}

void MainWindow::resetZoom( void )
{
    rightWidget->graphBuilder->ZoomB();
}
