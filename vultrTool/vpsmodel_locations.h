#ifndef VPSMODEL_LOCATIONS_H
#define VPSMODEL_LOCATIONS_H
#include <QStringList>
#include "linkedlist.h"


//机场信息类
class LOCATION_DATA
{

public:
    QString airport ;  //机场3字代码
    QString name ;  //对应机场的名称
    int country;
    LOCATION_DATA( QString code, QString translate, int thecountry);
    LOCATION_DATA( QString code );
    static int count; //存储到底被实例化多少对象
    ~LOCATION_DATA(){ count--; }
};

//存储所有机场信息
class AirFamilly:public LinkedList<LOCATION_DATA>
{
public:
    AirFamilly(QString name);
    void append(QString code, QString translate, int thecountry);
    void append( LOCATION_DATA *data );
    void append( QString code );
};

#define EAmerican    0
#define EFrance     1
#define EEngland    2
#define EJapan     3
#define EHolland     4
#define EGermany    5
#define EAustralia  6

#define ECanada     7
#define EPoland     8
#define ESpain      9
#define EKorea      10
#define ESingapore  11
#define ESweden     12
#define EMexico     13


#define Eother     14


class VPSMODEL_LOCATIONS
{
public:
    VPSMODEL_LOCATIONS( );
    ~VPSMODEL_LOCATIONS();

    void update(QStringList *source); //传入一个机型可用的所有机场代码
    AirFamilly *at(int num);
    int size();

protected:
    AirFamilly *locations[Eother+1]; //指向transfer_locations的非空项目
    int size_locations; //记录上面指针数组的非空数量
    void addtolocations( QString aircode );  //传入一个机场代码，识别并添加到locations
    AirFamilly *all_air = new AirFamilly("all");

    AirFamilly *transfer_locations[Eother+1]=
    { //保存transfer的查找结果
        new AirFamilly("美国"),
        new AirFamilly("法国"),
        new AirFamilly("英国"),
        new AirFamilly("日本"),
        new AirFamilly("荷兰"),
        new AirFamilly("德国"),
        new AirFamilly("澳大利亚"),
        new AirFamilly("加拿大"),
        new AirFamilly("波兰"),
        new AirFamilly("西班牙"),
        new AirFamilly("韩国"),
        new AirFamilly("新加坡"),
        new AirFamilly("瑞典"),
        new AirFamilly("墨西哥"),
        new AirFamilly("无翻译")
        };
};




#endif // VPSMODEL_LOCATIONS_H
