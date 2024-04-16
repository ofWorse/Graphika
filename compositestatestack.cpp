#include "compositestatestack.h"

CompositeStateStack::CompositeStateStack( QWidget *parent )
    : QWidget{ parent }
{}

void CompositeStateStack::set( QObject* data )
{
    stack.push( data );
}

void CompositeStateStack::pop( QObject *data )
{
    int index = stack.indexOf( data );
    if( index != -1 )
    {
        stack.remove( index );
    }
    else
    {
        qDebug() << "Объект не найден.\n";
    }
}

void CompositeStateStack::receiveData( QObject *data, bool toRemove )
{
    if( toRemove )
    {
        pop( data );
        return;
    }
    set( data );
}
