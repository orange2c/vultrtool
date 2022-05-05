#ifndef PAGE_PageInformation_H
#define PAGE_PageInformation_H

#include <QMainWindow>
#include "vultr.h"
#include "pagebuy.h"

namespace Ui {
class PageInformation;
}

class PageInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageInformation(QWidget *parent = 0);
    ~PageInformation();



private:
    Ui::PageInformation *ui;
    VULTR *vr;  //定义一个操作vultr的类指针
    PageBuy *PBuy;

    void log( QString log_text ); //将传入字符串在log窗口显示出来
public slots:
    void log_slots( QString log_text );

private slots:
    void on_button_buy_clicked();
};

#endif // PAGE_PageInformation_H
