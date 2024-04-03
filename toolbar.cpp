#include "toolbar.h"

Toolbar::Toolbar( QWidget *parent )
    : QToolBar{ parent }
{
    addAction( "f(x)" );
    addAction( "Lagrange" );
}
