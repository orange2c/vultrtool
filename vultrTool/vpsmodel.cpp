
#include "vpsmodel.h"


VPSMODEL::VPSMODEL( QJsonObject *vps_json )
{
//    qDebug("开始vpsmodel");
    locationsCNp = new  QStringList();
    locationsENp = new  QStringList();
    introduceP = new  QString();

    //开始拆解json中的机型信息
    id .append( SPIDER::path( vps_json, "id" ).toString()) ;
    vcpu_count =  SPIDER::path( vps_json, "vcpu_count" ).toInt() ;
    ram =  SPIDER::path( vps_json, "ram" ).toInt() ;
    disk = SPIDER::path( vps_json, "disk" ).toInt() ;
    disk_count = SPIDER::path( vps_json, "disk_count" ).toInt() ;
    bandwidth = SPIDER::path( vps_json, "bandwidth" ).toInt() ;
    disk_count = SPIDER::path( vps_json, "disk_count" ).toInt() ;
    monthly_cost =  SPIDER::path( vps_json, "monthly_cost" ).toDouble() ;

    introduceP->append(QString::number(vcpu_count)+'\t');
    introduceP->append(QString::number(ram/1024)+"g\t");
    introduceP->append(QString::number(disk)+"G\t");
    introduceP->append(QString::number(monthly_cost/672, 'f', 4 )+ "$\t");
    introduceP->append(QString::number(monthly_cost)+ "$");

    QJsonArray location_json = SPIDER::path( vps_json, "locations" ).toArray();
    for( int i = 0; i<location_json.size(); i++ )
        locationsENp->append( location_json.at(i).toString()  );

    local->transfer(locationsENp);
}

VPSMODEL::~VPSMODEL()
{
    delete introduceP;
    delete locationsCNp;
    delete locationsENp;
    delete local;
}

QString VPSMODEL::introduce()
{
    return QString(*introduceP);
}

//QStringList VPSMODEL::locationsEN()
//{
//    return QStringList(*locationsENp);
//}
QString VPSMODEL::model_id()
{
    return QString(id);
}

/******************VModelFamilly*********************/


void VModelFamilly::append( QJsonObject *vps_json )
{
    VPSMODEL *newmodel = new VPSMODEL( vps_json );
    LinkedList::append( newmodel );
}


