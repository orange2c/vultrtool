#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>

#include <QEventLoop>
#include <QTimer>

class SPIDER : public QObject
{
    Q_OBJECT

public:
    SPIDER(); //不传入key，可使用各种匹配函数等
    SPIDER( QByteArray *KEY ); //传入key，才能使用发出get请求的功能
    ~SPIDER( );
    QNetworkAccessManager *NetManager;

    void get(QString path);
    QJsonValue path( QStringList *list );  //从上一次通信所接收的json中，根据list的规则匹配,适用于寻找被多层嵌套的属性
    static QJsonValue path( QJsonObject *obj,  QString type );  //从obj中返回type属性的值
    void take( QJsonArray *text, QString type, QJsonValue value, QJsonArray *ReturnValue );   //从text中，将type为value的所有项目，剪切组成新的数组，保存起来
//    void take( QJsonArray *text, QString type, QJsonArray value, QJsonArray *ReturnValue );   //适用于type是个json数组，匹配
    QJsonArray *match( QJsonArray *text, QString type, QJsonValue value );   //从text中，寻找type为value的所有项目
protected:
    QByteArray *API_KEY ;
    QJsonObject *replyJson = NULL;  //指向用于存放get返回的json数据的内存
    bool is_wait_reply = 0;

    void waiting_reply();
    QJsonValue _recursive_find(  QJsonObject *obj, QStringList *match_list );  //递归查找某项目，供path函数调用


public Q_SLOTS:
    void reply_slot( QNetworkReply *reply );
signals:
    void log( QString log_text );

};

#endif // SPIDER_H
