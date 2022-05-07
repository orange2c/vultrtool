
#include "vpsmodel.h"


VPSMODE_DATA::VPSMODE_DATA( QJsonObject *vps_json )
{
//    qDebug("开始vpsmodel");
//    locationsCNp = new  QStringList();
    location_strlist = new  QStringList();
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
        location_strlist->append( location_json.at(i).toString()  );

    local->transfer(location_strlist);
}

VPSMODE_DATA::~VPSMODE_DATA()
{
    delete introduceP;
    delete location_strlist;
    delete local;
}

QString VPSMODE_DATA::introduce()
{
    return QString(*introduceP);
}


QString VPSMODE_DATA::model_id()
{
    return QString(id);
}

/******************VModelFamilly*********************/
VModelFamilly::VModelFamilly()
{}
VModelFamilly::VModelFamilly( QString name, QString type_name  )
{
    setname(name);
    model_type = type_name;
}
void VModelFamilly::append( QJsonObject *vps_json )
{
    VPSMODE_DATA *newmodel = new VPSMODE_DATA( vps_json );
    LinkedList::append( newmodel );
}


