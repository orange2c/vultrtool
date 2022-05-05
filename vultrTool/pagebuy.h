#ifndef PAGEBUY_H
#define PAGEBUY_H

#include <QMainWindow>
#include "vultr.h"
#include <QListWidgetItem>

namespace Ui {
class PageBuy;
}

class PageBuy : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageBuy(QWidget *parent = nullptr);
    ~PageBuy();

private:
    Ui::PageBuy *ui;
    VULTR *vr;  //定义一个操作vultr的类指针
    VPSMODEL *now_model;

    void update_model_list();
    void update_model_owidget();
    void log( QString log_text ); //将传入字符串在log窗口显示出来

public slots:
    void log_slots( QString log_text );
private slots:
    void showEvent(QShowEvent *event);

    void on_vpslist_tabBarClicked(int index);
    void on_list_model_itemClicked(QListWidgetItem *item);
    void on_pushButton_clicked();
};

#endif // PAGEBUY_H
