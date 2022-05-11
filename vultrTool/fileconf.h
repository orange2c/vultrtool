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
    FileConf();
    bool is_exist(); //conf文件是否存在
    void write_apikey( QString apikey); //写入apikey
    QString read_apikey();
    void save();

protected:
    bool flag_exist=false;
    QString SaveApiKey;
#define FILENAME "VTool.ini"
#define JNAME_APIKEY "API_KEY"


};

#endif // FILECONF_H
