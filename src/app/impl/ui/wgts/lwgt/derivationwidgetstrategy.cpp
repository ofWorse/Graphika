#include "derivationwidgetstrategy.h"

QLayout* DerivationWidgetStrategy::createWidgets( void )
{
    layout = widgets->initLayout();
    widgets->calculatedArea->show();
    widgets->area->show();
    widgets->buildGraph->setText( "Вычислить площадь" );
    return layout;
}

void DerivationWidgetStrategy::saveState( void )
{

}

void DerivationWidgetStrategy::restoreState( void )
{

}
