
#include "vultr.h"
#include <QString>
#include <map>

#include <QObject>
#include <spider.h>

QString Vultr::email = "0";
QString Vultr::username = "NULL";
double Vultr::Balance = 0.0;
QByteArray Vultr::API_KEY = NULL;

Vultr::Vultr()
{
    spider = new Spider( &API_KEY );
    os = new VpsOs;
    model = new VpsModel;
    instances = new VpsInstances;

}
Vultr::~Vultr()
{
    delete spider;
    delete os;
    delete model;
    delete instances;
}
VpsModel *Vultr::get_model()
{
    return model;
}
VpsOs *Vultr::get_os()
{
    return os;
}

void Vultr::set_key(QString key_text)
{
    if( API_KEY.size()>0 ) API_KEY.clear();
    API_KEY.append( key_text);
}



bool Vultr::login()
{
    os->update();
    model->updata();
    instances->updata();
    update_message();
    if( this->email.size()>1 )
    {
        return true;
    }
    else
    {
        return false;
    }

}

void Vultr::update_message()
{
    spider->get( "account" );
    QStringList match_str;

    match_str << "account" <<"email";
    email.clear();
    email = spider->path( &match_str).toString();

    match_str<< "account" << "name"; //match函数内会清空本qstringlist
    username.clear();
    username = spider->path( &match_str ).toString();

    match_str<< "account" << "balance"; //match函数内会清空本qstringlist
     Balance = spider->path( &match_str ).toDouble();

     double pending;
     match_str<< "account" << "pending_charges"; //match函数内会清空本qstringlist
     pending =  spider->path( &match_str).toDouble();
     Balance = 0-( pending + Balance );

}



