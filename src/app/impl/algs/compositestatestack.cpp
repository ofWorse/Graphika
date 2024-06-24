#include "compositestatestack.h"

CompositeStateStack::CompositeStateStack( QWidget *parent )
    : QWidget{ parent }
{}


//void CompositeStateStack::receiveData( QVariant& data, bool toRemove )
//{
//    if( toRemove )
//    {
//        stack->removeOne( data );
//        return;
//    }
//    stack->append( data );
//}
