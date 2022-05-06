#ifndef VPSMODEL_LOCATIONS_H
#define VPSMODEL_LOCATIONS_H
#include <QStringList>
#include "linkedlist.h"

enum countryENUM
{
    EAmerican=0, EFrance, EEngland,
    EJapan,  EHolland,
    EcountryMAX
}; //国家枚举

class aircode
{
public:
    QString airport ;  //机场3字代码
    QString cn ;  //对应机场的中文名称
    countryENUM country;
    aircode( QString code, QString translate, countryENUM thecountry);
    ~aircode(){ count--; }
    static int count; //存储到底被实例化多少对象
};
int aircode::count = 0;
class country_familly:public LinkedList<aircode>
{
public:
    country_familly(QString name);
};

class VPSMODEL_LOCATIONS
{
public:
    VPSMODEL_LOCATIONS( ); //传入一个机型可用的所有机场代码
    ~VPSMODEL_LOCATIONS();

    void transfer(QStringList *source);

    country_familly *locations[EcountryMAX];
    int size_locations;
protected:
    country_familly *allfamilly[EcountryMAX];

};

#endif // VPSMODEL_LOCATIONS_H
