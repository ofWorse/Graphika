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
    connect( toolbar->actions().at( 1 ), &QAction::triggered, this, &MainWindow::openPolynomialMenuWidget );
    connect( toolbar->actions().at( 2 ), &QAction::triggered, this, &MainWindow::openGraphMenuWidget );
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
    layout->deleteLater();
    layout = LayoutFactory::createFunctionLayout( this );
    centralwidget->setLayout( layout );
}


void MainWindow::openPolynomialMenuWidget()
{
    clearLayout( layout );
    layout->deleteLater();
    layout = LayoutFactory::createPolynomeLayout( this );
    centralwidget->setLayout( layout );
}

void MainWindow::openGraphMenuWidget()
{
    clearLayout( layout );
    layout->deleteLater();
    layout = LayoutFactory::createGraphLayout( this );
    centralwidget->setLayout( layout );
}
