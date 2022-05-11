
#include "vultr.h"
#include <QString>
#include <map>

#include <QObject>
#include <spider.h>

QString VULTR::email = "0";
QString VULTR::username = "NULL";
double VULTR::Balance = 0.0;
QByteArray VULTR::API_KEY = NULL;

VULTR::VULTR()
{
    spider = new SPIDER( &API_KEY );
    QObject::connect( spider, SIGNAL(log(QString)), this, SLOT(log_Transfer(QString)) );
}
VULTR::~VULTR()
{
    delete spider;
    delete os;
}
void VULTR::set_key(QString key_text)
{
    if( API_KEY.size()>0 ) API_KEY.clear();
    API_KEY.append( key_text);
}

void VULTR::log_Transfer( QString log_text )
{
    emit log( log_text );
}

bool VULTR::login()
{
    update_message();
    if( this->email.size()>1 )
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
    email.clear();
    email = spider->path( &match_str).toString();
    emit log(email);

    match_str<< "account" << "name"; //match函数内会清空本qstringlist
    username.clear();
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

    //获取可用os信息
    os->update();
    model->update();

}
