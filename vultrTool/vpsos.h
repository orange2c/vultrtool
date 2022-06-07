#ifndef VPSOS_H
#define VPSOS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "spider.h"
#include "linkedlist.h"

class Os_Data
{

public:
    Os_Data( QJsonObject *os_json ); //传入一串带os信息的json，拆解其中信息

    int id;
    QString name;
    QString arch;
    QString family;

};

class Os_LinkedList: public LinkedList< Os_Data >
{
public:
    Os_LinkedList( QString name ); //传入familly名称

    void append( QJsonObject *os_json );
    bool appendSame( Os_Data *os ); //会判断传入的os的familly是否跟自己一致，相同则append然后返回true

};
class VpsOs : public QObject
{
    Q_OBJECT
public:
    explicit VpsOs( QObject *parent = 0 );
    ~VpsOs();
    Os_LinkedList *at( int num );
    void update();

public slots:
    void analyze_os();

protected:
    Spider *spider_os = NULL;
#define  OS_LIST_SIZE  8
    Os_LinkedList *OSlist[OS_LIST_SIZE] = {
        //目前可用os类型
        new Os_LinkedList("ubuntu"),
        new Os_LinkedList("centos"),
        new Os_LinkedList("debian"),
        new Os_LinkedList("freebsd"),
        new Os_LinkedList("fedora"),
        new Os_LinkedList("vzlinux"),
        new Os_LinkedList("openbsd"),
        new Os_LinkedList("other")
    };

};

#endif // VPSOS_H
