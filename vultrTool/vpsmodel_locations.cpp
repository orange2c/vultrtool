#include "vpsmodel_locations.h"
int Locatiom_Data::count = 0;

Locatiom_Data::Locatiom_Data( QString code, QString translate, int thecountry)
{
    airport = code;
    name =translate;
    country = thecountry;
    count++;
}
Locatiom_Data::Locatiom_Data(QString code)
{
    airport = code;
    name = code;
    country = Eother;
    count++;
}

void Location_LinkedList::append(QString code, QString translate, int thecountry)
{
    Locatiom_Data *newdata = new Locatiom_Data( code, translate, thecountry );
    LinkedList::append(newdata);
}
void Location_LinkedList::append(Locatiom_Data *data)
{
    LinkedList::append(data);
}
void Location_LinkedList::append(QString code)
{
    Locatiom_Data *newdata = new Locatiom_Data(code);
    LinkedList::append(newdata);
}
Location_LinkedList::Location_LinkedList(QString name)
{
    setname(name);
}

VpsModel_Locations::VpsModel_Locations()
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
    all_air->append("hnl", "火奴鲁鲁", EAmerican);
    all_air->append("bom", "孟买", EIndia);


}
VpsModel_Locations::~VpsModel_Locations()
{

}
int VpsModel_Locations::size()
{
    return size_locations;
}
Location_LinkedList* VpsModel_Locations::at(int num)
{
    if( num<0 ) num=0;
    if( num>=size_locations ) num = size_locations-1;
    return locations[num];
}
void VpsModel_Locations::addtolocations(QString aircode)
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

void VpsModel_Locations::update(QStringList *source)
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
//    qDebug("american=%d", transfer_locations[EAmerican]->size() );
//    qDebug("可用地区为%d", size_locations );

}

