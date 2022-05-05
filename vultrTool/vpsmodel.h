#ifndef VPSMODEL_H
#define VPSMODEL_H

#include <QObject>
#include "spider.h"
#include <QString>



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

class VModelFamilly
{
public:
    VModelFamilly();
    ~VModelFamilly();
    void append( VPSMODEL *model );
    void append( QJsonObject *vps_json );
    VPSMODEL *at(int num);
    int size();
protected:
    int size_p = 0;  //有多少成员
    struct linked_list
    {
        VPSMODEL *data;
        linked_list *next;
    };
    linked_list *first=NULL;
    linked_list *last;

};

#endif // VPSMODEL_H
