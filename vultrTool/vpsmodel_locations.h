#ifndef VPSMODEL_LOCATIONS_H
#define VPSMODEL_LOCATIONS_H
#include <QStringList>
#include "linkedlist.h"


//机场信息类
class Locatiom_Data
{

public:
    QString airport ;  //机场3字代码
    QString name ;  //对应机场的名称
    int country;
    Locatiom_Data( QString code, QString translate, int thecountry);
    Locatiom_Data( QString code );
    static int count; //存储到底被实例化多少对象
    ~Locatiom_Data(){ count--; }
};

//存储所有机场信息
class Location_LinkedList:public LinkedList<Locatiom_Data>
{
public:
    Location_LinkedList(QString name);
    void append(QString code, QString translate, int thecountry);
    void append( Locatiom_Data *data );
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
#define EIndia      14

#define Eother     15


class VpsModel_Locations
{
public:
    VpsModel_Locations( );
    ~VpsModel_Locations();

    void update(QStringList *source); //传入一个机型可用的所有机场代码,自动识别分类存储到本类
    Location_LinkedList *at(int num);
    int size();

protected:
    Location_LinkedList *locations[Eother+1]; //指向transfer_locations的非空项目
    int size_locations; //记录上面指针数组的非空数量
    void addtolocations( QString aircode );  //传入一个机场代码，识别并添加到locations
    Location_LinkedList *all_air = new Location_LinkedList("all");

    Location_LinkedList *transfer_locations[Eother+1]=
    { //保存transfer的查找结果
        new Location_LinkedList("美国"),
        new Location_LinkedList("法国"),
        new Location_LinkedList("英国"),
        new Location_LinkedList("日本"),
        new Location_LinkedList("荷兰"),
        new Location_LinkedList("德国"),
        new Location_LinkedList("澳大利亚"),
        new Location_LinkedList("加拿大"),
        new Location_LinkedList("波兰"),
        new Location_LinkedList("西班牙"),
        new Location_LinkedList("韩国"),
        new Location_LinkedList("新加坡"),
        new Location_LinkedList("瑞典"),
        new Location_LinkedList("墨西哥"),
        new Location_LinkedList("印度"),
        new Location_LinkedList("无翻译")
        };
};




#endif // VPSMODEL_LOCATIONS_H
