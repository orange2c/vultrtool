
#include "vpsmodel.h"

QStringList *location_transfer(QStringList *source)
{
    QStringList locations_cn ={ "美国-纽约", "美国-芝加哥", "美国-德克萨斯", "美国-洛杉矶", "美国-亚特兰大",
                                "荷兰-阿姆斯特丹", "英国-伦敦", "德国-法兰克福", "美国-加利福尼亚", "澳大利亚-悉尼",
                               "加拿大-多伦多", "法国-巴黎", "日本-东京", "波兰-华沙", "西班牙-马德里",
                               "韩国-仁川", "美国-迈阿密", "新加坡", "瑞典-斯德哥尔摩", "墨西哥",
                               "澳大利亚-墨尔本", "美国-西雅图"
                             };

    QStringList locations_en = { "ewr","ord","dfw","lax","atl",
                                "ams","lhr","fra","sjc","syd",
                                "yto","cdg","nrt","waw","mad",
                                "icn","mia","sgp","sto","mex",
                                "mel", "sea"
                               };

    QStringList *locations = new QStringList();
    int j=0;
    for( int i = 0; i<source->size(); i++ )
    {


        for( j=0; j<locations_en.size(); j++ )
        {


            if( QString::compare( source->at(i), locations_en.at(j) ) == 0 )
            {
                locations->append( locations_cn.at(j) ); //
                locations_cn.removeAt(j);
                locations_en.removeAt(j); //删除查找到的项，下次查找时就能减少时间
                break;
            }
            else if( j == locations_en.size()-1 )//即遍历到数组最后一个也没找到匹配的
            {
                locations->append( source->at(i) ); //则原样返回
            }
        }

    }
//    qSort( *locations);
    return locations;

}

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

    locationsCNp = location_transfer(locationsENp);

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
QStringList VPSMODEL::locationsCN()
{
    return QStringList(*locationsCNp);
}
QStringList VPSMODEL::locationsEN()
{
    return QStringList(*locationsENp);
}
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


