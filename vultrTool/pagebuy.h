#ifndef PAGEBUY_H
#define PAGEBUY_H

#include <QMainWindow>
#include "vultr.h"
#include <QListWidgetItem>

namespace Ui {
class PageBuy;
}

//创建一个类来存储当前的页面内所有项目的选择
class MODEL_NOW
{
public:
};

class PageBuy : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageBuy(QWidget *parent = nullptr);
    ~PageBuy();

private:
    Ui::PageBuy *ui;
    VULTR *vr;  //定义一个操作vultr的类指针

    VPSMODE_DATA *select_model;
    OSDATA *select_os;

    void log( QString log_text ); //将传入字符串在log窗口显示出来

public slots:
    void log_slots( QString log_text );
private slots:
    void showEvent(QShowEvent *event);

    void on_Box_OS1_currentIndexChanged(int index);
    void on_Box_OS2_currentIndexChanged(int index);
    void on_TAB_model1_currentChanged(int index);
    void on_TAB_model2_currentChanged(int index);
    void on_list_model_currentRowChanged(int currentRow);
    void on_Box_locations1_currentIndexChanged(int index);
};

#endif // PAGEBUY_H
