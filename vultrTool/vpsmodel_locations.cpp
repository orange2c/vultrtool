#include "vpsmodel_locations.h"
int airdata::count = 0;

airdata::airdata( QString code, QString translate, int thecountry)
{
    airport = code;
    name =translate;
    country = thecountry;
    count++;
}
airdata::airdata(QString code)
{
    airport = code;
    name = code;
    country = Eother;
    count++;
}

void AirFamilly::append(QString code, QString translate, int thecountry)
{
    airdata *newdata = new airdata( code, translate, thecountry );
    LinkedList::append(newdata);
}
void AirFamilly::append(airdata *data)
{
    LinkedList::append(data);
}
void AirFamilly::append(QString code)
{
    airdata *newdata = new airdata(code);
    LinkedList::append(newdata);
}
AirFamilly::AirFamilly(QString name)
{
    setname(name);
}
VPSMODEL_LOCATIONS::VPSMODEL_LOCATIONS()
{
    all_air->append("ewr", "纽约", EAmerican);
    all_air->append("ord", "芝加哥", EAmerican);
    all_air->append("ams", "阿姆斯特丹", EHolland);

}
VPSMODEL_LOCATIONS::~VPSMODEL_LOCATIONS()
{

}
int VPSMODEL_LOCATIONS::size()
{
    return size_locations;
}
AirFamilly* VPSMODEL_LOCATIONS::at(int num)
{
    if( num<0 ) num=0;
    if( num>=size_locations ) num = size_locations-1;
    return locations[num];
}
void VPSMODEL_LOCATIONS::addtolocations(QString aircode)
{
    for( int i=0; i<all_air->size(); i++ )
    {
        if( QString::compare( aircode, all_air->at(i)->airport )==0 )
        {
            transfer_locations[ all_air->at(i)->country ]->append( all_air->at(i)  );
            return;
        }
    }
    transfer_locations[Eother]->append(aircode);
}

void VPSMODEL_LOCATIONS::update(QStringList *source)
{
    size_locations = 0; //
    for( int i=0; i<Eother+1; i++ )
    {
        transfer_locations[i]->clear();
    }

    for( int i=0; i< source->size(); i++ )
    {
        addtolocations( source->at(i) );
    }
    int p_locations = 0;
    for( int i=0;i<Eother+1; i++ )
    {
        if( transfer_locations[i]->size() >0 )
        {
            locations[p_locations] = transfer_locations[i];
            p_locations++;
            size_locations++;
        }
    }
    qDebug("american=%d", transfer_locations[EAmerican]->size() );
    qDebug("可用地区为%d", size_locations );

}

//QStringList locations_cn ={ "美国-纽约", "美国-芝加哥", "美国-德克萨斯", "美国-洛杉矶", "美国-亚特兰大",
//                                "荷兰-阿姆斯特丹", "英国-伦敦", "德国-法兰克福", "美国-加利福尼亚", "澳大利亚-悉尼",
//                               "加拿大-多伦多", "法国-巴黎", "日本-东京", "波兰-华沙", "西班牙-马德里",
//                               "韩国-仁川", "美国-迈阿密", "新加坡", "瑞典-斯德哥尔摩", "墨西哥",
//                               "澳大利亚-墨尔本", "美国-西雅图"
//                             };

//QStringList locations_en = { "ewr","ord","dfw","lax","atl",
//                                "ams","lhr","fra","sjc","syd",
//                                "yto","cdg","nrt","waw","mad",
//                                "icn","mia","sgp","sto","mex",
//                                "mel", "sea"
//                               };
//countryENUM locations_country[] = { EAmerican, EAmerican, EAmerican, EAmerican, EAmerican

//                                };

//        QStringList *locations = new QStringList();
//        int j=0;
//        for( int i = 0; i<source->size(); i++ )
//        {
//            for( j=0; j<locations_en.size(); j++ )
//            {

//                if( QString::compare( source->at(i), locations_en.at(j) ) == 0 )
//                {
//                    locations->append( locations_cn.at(j) ); //
//                    locations_cn.removeAt(j);
//                    locations_en.removeAt(j); //删除查找到的项，下次查找时就能减少时间
//                    break;
//                }
//                else if( j == locations_en.size()-1 )//即遍历到数组最后一个也没找到匹配的
//                {
//                    locations->append( source->at(i) ); //则原样返回
//                }
//            }

//        }

//}
//VPSMODEL_LOCATIONS::~VPSMODEL_LOCATIONS()
//{
//    for(int i=0; i<EcountryMAX; i++ )
//        delete allfamilly[i];
//}


