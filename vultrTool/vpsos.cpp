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
    setname(name);
}


void VOsFamilly::append( QJsonObject *os_json )
{
    VPSOS *os = new VPSOS(os_json);
    LinkedList::append( os);
}
bool VOsFamilly::appendSame( VPSOS *os )
{
    qDebug("myname=%s",qPrintable(this->name()) );
    qDebug("hisfamilly=%s",qPrintable(os->family) );

    if( QString::compare( this->name(), os->family )==0 )
    {
        LinkedList::append(os);
        return true;
    }
    else
    {
//        qDebug("vpsarray,no");
        return false;
    }

}
