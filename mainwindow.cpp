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

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    connect( toolbar->actions().at( 1 ), &QAction::triggered, this, &MainWindow::sendAction );
    connect( toolbar->actions().at( 4 ), &QAction::triggered, this, &MainWindow::clearGraph );
    connect( toolbar->actions().at( 5 ), &QAction::triggered, this, &MainWindow::resetZoom );
}

void MainWindow::sendAction( void )
{
    sender.setMacro(pymodules::Methods::LAGRANGE, pymodules::Modules::POLYNOMIALS);
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
