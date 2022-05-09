#ifndef VPSMODEL_H
#define VPSMODEL_H

#include <QObject>
#include <QString>

#include "spider.h"
#include "linkedlist.h"
#include "vpsmodel_locations.h"


class VPSMODE_DATA
{
public:
    VPSMODE_DATA( QJsonObject *vps_json );
    ~VPSMODE_DATA();
    QString model_id();
    QString introduce();
    VPSMODEL_LOCATIONS *local = new VPSMODEL_LOCATIONS();

protected:
    QString *introduceP = NULL ;
    QStringList *location_strlist = NULL ;

    QString id;
    int type = 0;
    int vcpu_count;
    int ram = 0;
    int disk = 0;
    int disk_count = 0;
    int bandwidth = 0;
    double monthly_cost = 0;
    double minuter_cost = 0;
};

class VModelFamilly: public LinkedList< VPSMODE_DATA >
{
public:
    VModelFamilly( QString name, QString type_name, QString part="" );
    void takeSame(QJsonArray *vps_list); //传入json数组，将所有与model_type相同的都取走

    void append( QJsonObject *vps_json );
protected:
    QString model_type; //takesame时会比对type项是否为此值
    QString type_part=""; //如果此值非空，则takesame时也会匹配此值是否在id项目中
};

class VPSMODEL
{
public:
    void update(); //更新可用机型
    VModelFamilly *at(int num); //从AllModelFamilly中返回


protected:

#define  MODEL_LIST_SIZE  8
    VModelFamilly *AllModelFamilly[MODEL_LIST_SIZE] = {
        //目前可用类型
        new VModelFamilly("云电脑", "vc2"),
//        new VModelFamilly("专用云", "vdc"),
        new VModelFamilly("高频计算", "vhf"),
        new VModelFamilly("高性能amd", "vhp", "amd"),
        new VModelFamilly("高性能intel", "vhp", "intel"),
        new VModelFamilly("通用优化", "voc", "voc-g"),
        new VModelFamilly("cpu优化", "voc", "voc-c"),
        new VModelFamilly("内存优化", "voc", "voc-m"),
        new VModelFamilly("存储优化", "voc", "voc-s"),

    };
};

#endif // VPSMODEL_H
