#include "fileconf.h"

FileConf::FileConf()
{
    qDebug("%s", qPrintable( QCoreApplication::applicationDirPath()));

    QFile file(FILENAME);
    flag_exist = file.exists();

    if( flag_exist )
    {
        file.open(QIODevice::ReadOnly);
        QString file_text( file.readAll() );

        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(file_text.toUtf8(), &jsonError);
        if (jsonError.error == QJsonParseError::NoError && !doc.isNull()) {
            qDebug("开始解析配置文件");
            QJsonObject obj = doc.object();
            SaveApiKey.append(obj.value(JNAME_APIKEY).toString());

        }
    }


}
bool FileConf::is_exist()
{
    return flag_exist;
}
void FileConf::write_apikey(QString apikey)
{
    SaveApiKey.clear();
    SaveApiKey.append(apikey);
}
QString FileConf::read_apikey()
{
    return SaveApiKey;
}

void FileConf::save()
{
    QJsonObject text;
    text.insert(JNAME_APIKEY,SaveApiKey);
    text.insert("name","VultrTool config");

    QJsonDocument doc(text);

    QFile file(FILENAME);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();

}
