#include "vpsos.h"

VPSOS::VPSOS( QJsonObject *os_json )
{
    id =  SPIDER::path( os_json, "id" ).toInt() ;
    name.append( SPIDER::path( os_json, "name" ).toString() );
    family.append( SPIDER::path( os_json, "family" ).toString() );
    qDebug("id=%d,name=%s,familly=%s",id, qPrintable(name), qPrintable(family) );

}

/*******************************VOSFAMILLY*********************************/

VOsFamilly::VOsFamilly( QString name )
{
    familly_name.append(name);
}
VOsFamilly::~VOsFamilly( )
{
    linked_list *pnext;
    while( first!=NULL )
    {
        pnext = first->next;
        delete first->data;
        delete first;
        first = pnext;
    }
}
QString VOsFamilly::name()
{
    return QString(familly_name);
}

VPSOS* VOsFamilly::at(int num)
{
    int i = 0;
    linked_list *os_list = first ;
    for( ; i<num; i++ )
    {
        os_list = os_list->next;
    }
    return os_list->data;
}
int VOsFamilly::size()
{
    return size_p;
}
void VOsFamilly::append( VPSOS *os )
{
    linked_list *linked_new = new linked_list;
    linked_new->data = os;
    linked_new->next = NULL;
    if( size_p == 0  )
    {
        first = linked_new;
    }
    else
    {
        last->next = linked_new;
    }
    last = linked_new;
    size_p++ ;
}
void VOsFamilly::append( QJsonObject *os_json )
{
    VPSOS *os = new VPSOS(os_json);
    this->append( os);
}
bool VOsFamilly::appendSame( VPSOS *os )
{
    qDebug("myname=%s",qPrintable(this->familly_name) );
//    qDebug("id=%d", os->id );
    qDebug("hisfamilly=%s",qPrintable(os->family) );

    if( QString::compare( this->familly_name, os->family )==0 )
    {
        append(os);
        return true;
    }
    else
    {
//        qDebug("vpsarray,no");
        return false;
    }

}

