
#define KEY_FILE_PATH  "/home/cb/VULTR_KEY.txt"
#define KEY_FILE_PATH2 "D:\\Desktop\\api_key.txt"

#include "pagelogin.h"
#include "ui_pagelogin.h"
#include "vultr.h"
#include "pageinformation.h"

#include <QNetworkReply>
#include <QDebug>
#include <QString>

#include <QFile>
#include <spider.h>
PageLogin::PageLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageLogin)
{
    ui->setupUi(this);

    //输出可用网络协议
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    qDebug() << accessManager->supportedSchemes();
    delete  accessManager;


    //开始尝试读取配置文件中的apikey
    FileConf config;
    if( ! config.is_exist() )
    {
        qDebug("file not");
        config.write_apikey("hello");
        config.save();
    }
    else
    {
        qDebug("read api key%s", qPrintable( config.read_apikey() )  );

    }

    QByteArray key = openPDfile(KEY_FILE_PATH );
    if( key.size()>3)
    {
        VULTR::set_key( &key);
        ui->key_edit->setText( key.data());
    }
    QByteArray key2 = openPDfile(KEY_FILE_PATH2 );
    if( key2.size()>3)
    {
        VULTR::set_key( &key2);
        ui->key_edit->setText( key2.data());
    }

    vr = new VULTR();
    QObject::connect( vr, SIGNAL(log(QString)), this, SLOT(log_slots(QString)) );
    //判断配置文件是否存在
    //如果存在则将其中的数据读取进来
    //如果不存在则将创建，并在按下登陆按钮成功登陆后保存进去


}

PageLogin::~PageLogin()
{
    delete ui;
    delete vr;
    delete config;
}

void PageLogin::log_slots(QString log_text)
{
    this->ui->log_lab->appendPlainText( log_text);
    qDebug ("%s\n",qPrintable(log_text));
}
void PageLogin::log(QString log_text)
{
    this->ui->log_lab->appendPlainText( log_text);
    qDebug ("%s",qPrintable(log_text));
}
QByteArray PageLogin::openPDfile(QString filename)
{
    log("打开密码文件");
    QFile f;
    f.setFileName( filename );
    bool isok = f.open(QIODevice::ReadOnly);
    QByteArray array;
    if(isok == true)
        array = f.readLine();
    else
    {
        log("PDfile open error!!");
        return NULL;
    }
    f.close();
    return array;
}


void PageLogin::on_login_button_clicked()
{

    QString key_value =  this->ui->key_edit->text();
    log( key_value);

    if(vr->login())
    {
        PageInformation *mWindow = new PageInformation();
        log( " 切换新窗口 ");
        mWindow->show();
        this->close();
    }


}


