#include "integrationwidgetstrategy.h"

QGridLayout *IntegrationWidgetStrategy::createWidgets( void )
{
    layout = LayoutBuilder::initLabels( pymodules::Modules::INTEGRATION );
    return layout;
}

void IntegrationWidgetStrategy::saveState( void )
{

}

void IntegrationWidgetStrategy::restoreState( void )
{

}
