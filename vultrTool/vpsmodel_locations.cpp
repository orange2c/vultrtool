#include "vpsmodel_locations.h"



//QStringList VPSMODEL_LOCATIONS::countryNAME = {
//    "美国", "法国", "英国",
//    "日本", "荷兰"
//};

//airport VPSMODEL_LOCATIONS::find_aircode( QString code)
//{
//    airport all_aircode[5];
//    all_aircode[0] = {.aircode="ewr",.country=Amreican,.translate="纽约"};


//}




//VPSMODEL_LOCATIONS::VPSMODEL_LOCATIONS()
//{

//}

//struct airport all[]=
//{
//    {.aircode="ewr", .translate="纽约",   },
//    {.aircode="ord", .translate="芝加哥" },
//};

//aircode::aircode( QString code, QString translate, countryENUM thecountry)
//{
//    airport = code;
//    cn =translate;
//    country = thecountry;
//    count++;
//}


//country_familly::country_familly(QString name)
//{
//    setname(name);
//}


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

//void VPSMODEL_LOCATIONS::transfer( QStringList *source )
//{

//    aircode all_air[]={
//        aircode( "pwr","s", EAmerican ),

//    };

//    all_air[0].country = EAmerican ;


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


