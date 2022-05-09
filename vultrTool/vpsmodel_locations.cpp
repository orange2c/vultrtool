#include "vpsmodel_locations.h"
int LOCATION_DATA::count = 0;

LOCATION_DATA::LOCATION_DATA( QString code, QString translate, int thecountry)
{
    airport = code;
    name =translate;
    country = thecountry;
    count++;
}
LOCATION_DATA::LOCATION_DATA(QString code)
{
    airport = code;
    name = code;
    country = Eother;
    count++;
}

void AirFamilly::append(QString code, QString translate, int thecountry)
{
    LOCATION_DATA *newdata = new LOCATION_DATA( code, translate, thecountry );
    LinkedList::append(newdata);
}
void AirFamilly::append(LOCATION_DATA *data)
{
    LinkedList::append(data);
}
void AirFamilly::append(QString code)
{
    LOCATION_DATA *newdata = new LOCATION_DATA(code);
    LinkedList::append(newdata);
}
AirFamilly::AirFamilly(QString name)
{
    setname(name);
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

VPSMODEL_LOCATIONS::VPSMODEL_LOCATIONS()
{
    all_air->append("ewr", "纽约", EAmerican);
    all_air->append("ord", "芝加哥", EAmerican);
    all_air->append("dfw", "达拉斯", EAmerican);
    all_air->append("lax", "洛杉矶", EAmerican);
    all_air->append("atl", "亚特兰大", EAmerican);

    all_air->append("ams", "阿姆斯特丹", EHolland);
    all_air->append("lhr", "伦敦", EEngland);
    all_air->append("fra", "法兰克福", EGermany);
    all_air->append("sjc", "加利福尼亚", EAmerican);
    all_air->append("syd", "悉尼", EAustralia);

    all_air->append("yto", "多伦多", ECanada);
    all_air->append("cdg", "巴黎", EFrance);
    all_air->append("nrt", "东京", EJapan);
    all_air->append("waw", "华沙", EPoland);
    all_air->append("mad", "马德里", ESpain);


    all_air->append("icn", "仁川", EKorea);
    all_air->append("mia", "迈阿密", EAmerican);
    all_air->append("sgp", "新加坡", ESingapore);
    all_air->append("sto", "斯德哥尔摩", ESweden);
    all_air->append("mex", "墨西哥城", EMexico);

    all_air->append("mel", "墨尔本", EAustralia);
    all_air->append("sea", "西雅图", EAmerican);


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


