#ifndef FILECONF_H
#define FILECONF_H
#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
class FileConf
{
public:
#define FILENAME "VTool.ini"
#define JNAME_APIKEY "API_KEY"
    FileConf();

    void write_apikey( QString apikey); //写入apikey
    QString read_apikey( ); //读取

protected:


    QString SaveApiKey;
    QJsonObject *jtext = NULL; //存储转化为json的配置文件内容

    int load();  //读取配置文件内容存储到本类的text中,-1则为文件不存在
    QString read( QString key); //从text中，读取指定key所对应的内容
    void write( QString key, QString value ); //写入指定key到text中，
    void save();  //将text的内容创建并存储到文件





};

#endif // FILECONF_H
