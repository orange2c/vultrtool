#ifndef VPSOS_H
#define VPSOS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "spider.h"
#include "linkedlist.h"

class OSDATA : public QObject
{
    Q_OBJECT
public:
    OSDATA( QJsonObject *os_json ); //传入一串带os信息的json，拆解其中信息

    int id;
    QString name;
    QString arch;
    QString family;

};

class VOsFamilly: public LinkedList< OSDATA >
{
public:
    VOsFamilly( QString name ); //传入familly名称

    void append( QJsonObject *os_json );
    bool appendSame( OSDATA *os ); //会判断传入的os的familly是否跟自己一致，相同则append然后返回true

};
class VPSOS
{
public:
    ~VPSOS();
    VOsFamilly *at( int num );
    void update();

protected:
    void analyze(QJsonArray *all_os_json); //传入包含所有os的json数组

#define  OS_LIST_SIZE  8
    VOsFamilly *OSlist[OS_LIST_SIZE] = {
        //目前可用os类型
        new VOsFamilly("ubuntu"),
        new VOsFamilly("centos"),
        new VOsFamilly("debian"),
        new VOsFamilly("freebsd"),
        new VOsFamilly("fedora"),
        new VOsFamilly("vzlinux"),
        new VOsFamilly("openbsd"),
        new VOsFamilly("other")
    };

};
//    };


#endif // VPSOS_H
