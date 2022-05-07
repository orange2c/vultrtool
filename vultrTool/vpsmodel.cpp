
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
    minuter_cost = monthly_cost/672;
    introduceP->append(QString::number(vcpu_count)+'\t');
    introduceP->append(QString::number(ram/1024)+"g\t");
    introduceP->append(QString::number(disk)+"G\t");
    introduceP->append(QString::number(minuter_cost, 'f', 4 )+ "$\t");
    introduceP->append(QString::number(monthly_cost)+ "$");

    QJsonArray location_json = SPIDER::path( vps_json, "locations" ).toArray();
    for( int i = 0; i<location_json.size(); i++ )
        location_strlist->append( location_json.at(i).toString()  );

    local->update(location_strlist);
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

VModelFamilly::VModelFamilly( QString name, QString type_name, QString part  )
{
    setname(name);
    model_type = type_name;
    type_part = part;
}
void VModelFamilly::append( QJsonObject *vps_json )
{
    VPSMODE_DATA *newmodel = new VPSMODE_DATA( vps_json );
    LinkedList::append( newmodel );
}
void VModelFamilly::takeSame(QJsonArray *vps_list)
{
    SPIDER spider;
    QJsonArray thisModel;
    spider.take( vps_list, "type", QJsonValue(this->model_type), &thisModel, "id", type_part ); //将所有model_type机型的信息json，都提取出来

    QJsonArray non_delete;
    spider.take(  &thisModel, "locations", QJsonValue("sao"), &non_delete ); //删除巴西特供版机型（和其他地区机型相同，但贵%50）
    spider.take(  &thisModel, "locations", QJsonValue(), &non_delete ); //删除可部署地区为空的（不可用机型）
    int liset_size = thisModel.size();
    for( int i = 0; i<liset_size; i++ )
    {
        QJsonObject obj = thisModel.at(i).toObject();
        append( &obj );
    }
    qDebug( "%s共%d种可用机型",qPrintable(model_type),  size() );

}
VModelFamilly* VPSMODEL::at(int num)
{
    if( num<0 ) num=0;
    if( num>=MODEL_LIST_SIZE )num = MODEL_LIST_SIZE-1;
    return AllModelFamilly[ num ];
}
void VPSMODEL::update()
{
    SPIDER spider;
    spider.get( "plans" );
    QStringList match_str;

    match_str << "plans";
    QJsonArray *vps_list = new QJsonArray(spider.path( &match_str ).toArray());
    for( int i=0; i<MODEL_LIST_SIZE; i++ )
    {
        qDebug("moedl-i=%d", i);
        AllModelFamilly[i]->takeSame(vps_list);
    }



}
