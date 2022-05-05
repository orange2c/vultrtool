#ifndef VPSOS_H
#define VPSOS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "spider.h"
class VPSOS : public QObject
{
    Q_OBJECT
public:
    VPSOS( QJsonObject *os_json ); //传入一串带os信息的json，拆解其中信息

    int id;
    QString name;
    QString arch;
    QString family;

};

class VOsFamilly
{
public:
    VOsFamilly( QString name ); //传入familly名称
    ~VOsFamilly();  //删除familly时，会顺带delete所有append进familly中的vpsos对象
    QString name();
    void append( VPSOS *os );
    void append( QJsonObject *os_json );
    bool appendSame( VPSOS *os ); //会判断传入的os的familly是否跟自己一致，相同则append然后返回true
//    void append( VPSOS *os );
    VPSOS *at( int num );
    int size();

protected:
    QString familly_name;
    int size_p = 0;  //有多少成员
    struct linked_list
    {
        VPSOS *data;
        linked_list *next;
    };
    linked_list *first=NULL;
    linked_list *last;

};



#endif // VPSOS_H
