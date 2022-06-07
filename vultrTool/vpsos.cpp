#include "vpsos.h"

Os_Data::Os_Data( QJsonObject *os_json )
{
    id =  Spider::path( os_json, "id" ).toInt() ;
    name.append( Spider::path( os_json, "name" ).toString() );
    family.append( Spider::path( os_json, "family" ).toString() );
    qDebug("id=%d,name=%s,familly=%s",id, qPrintable(name), qPrintable(family) );
}

/*******************************VOSFAMILLY*********************************/

Os_LinkedList::Os_LinkedList( QString name )
{
    setname(name);
}

void Os_LinkedList::append( QJsonObject *os_json )
{
    Os_Data *os = new Os_Data(os_json);
    LinkedList::append( os);
}
bool Os_LinkedList::appendSame( Os_Data *os )
{

    if( QString::compare( this->name(), os->family )==0 )
    {
        LinkedList::append(os);
        return true;
    }
    else
        return false;
}

Os_LinkedList* VpsOs::at(int num)
{
    if( num<0 ) num=0;
    if( num>=OS_LIST_SIZE )num = OS_LIST_SIZE-1;
    return OSlist[ num ];
}


VpsOs::VpsOs( QObject *parent )
{
    Q_UNUSED( parent );

}

VpsOs::~VpsOs()
{
    for( int i=0; i<OS_LIST_SIZE; i++)
    {
        delete OSlist[i];
    }
}

void VpsOs::update()
{
    if( spider_os == NULL )
    {
        spider_os = new Spider;
        connect( spider_os, SIGNAL( reply_ready() ), SLOT( analyze_os() )   );
        spider_os->get("os");

    }
}
void VpsOs::analyze_os()
{

    QStringList match_str;
    match_str << "os";

    QJsonArray all_os_json = spider_os->path( &match_str ).toArray();
//    analyze(&all_os_json);

    Os_LinkedList *os_all = OSlist[OS_LIST_SIZE-1];//存储所有可用os
    for( int i=0; i<all_os_json.size(); i++ )
    {
        QJsonObject os_json = all_os_json.at(i).toObject();
        os_all->append( &os_json );
    }
    for( int listp=0; listp<( OS_LIST_SIZE-1); listp++ )//计算数组长度，控制为循环次数
    {
        int i =0;
        while (i < os_all->size())
        {
            if( OSlist[listp]->appendSame( os_all->at(i) ) )
            {
                os_all->deleteat(i);
            }
             i++;
        }
    }
    delete  spider_os;
    spider_os = NULL;
}
