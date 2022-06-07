#ifndef VPSINSTANCES_H
#define VPSINSTANCES_H

#include <QObject>
#include "spider.h"
#include "linkedlist.h"


class VpsInstances_Data
{
protected:
    QString *id = NULL;
    QString *ip = NULL;
};

class VpsInstances : public QObject
{
    Q_OBJECT
public:
    explicit VpsInstances(QObject *parent = nullptr);
    void updata();
protected:
    Spider *spider = NULL ;

signals:
public slots:
    void reply_instances();

};

#endif // VPSINSTANCES_H
