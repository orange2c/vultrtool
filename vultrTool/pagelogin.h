#ifndef PAGELOGIN_H
#define PAGELOGIN_H

#include <QDialog>
#include <vultr.h>
#include "fileconf.h"
namespace Ui {
class PageLogin;
}

class PageLogin : public QDialog
{
    Q_OBJECT

public:
    explicit PageLogin(QWidget *parent = 0);
    ~PageLogin();
protected:
    Ui::PageLogin *ui;

    VULTR *vr;
    void login(); //使用界面上栏内的值进行登陆
    void log( QString log_text ); //将传入字符串在log窗口显示出来
    QByteArray openPDfile( QString filename );


public slots:
    void log_slots( QString log_text );

private slots:
    void on_login_button_clicked();

};

#endif // PAGELOGIN_H
