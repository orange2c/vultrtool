#ifndef VPSINSTANCES_H
#define VPSINSTANCES_H

#include <QObject>
#include "spider.h"
#include "linkedlist.h"


class VpsInstances_Data
{

};

class VpsInstances : public QObject
{
    Q_OBJECT
public:
    explicit VpsInstances(QObject *parent = nullptr);
    void updata();

signals:

};

#endif // VPSINSTANCES_H
