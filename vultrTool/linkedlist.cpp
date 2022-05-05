#include "linkedlist.h"

LinkedList::~LinkedList()
{
    list *pnext;
    while( first!=NULL )
    {
        pnext = first->next;
        delete first->data;
        delete first;
        first = pnext;
    }
}
int LinkedList::size()
{
    return list_size;
}
LinkedList::list* LinkedList::list_at(int num)
{
    int i = 0;
    list *datalist = first ;
    for( ; i<num; i++ )
    {
        datalist = datalist->next;
    }
    return datalist;
}
void LinkedList::list_append( list *append_source )
{

    append_source->next = NULL;
    if( list_size == 0  )
    {
        first = append_source;
    }
    else
    {
        last->next = append_source;
    }
    last = append_source;
    list_size++ ;
}
