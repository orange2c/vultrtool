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
    if(num >= list_size)
        num = list_size-1;
    if(num<0)
        num = 0;
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

void LinkedList::list_deleteat(int num)
{
    list *waite_delete = list_at(num);

    list_at(num-1)->next = list_at(num+1); //at函数会判断num是否越界，并自动修正

    list_size --;
    delete waite_delete;
}
void LinkedList::list_clear()
{
    while( list_size >1 )
        list_deleteat( list_size-1 );
}
