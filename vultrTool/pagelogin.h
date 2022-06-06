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

    Vultr *vultr;
    void login(); //使用界面上栏内的值进行登陆

public slots:

private slots:
    void on_login_button_clicked();

};

#endif // PAGELOGIN_H
