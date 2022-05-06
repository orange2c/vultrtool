#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <QObject>


//链表核心，实现所有功能，但存储的data是个void*指针,不能实现delete data，new等操作
class LinkedList_core
{
public:
    ~LinkedList_core();

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
    void list_deleteat(int num);
    void list_clear();
};

//模板类，传入data的数据类型，调用上面core类实现大部分功能
template <class data_type>
class LinkedList: public LinkedList_core
{
public:
    void append( data_type *data ){
        list_append(data);
    }
    data_type *at( int num ){
        return (data_type *)list_at(num)->data;
    }
    void deleteat( int num ){
        delete at(num);
    }
    void clear(){
        while( list_size >1 )
            deleteat( list_size-1 );
    }
};

#endif // LINKEDLIST_H
