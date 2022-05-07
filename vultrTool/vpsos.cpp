#include "vpsos.h"

OSDATA::OSDATA( QJsonObject *os_json )
{
    id =  SPIDER::path( os_json, "id" ).toInt() ;
    name.append( SPIDER::path( os_json, "name" ).toString() );
    family.append( SPIDER::path( os_json, "family" ).toString() );
    qDebug("id=%d,name=%s,familly=%s",id, qPrintable(name), qPrintable(family) );
}

/*******************************VOSFAMILLY*********************************/

VOsFamilly::VOsFamilly( QString name )
{
    setname(name);
}

void VOsFamilly::append( QJsonObject *os_json )
{
    OSDATA *os = new OSDATA(os_json);
    LinkedList::append( os);
}
bool VOsFamilly::appendSame( OSDATA *os )
{

    if( QString::compare( this->name(), os->family )==0 )
    {
        LinkedList::append(os);
        return true;
    }
    else
        return false;
}

VOsFamilly* VPSOS::at(int num)
{
    if( num<0 ) num=0;
    if( num>=OS_LIST_SIZE )num = OS_LIST_SIZE-1;
    return OSlist[ num ];
}
VPSOS::~VPSOS()
{
    for( int i=0; i<OS_LIST_SIZE; i++)
    {
        delete OSlist[i];
    }
}

void VPSOS::analyze(QJsonArray *all_os_json)
{
    VOsFamilly *os_all = OSlist[OS_LIST_SIZE-1];//存储所有可用os
    for( int i=0; i<all_os_json->size(); i++ )
    {
        QJsonObject os_json = all_os_json->at(i).toObject();
        os_all->append( &os_json );
    }
    for( int listp=0; listp<( OS_LIST_SIZE-1); listp++ )//计算数组长度，控制为循环次数
    {
        int i =0;
        while (i < os_all->size())
        {
//            qDebug("i=%d,id=%d", i, os_all->at(i)->id);
            if( OSlist[listp]->appendSame( os_all->at(i) ) )
            {
                os_all->deleteat(i);
            }
             i++;
        }
    }
}

void VPSOS::update()
{
    SPIDER spider;
    spider.get("os");
    qDebug("get");
    QStringList match_str;
    match_str << "os";

    QJsonArray os_all_json = spider.path( &match_str ).toArray();
    analyze(&os_all_json);

}
