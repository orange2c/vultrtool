#ifndef PAGE_PageInformation_H
#define PAGE_PageInformation_H

#include <QMainWindow>
#include "vultr.h"
#include "pagebuy.h"
#include "vpsinstances.h"

namespace Ui {
class PageInformation;
}

class PageInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageInformation( Vultr *vultr_p, QWidget *parent = 0);
    ~PageInformation();
private:
    Ui::PageInformation *ui;
    Vultr *vultr;  //定义一个操作vultr的类指针


    PageBuy *page[3];

public slots:
private slots:
    void on_button_buy_clicked();
};

#endif // PAGE_PageInformation_H
