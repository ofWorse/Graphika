#include "functionlayout.h"
#include "graphlayout.h"
#include "layoutfactory.h"
#include "polynomelayout.h"


QGridLayout *LayoutFactory::createFunctionLayout( QWidget *parent )
{
    return (new FunctionLayout( parent ))->getLayout();
}

QGridLayout *LayoutFactory::createPolynomeLayout( QWidget *parent )
{
    return (new PolynomeLayout( parent ))->getLayout();
}

QGridLayout *LayoutFactory::createGraphLayout( QWidget *parent )
{
    return (new GraphLayout( parent ))->getLayout();
}
