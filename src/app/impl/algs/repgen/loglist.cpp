#include "loglist.h"

void LogList::addItem( const Item& item )
{
    items.append( item );
}

LogList::ItemType LogList::getItemType( const Item& item )
{
    return item.item;
}
