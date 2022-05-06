#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <QObject>


//链表核心，实现所有功能，但存储的data是个void*指针,不能实现delete data，new等操作
class LinkedList_core
{
public:
    int size();
    void setname(QString name);
    QString name();
protected:
    QString name_core;
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
//    void append( data_type data ){
//        data_type newdata = new data_type();
//        list_append(newdata);
//    }
    data_type *at( int num ){
        return (data_type *)list_at(num)->data;
    }
    void deleteat( int num ){ //仅删除链表
        list_deleteat(num);
    }
    void deletedataat( int num ){ //删除链表节点及内含数据
        delete at(num);
        list_deleteat(num);
    }
    void clear(){
        while( list_size >1 )
            deleteat( list_size-1 );
    }
    void cleardata(){ //删除链表节点及内含数据
        while( list_size >1 )
            deletedataat( list_size-1 );
    }
    void take(  ){

    }
    ~LinkedList(){
        cleardata();
    }


};

#endif // LINKEDLIST_H
