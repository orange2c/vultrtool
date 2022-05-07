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
    VModelFamilly();
    VModelFamilly( QString name, QString type_name );
    void append( QJsonObject *vps_json );
protected:
    QString model_type;
};

class VPSMODEL
{
protected:

#define  OS_LIST_SIZE  8
    VModelFamilly *OSlist[OS_LIST_SIZE] = {
        //目前可用os类型
        new VModelFamilly("云电脑", "vc2"),

    };
};

#endif // VPSMODEL_H
