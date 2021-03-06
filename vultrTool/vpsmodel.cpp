
#include "vpsmodel.h"


VpsModel_Data::VpsModel_Data( QJsonObject *vps_json, bool is_metal )
{
    this->is_metal_model =  is_metal;
//    qDebug("开始vpsmodel");
//    locationsCNp = new  QStringList();
    location_strlist = new  QStringList();
    introduceP = new  QString();

    //开始拆解json中的机型信息
    id .append( Spider::path( vps_json, "id" ).toString()) ;
    type .append( Spider::path( vps_json, "type" ).toString()) ;
    ram =  Spider::path( vps_json, "ram" ).toInt() ;
    disk = Spider::path( vps_json, "disk" ).toInt() ;
    disk_count = Spider::path( vps_json, "disk_count" ).toInt() ;
    bandwidth = Spider::path( vps_json, "bandwidth" ).toInt() ;
    monthly_cost =  Spider::path( vps_json, "monthly_cost" ).toDouble() ;
    minuter_cost = monthly_cost/672;

    if( is_metal_model )
    {
        cpu_model.append( Spider::path( vps_json, "cpu_model" ).toString()) ;
        cpu_count =  Spider::path( vps_json, "cpu_count" ).toInt() ;
        cpu_threads =  Spider::path( vps_json, "cpu_threads" ).toInt() ;

        introduceP->append(cpu_model +"\t");
        introduceP->append(QString::number(cpu_count) +"核" +QString::number(cpu_threads) +"线程\t" );
        introduceP->append(QString::number(ram/1024)+"g\t");
        introduceP->append(QString::number(disk_count) +"*" + QString::number(disk)+"G\t");
        introduceP->append(QString::number(minuter_cost, 'f', 4 )+ "$\t");
        introduceP->append(QString::number(monthly_cost)+ "$");
    }
    else
    {
        vcpu_count =  Spider::path( vps_json, "vcpu_count" ).toInt() ;
        introduceP->append(QString::number(vcpu_count)+'\t');
        introduceP->append(QString::number(ram/1024)+"g\t");
        introduceP->append(QString::number(disk)+"G\t");
        introduceP->append(QString::number(minuter_cost, 'f', 4 )+ "$\t");
        introduceP->append(QString::number(monthly_cost)+ "$");
    }

    QJsonArray location_json = Spider::path( vps_json, "locations" ).toArray();
    for( int i = 0; i<location_json.size(); i++ )
        location_strlist->append( location_json.at(i).toString()  );

    location->update(location_strlist);

}

VpsModel_Data::~VpsModel_Data()
{
    delete introduceP;
    delete location_strlist;
    delete location;
}

QString VpsModel_Data::introduce()
{
    return QString(*introduceP);
}

QString VpsModel_Data::model_id()
{
    return QString(id);
}
QString VpsModel_Data::cost_month()
{
    return QString(  QString::number( monthly_cost) );
}
/******************VModelFamilly*********************/

VpsModel_LinkedList::VpsModel_LinkedList( QString name, QString type_name, QString part  )
{
    setname(name);
    model_type = type_name;
    type_part = part;
}


void VpsModel_LinkedList::append( QJsonObject *vps_json, bool ismetal )
{
    VpsModel_Data *newmodel;
    if(ismetal)
        newmodel = new VpsModel_Data( vps_json, true );
    else
        newmodel = new VpsModel_Data( vps_json );
    LinkedList::append( newmodel );
}
void VpsModel_LinkedList::takeSame(QJsonArray *vps_list)
{
    Spider spider;
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
void VpsModel_LinkedList::appendmetal(QJsonArray *vps_list)
{
    Spider spider;
    QJsonArray thisModel (*vps_list);
    QJsonArray non_delete;

    spider.take(  &thisModel, "locations", QJsonValue("sao"), &non_delete ); //删除巴西特供版机型（和其他地区机型相同，但贵%50）
    spider.take(  &thisModel, "locations", QJsonValue(), &non_delete ); //删除可部署地区为空的（不可用机型）
    int liset_size = thisModel.size();
    for( int i = 0; i<liset_size; i++ )
    {
        QJsonObject obj = thisModel.at(i).toObject();
        append( &obj, true );
    }
    qDebug( "metal共%d种可用机型",  size() );
}
VpsModel_LinkedList* VpsModel::at(int num)
{
    if( num<0 ) num=0;
    if( num>=MODEL_LIST_SIZE )num = MODEL_LIST_SIZE-1;
    return AllModelFamilly[ num ];
}
VpsModel_Data *VpsModel::at( int familly, int num  )
{
    VpsModel_LinkedList *traget = this->at( familly );
    if( num<0 ) num=0;
    if( num>=traget->size() )num = traget->size()-1;
    return traget->at(num);
}
VpsModel::VpsModel(  QObject *parent )
{
    Q_UNUSED( parent );
//    updata();
}
void VpsModel::updata()
{
    if( spider_plans == NULL )
    {
        spider_plans = new Spider;
        connect( spider_plans, SIGNAL( reply_ready() ), SLOT( analyze_plans() )   );
        spider_plans->get( "plans" );
    }
    if( spider_metal == NULL )
    {
        spider_metal = new Spider;
        connect( spider_metal, SIGNAL( reply_ready() ), SLOT( analyze_metal() )   );
        spider_metal->get( "plans-metal" );
    }
}
void VpsModel::analyze_plans()
{

    QStringList match_str;

    match_str << "plans";
    QJsonArray *vps_list = new QJsonArray( spider_plans->path( &match_str ).toArray() );
    for( int i=0; i<MODEL_LIST_SIZE-1; i++ )
    {
//        qDebug("moedl-i=%d", i);
        AllModelFamilly[i]->takeSame(vps_list);
    }

    delete spider_plans;
    spider_plans = NULL;
}
void VpsModel::analyze_metal()
{

    QStringList match_str;
    match_str << "plans_metal";
    QJsonArray *metal_list = new QJsonArray(spider_metal->path( &match_str ).toArray());

    AllModelFamilly[MODEL_LIST_SIZE-1]->appendmetal(metal_list);
    delete  spider_metal;
    spider_metal = NULL;

}
