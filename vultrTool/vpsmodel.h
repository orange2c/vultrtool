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
    int monthly_cost = 0;
};

class VModelFamilly: public LinkedList< VPSMODE_DATA >
{
public:
    VModelFamilly( QString name, QString type_name );
    void takeSame(QJsonArray *vps_list); //传入json数组，将所有与model_type相同的都取走

    void append( QJsonObject *vps_json );
protected:
    QString model_type;
};

class VPSMODEL
{
public:
    void update(); //更新可用机型
    VModelFamilly *at(int num);
protected:

#define  MODEL_LIST_SIZE  2
    VModelFamilly *AllModelFamilly[MODEL_LIST_SIZE] = {
        //目前可用类型
        new VModelFamilly("云电脑", "vc2"),
        new VModelFamilly("vhf云电脑", "vhf"),

    };
};

#endif // VPSMODEL_H
