#include "mainwindow.h"

// TODO: Сделать код чище
//       Подумать над неймингом объектов.
//       Сделать вертикальное меню
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    setFixedSize( 740, 480 );
    setWindowTitle( "Graphika" );

    toolbar = new Toolbar( this );
    addToolBar( toolbar );

    layout = new QGridLayout( this );
    centralwidget = new QWidget( this );

    centralwidget->setLayout( layout );
    setCentralWidget( centralwidget );

    connect( toolbar->actions().at( 0 ), &QAction::triggered, this, &MainWindow::openLeftMenuWidget );
    connect( toolbar->actions().at( 1 ), &QAction::triggered, this, &MainWindow::openRightMenuWidget );
}

void MainWindow::openLeftMenuWidget( void )
{
    clearLayout( layout );
    layout->deleteLater();
    leftLayout = new LeftLayout( buffer, this );
    layout = leftLayout->getLayout();
    centralwidget->setLayout( layout );
}


void MainWindow::openRightMenuWidget( )
{
    clearLayout( layout );
    layout->deleteLater();
    rightLayout = new RightLayout( buffer, this );
    layout = rightLayout->getLayout();
    centralwidget->setLayout( layout );
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
