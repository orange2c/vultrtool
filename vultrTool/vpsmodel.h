#ifndef VPSMODEL_H
#define VPSMODEL_H

#include <QObject>
#include <QString>

#include "spider.h"
#include "linkedlist.h"
#include "vpsmodel_locations.h"


class VpsModel_Data
{
public:
    VpsModel_Data( QJsonObject *vps_json, bool ismetal=false );
    ~VpsModel_Data();
    QString model_id();
    QString cost_month();
    QString introduce();
    VpsModel_Locations *location = new VpsModel_Locations();

protected:
    QString *introduceP = NULL ;
    QStringList *location_strlist = NULL ;

    QString id;
    QString type;
    int vcpu_count;
    int ram = 0;
    int disk = 0;
    int disk_count = 0;
    int bandwidth = 0;
    double monthly_cost = 0;
    double minuter_cost = 0;

    bool is_metal_model = false ;
    int cpu_count = 0;
    int cpu_threads = 8;
    QString cpu_model;

};

class VpsModel_LinkedList: public LinkedList< VpsModel_Data >
{
public:
    VpsModel_LinkedList( QString name, QString type_name, QString part="" );
    void takeSame(QJsonArray *vps_list); //传入json数组，将所有与model_type相同的都取走
    void appendmetal( QJsonArray *vps_list );
    void append( QJsonObject *vps_json, bool ismetal=false );
protected:
    QString model_type; //takesame时会比对type项是否为此值
    QString type_part=""; //如果此值非空，则takesame时也会匹配此值是否在id项目中
};


class VpsModel : public QObject
{
    Q_OBJECT
public:
    explicit VpsModel( QObject *parent = 0 );
    void updata(); //更新可用机型
    VpsModel_LinkedList *at(int num); //从AllModelFamilly中返回
    VpsModel_Data *at( int familly, int num  );
    VpsModel_LinkedList metal( int num );
public slots:
    void analyze_plans();
    void analyze_metal();

protected:
    Spider *spider_plans = NULL;
    Spider *spider_metal = NULL; //在updata调用时new，在槽内处理完数据就delete

#define  MODEL_LIST_SIZE  9
    VpsModel_LinkedList *AllModelFamilly[MODEL_LIST_SIZE] = {
        //目前可用类型
        new VpsModel_LinkedList("云电脑", "vc2"),
//        new VModelFamilly("专用云", "vdc"),
        new VpsModel_LinkedList("高频计算", "vhf"),
        new VpsModel_LinkedList("高性能amd", "vhp", "amd"),
        new VpsModel_LinkedList("高性能intel", "vhp", "intel"),
        new VpsModel_LinkedList("通用优化", "voc", "voc-g"),
        new VpsModel_LinkedList("cpu优化", "voc", "voc-c"),
        new VpsModel_LinkedList("内存优化", "voc", "voc-m"),
        new VpsModel_LinkedList("存储优化", "voc", "voc-s"),

        new VpsModel_LinkedList("metal", "", ""),

    };
};

#endif // VPSMODEL_H
