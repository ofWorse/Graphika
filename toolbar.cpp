#include "toolbar.h"
#include <QIcon>

Toolbar::Toolbar( QWidget *parent )
    : QToolBar{ parent }
{
    addAction( QIcon( ":/toolbaricons/resources/function.PNG" ), "Построить график функции f(x)" );
    addAction( QIcon( ":/toolbaricons/resources/diff.PNG" ), "Построить график функции f'(x)" );
    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/lagrange.PNG" ), "Построить модель полинома Лагранжа" );
    addAction( QIcon( ":/toolbaricons/resources/newthon.PNG" ), "Построить модель полинома Ньютона" );
    addAction( QIcon( ":/toolbaricons/resources/berruta.PNG" ), "Построить модель полинома Берута" );
    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/clean.PNG" ), "Очистить график" );
    addAction( QIcon( ":/toolbaricons/resources/home.PNG" ), "Вернуть график" );
}
