#ifndef VPSMODEL_LOCATIONS_H
#define VPSMODEL_LOCATIONS_H
#include <QStringList>
#include "linkedlist.h"

enum countryENUM
{
    EAmerican=0, EFrance, EEngland,
    EJapan,  EHolland,
    Eother
}; //国家枚举

//机场信息类
class airdata
{

public:
    QString airport ;  //机场3字代码
    QString name ;  //对应机场的名称
    countryENUM country;
    airdata( QString code, QString translate, countryENUM thecountry);
    airdata( QString code );
    static int count; //存储到底被实例化多少对象
    ~airdata(){ count--; }
};

//存储所有机场信息
class AirFamilly:public LinkedList<airdata>
{
public:
    AirFamilly(QString name);
    void append(QString code, QString translate, countryENUM thecountry);
    void append( airdata *data );
    void append( QString code );
};

class VPSMODEL_LOCATIONS
{
public:
    VPSMODEL_LOCATIONS( );
    ~VPSMODEL_LOCATIONS();

    void transfer(QStringList *source); //传入一个机型可用的所有机场代码
    AirFamilly *at(int num);
    int size();

protected:
    AirFamilly *transfer_locations[Eother+1]; //保存transfer的查找结果
    AirFamilly *locations[Eother+1]; //指向transfer_locations的非空项目
    int size_locations; //记录上面指针数组的非空数量
    void addtolocations( QString aircode );  //传入一个机场代码，识别并添加到locations
    AirFamilly *all_air = new AirFamilly("all");
};




#endif // VPSMODEL_LOCATIONS_H
