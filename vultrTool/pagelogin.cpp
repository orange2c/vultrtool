
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
    if(  config.is_exist() )
    {
        ui->key_edit->setText( config.read_apikey() );
        qDebug("read api key%s", qPrintable( config.read_apikey() )  );
    }

    vr = new VULTR();
    QObject::connect( vr, SIGNAL(log(QString)), this, SLOT(log_slots(QString)) );

}

PageLogin::~PageLogin()
{
    delete ui;
    delete vr;
}
void PageLogin::login()
{
    QString key_text = ui->key_edit->text();
    vr->set_key( key_text );

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

void PageLogin::on_login_button_clicked()
{

    QString key_value =  this->ui->key_edit->text();
    vr->set_key(key_value);
    log( key_value);

    if(vr->login())
    {
        PageInformation *mWindow = new PageInformation();
        log( " 切换新窗口 ");
        mWindow->show();
        this->close();
    }


}


