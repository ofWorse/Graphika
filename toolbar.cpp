#include "toolbar.h"

Toolbar::Toolbar( QWidget *parent )
    : QToolBar{ parent }
{
    addAction( "f(x)" );
    //addAction( "f'(x)" );
    addAction( "p(x)" );
    addAction( "Graphika" );
}
