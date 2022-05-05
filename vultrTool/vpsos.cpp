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

QString VOsFamilly::name()
{
    return QString(familly_name);
}

VPSOS* VOsFamilly::at(int num)
{
    return (VPSOS*)list_at(num)->data;
}
void VOsFamilly::append( VPSOS *os )
{
    list_append( os);
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

