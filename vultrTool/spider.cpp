#include "spider.h"
QByteArray* SPIDER::API_KEY = NULL;

SPIDER::SPIDER(  )
{
}

SPIDER::SPIDER( QByteArray *KEY )
{
    API_KEY = KEY;
}

SPIDER::~SPIDER()
{
    delete NetManager;
    if( replyJson != NULL)
        delete  replyJson;
}


void SPIDER::reply_slot(QNetworkReply *reply)
{
    is_wait_reply = 0;

    QNetworkReply::NetworkError err = reply->error();

    QByteArray  reply_data = reply->readAll();
    emit log( reply_data );
    reply->deleteLater();

    if(err != QNetworkReply::NoError)
    {
        emit log( "NetWork ERROR:" + reply->errorString() );
        replyJson = NULL;
        return;
    }

    if(err != QNetworkReply::NoError)
    {
        emit log( "NetWork ERROR:" + reply->errorString() );
        replyJson = NULL;
    }
    QJsonParseError json_error;
    QJsonDocument doucment = QJsonDocument::fromJson(reply_data, &json_error);
    if (json_error.error == QJsonParseError::NoError)
        if (doucment.isObject())
        {
            if( replyJson != NULL )
            {
                delete replyJson;
                replyJson = NULL;
            }
            replyJson = new QJsonObject(doucment.object());
        }

}
QJsonValue SPIDER::_recursive_find( QJsonObject *obj, QStringList *match_list )
{
    emit log("matching:"+match_list->at(0));
    if (obj->contains(match_list->at(0)))
    {
        if( match_list->size()>1 )
        {
            QJsonObject obj_next = obj->value(match_list->at(0)).toObject() ;
            match_list->removeFirst();
            return _recursive_find( &obj_next, match_list );
        }
        else
        {
            QJsonValue value_str = obj->value(match_list->at(0));
            match_list->clear();
            return value_str;
        }
      }
    else
      {
            return "Not Find";
      }
    return "Not Find";
}
void SPIDER::waiting_reply()
{
    if( is_wait_reply == 1 )
    {
        QEventLoop eventLoop;
        connect(NetManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        eventLoop.exec();  //等待直到网络通讯完成
    }
}
QJsonValue SPIDER::path( QStringList *list )
{
    waiting_reply();
    if( replyJson == NULL )
    {
        return QJsonValue("");  //返回一个空串，防止后面程序出错
    }
    return  _recursive_find( replyJson, list );
}
QJsonValue SPIDER::path( QJsonObject *obj,  QString type )
{
    if (obj->contains(type))
    {
         return obj->value(type);
    }
    else
    {
        return "Not Find";
    }
}
void SPIDER::take(QJsonArray *text, QString type, QJsonValue value, QJsonArray *ReturnValue, QString type2, QJsonValue part)
{
    if( value.isString() )
    {
        emit log("isString");
        QString take_value = value.toString();
        QString part_value = part.toString();
        bool half_match =false;
        if( part_value.size()>0 ) //如果第二部分半匹配存在参数
        {
            half_match =true;
        }
        emit log(take_value);
        int i = 0;

        while( i<= text->size()-1 )
        {
            QJsonValue text_take_value = text->at(i).toObject().value(type) ;
            QJsonValue text_part_value = text->at(i).toObject().value(type2) ;
            QString take_traget;
            QString part_traget = text_part_value.toString() ;

//            QJsonValue text_value
            if( text_take_value.isString() )
            {
                take_traget.append(text_take_value.toString()) ;
            }
            else if( text_take_value.isArray() )
            {
                take_traget.append(text_take_value.toArray().at(0).toString()) ;
            }



            if( QString::compare( take_traget, take_value ) == 0 )
            {
                if( half_match )
                {
                    if( part_traget.contains( part_value ))
                    {
                        ReturnValue->append( text->at(i) );
                        text->removeAt(i);
                    }
                    else
                        i++;
                }
                else
                {
                    ReturnValue->append( text->at(i) );
                    text->removeAt(i);
                }
            }
            else
                i++;
        }
    }
    else if( value.isNull() )
    {
        int i = 0;
        while( i<= text->size()-1 )
        {
            QJsonValue text_value = text->at(i).toObject().value(type) ;
            QJsonValue traget;

            if( text_value.isNull() )
            {
                ReturnValue->append( text->at(i) );
                text->removeAt(i);
            }
            else if( text_value.isArray() && text_value.toArray().size()<1  )
            {
                ReturnValue->append( text->at(i) );
                text->removeAt(i);
            }
            else
                i++;
        }
    }


}



void SPIDER::get(QString path)
{
    QObject::connect(NetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(reply_slot(QNetworkReply*)) );

    QUrl api_path ("https://api.vultr.com/v2/" + path );
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    request.setUrl(api_path);

    emit log(api_path.toDisplayString());
    emit log( *API_KEY );

    QSslConfiguration config;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);

    QByteArray author;
    author.append("Bearer ");
    author.append( *API_KEY );
    request.setRawHeader("Authorization", author);

    NetManager->get(request);
    is_wait_reply = 1;

}
