
#include "vultr.h"
#include <QString>
#include <map>

#include <QObject>
#include <spider.h>

QByteArray* VULTR::API_KEY = NULL;
VULTR::VULTR()
{
    spider = new SPIDER( this->API_KEY );
    QObject::connect( spider, SIGNAL(log(QString)), this, SLOT(log_Transfer(QString)) );
    OSlist[0] = new VOsFamilly("ubuntu");
    OSlist[1] = new VOsFamilly("ubuntu");
}
VULTR::~VULTR()
{
    delete vc2;
    delete spider;
    int OSlist_size = sizeof(OSlist) / sizeof(OSlist[0]);
    for( int i=0; i<OSlist_size; i++)
    {
        delete OSlist[i];
    }
}

void VULTR::log_Transfer( QString log_text )
{
    emit log( log_text );
}

bool VULTR::login()
{
    spider->get( "account" );
    QStringList match_str = {"account","email"};
    if(  spider->path( &match_str ).toString() != NULL )
    {
        emit log( "密钥正确" );
        return true;
    }
    else
    {
        emit log( "密钥错误" );
        return false;
    }

}

void VULTR::update_message()
{
    emit log("更新vultr信息...");
    spider->get( "account" );
    QStringList match_str;

    match_str << "account" <<"email";
    email = spider->path( &match_str).toString();
    emit log(email);

    match_str<< "account" << "name"; //match函数内会清空本qstringlist
    username = spider->path( &match_str ).toString();
    emit log(username);


    match_str<< "account" << "balance"; //match函数内会清空本qstringlist
     Balance = spider->path( &match_str ).toDouble();

     double pending;
     match_str<< "account" << "pending_charges"; //match函数内会清空本qstringlist
     pending =  spider->path( &match_str).toDouble();
      Balance = 0-( pending + Balance );
}


void VULTR::update_model()
{
    emit log("更新可购买vps列表...");
    spider->get( "plans" );
    QStringList match_str;

    match_str << "plans";
    QJsonArray *vps_list = new QJsonArray(spider->path( &match_str ).toArray());
    QJsonArray *vc2_json = new QJsonArray();


    emit log("take vc2");
    spider->take( vps_list, "type", QJsonValue("vc2"), vc2_json ); //将所有vc2机型的信息json，都提取出来
    QJsonArray non_delete;
    spider->take(  vc2_json, "locations", QJsonValue("sao"), &non_delete ); //删除巴西特供版机型（和其他地区机型相同，但贵%50）
    spider->take(  vc2_json, "locations", QJsonValue(), &non_delete ); //删除可部署地区为空的（不可用机型）

    int liset_size = vc2_json->size();

    for( int i = 0; i<liset_size; i++ )
    {
        QJsonObject obj = vc2_json->at(i).toObject();
        vc2->append( &obj );

    }
    qDebug( "vc2共%d种可用机型",vc2->size() );

    spider->get("os");
    match_str << "os";
    QJsonArray os_all_json = spider->path( &match_str ).toArray();

    VOsFamilly *os_all = new VOsFamilly("all");



    for( int i=0; i<os_all_json.size(); i++ )
    {
        qDebug("find" );
        QJsonObject os_json = os_all_json.at(i).toObject();
        os_all->append( &os_json );
    }
    int i =5;
    while (i < os_all->size()) {

        qDebug("i=%d,id=%d", i, os_all->at(i)->id);
        if( OSlist[0]->appendSame( os_all->at(i) ) )
        {
            os_all->deleteat(i);
            qDebug("匹配成功");
            qDebug("ubuntu成员有%d", OSlist[0]->size());
        }
         i++;
    }
//        OSlist->at(0)->appendSame( os_all->at(20) );

    qDebug("os size=%d",os_all->size() );
    delete os_all;
}
