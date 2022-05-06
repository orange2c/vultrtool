#ifndef VPSMODEL_H
#define VPSMODEL_H

#include <QObject>
#include <QString>

#include "spider.h"
#include "linkedlist.h"
#include "vpsmodel_locations.h"


class VPSMODEL
{
public:
    VPSMODEL( QJsonObject *vps_json );
    ~VPSMODEL();
    QString model_id();
    QString introduce();
    QStringList locationsCN();
    QStringList locationsEN();

protected:
    QString id;
    int type = 0;
    int vcpu_count;
    int ram = 0;
    int disk = 0;
    int disk_count = 0;
    int bandwidth = 0;
    int monthly_cost = 0;
    QString *introduceP = NULL ;
    QStringList *locationsCNp = NULL ;
    QStringList *locationsENp = NULL ;


};

class VModelFamilly: public LinkedList_core
{
public:
    VModelFamilly();
    ~VModelFamilly();

    VPSMODEL *at(int num);
    void append( VPSMODEL *model );
    void append( QJsonObject *vps_json );

protected:


};

#endif // VPSMODEL_H
