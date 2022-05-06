#ifndef VPSOS_H
#define VPSOS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "spider.h"
#include "linkedlist.h"

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

class VOsFamilly: public LinkedList
{
public:
    VOsFamilly( QString name ); //传入familly名称
    ~VOsFamilly( ); //delete所有被append进来的VPSOS
    QString name();

    VPSOS *at( int num );
    void append( VPSOS *os );
    void append( QJsonObject *os_json );
    bool appendSame( VPSOS *os ); //会判断传入的os的familly是否跟自己一致，相同则append然后返回true
    void deleteat( int num );
    void clear();
protected:
    QString familly_name;


};



#endif // VPSOS_H
