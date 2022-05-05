#ifndef VPSMODEL_LOCATIONS_H
#define VPSMODEL_LOCATIONS_H
#include <QStringList>


enum countryENUM
{
    Amreican=0, France, England,
    Japan,  Holland,
}; //国家枚举

struct airport
{
    QString aircode;  //机场3字代码
    countryENUM country;  //归属国家
    QString translate;  //对应机场的中文名称
};


class VPSMODEL_LOCATIONS
{
public:
    VPSMODEL_LOCATIONS();
protected:
    static QStringList countryNAME;
    airport find_aircode( QString code);

};

#endif // VPSMODEL_LOCATIONS_H
