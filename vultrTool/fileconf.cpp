#include "fileconf.h"

FileConf::FileConf()
{
    qDebug("%s", qPrintable( QCoreApplication::applicationDirPath()));
    load();
}

int FileConf::load()
{
    QFile file(FILENAME);
    if( jtext != NULL )
    {
        delete jtext;
        jtext = NULL;
    }

    if( file.exists() )
    {

        file.open(QIODevice::ReadOnly);
        QString file_text( file.readAll() );

        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(file_text.toUtf8(), &jsonError);

        if (jsonError.error == QJsonParseError::NoError && !doc.isNull()) {
            jtext = new QJsonObject( doc.object() );
        }

        return 0;
    }
    else
    {
        jtext = new QJsonObject();
    }
    return -1;
}
QString FileConf::read(QString key)
{
    if( load() >= 0 ) //载入配置文件
        if( jtext != NULL )
            return jtext->value( key ).toString();
    return "";

}

void FileConf::write(QString key, QString value)
{

    if( jtext != NULL )
        jtext->insert(key,value);
}


void FileConf::save()
{
    if( jtext == NULL )
        return;
    QJsonDocument doc( *jtext );
    QFile file(FILENAME);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

QString FileConf::read_apikey()
{
    if( load()<0 ) //载入配置文件
        return "";
    qDebug("检查apikey");
    return read(JNAME_APIKEY);
}
void FileConf::write_apikey(QString apikey)
{
    load();
    write( JNAME_APIKEY, apikey);
    save();
}
