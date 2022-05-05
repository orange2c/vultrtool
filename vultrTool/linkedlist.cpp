#include "linkedlist.h"

LinkedList::~LinkedList()
{
    list *pnext;
    while( first!=NULL )
    {
        pnext = first->next;
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
void LinkedList::list_append( void *append_data )
{
    list *newlist = new list();
    newlist->data = append_data;
    newlist->next = NULL;
    if( list_size == 0  )
    {
        first = newlist;
    }
    else
    {
        last->next = newlist;
    }
    last = newlist;
    list_size++ ;
}
