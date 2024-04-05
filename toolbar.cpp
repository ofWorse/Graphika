#include "toolbar.h"
#include <QIcon>

Toolbar::Toolbar( QWidget *parent )
    : QToolBar{ parent }
{
    addAction( QIcon( ":/toolbaricons/resources/function.PNG" ), "f(x)" );
    // TODO: подумать над улучшенной реализацией разделения
    addSeparator();
    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/lagrange.PNG" ), "L" );
    addAction( QIcon( ":/toolbaricons/resources/newthon.PNG" ), "N" );
    addAction( QIcon( ":/toolbaricons/resources/berruta.PNG" ), "B" );
    addSeparator();
    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/clean.PNG" ), "cl" );
}
