#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <QObject>

class LinkedList
{
public:
    ~LinkedList();

    int size();
protected:
    class list
    {
    public:
        void *data;
        list *next;
    };
    int list_size= 0;  //有多少成员

    list *first=NULL; //指向链表第一个成员
    list *last; //指向链表最后一个成员

    list * list_at(int num);
    void list_append( void *append_data );
    void list_delete(int num);


};

#endif // LINKEDLIST_H
