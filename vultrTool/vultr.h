#ifndef VULTR_H
#define VULTR_H

#include <QString>
#include <QWidget>

#include <spider.h>
#include "vpsmodel.h"
#include "vpsos.h"


class VULTR: public QObject
{
    Q_OBJECT
public:
    VULTR();
    ~VULTR();

    bool login(); //测试密钥是否正确
    static void set_key( QByteArray *key ){ if(key!=NULL) delete API_KEY; API_KEY = new QByteArray(*key);}

    void update_message(); //更新个人信息
    void update_model();

    QString email;
    QString username;
    double Balance;

    VModelFamilly *vc2 = new VModelFamilly();
    VOsFamilly *OSlist[3] ;

protected:
    static QByteArray *API_KEY ;
    SPIDER *spider;



public Q_SLOTS:
    void log_Transfer( QString log_text );

signals:
    void log( QString log_text );

};

#endif // VULTR_H
