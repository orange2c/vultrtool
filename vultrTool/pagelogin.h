#ifndef PAGELOGIN_H
#define PAGELOGIN_H

#include <QDialog>
#include <vultr.h>
namespace Ui {
class PageLogin;
}

class PageLogin : public QDialog
{
    Q_OBJECT

public:
    explicit PageLogin(QWidget *parent = 0);
    ~PageLogin();

public slots:
    void log_slots( QString log_text );

private slots:
    void on_login_button_clicked();


private:
    VULTR *vr;
    Ui::PageLogin *ui;
    void log( QString log_text ); //将传入字符串在log窗口显示出来
    QByteArray openPDfile( QString filename );

};

#endif // PAGELOGIN_H
