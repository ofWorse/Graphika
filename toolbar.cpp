#include "toolbar.h"

Toolbar::Toolbar( QWidget *parent )
    : QToolBar{ parent }
{
    addAction( "f(x)" );
    addAction( "f'(x)" );
    addAction( "p(x)" );
    addAction( "Graphika" );
    addSeparator();

    QAction* action = addAction( "Выйти" );
    connect( action, &QAction::triggered, qApp, &QApplication::quit );
}
