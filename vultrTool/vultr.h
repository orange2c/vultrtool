#ifndef VULTR_H
#define VULTR_H

#include <QString>
#include <QWidget>

#include <spider.h>
#include "vpsmodel.h"
#include "vpsos.h"
#include "vpsinstances.h"


class Vultr: public QObject
{
    Q_OBJECT
public:
    Vultr();
    ~Vultr();

    static QString email;
    static QString username;
    static double Balance;

    bool login(); //测试密钥是否正确
    void set_key( QString key_text );
    void update_message(); //更新个人信息
    void update_model();

    VpsOs *get_os();
    VpsModel *get_model();



protected:
    static QByteArray API_KEY ;
    Spider *spider;
    VpsOs *os ;  //部署新vps可用的os
    VpsModel *model ;



public Q_SLOTS:


};


#endif // VULTR_H
