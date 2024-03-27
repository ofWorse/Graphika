#include "graphlayout.h"

#include <QLabel>

GraphLayout::GraphLayout( QWidget *parent )
    : QWidget( parent )
{
    layout = new QGridLayout( this );
    QLabel* soon = new QLabel( "скоро", this );
    layout->addWidget( soon, 0, 0 );
}
