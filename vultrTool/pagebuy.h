#ifndef PAGEBUY_H
#define PAGEBUY_H

#include <QMainWindow>
#include "vultr.h"
#include <QListWidgetItem>
#include "fileconf.h"

namespace Ui {
class PageBuy;
}



class PageBuy : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageBuy( Vultr *vultr_p, QWidget *parent = nullptr);
    ~PageBuy();

private:
    Ui::PageBuy *ui;
    FileConf *config;
    Vultr *vultr ;  //由外部传入vultr指针
    VpsOs *os ; //由vultr类中分离出来专门指向os
    VpsModel *model ; //由vultr类中分离出来专门指向model

    VpsModel_Data *select_model; //指向当前选择的机型
    Os_Data *select_os; //指向当前选择的系统
    Locatiom_Data *select_location;  //指向当前选择的地区


public slots:

private slots:
    void showEvent(QShowEvent *event);

    void on_Box_OS1_currentIndexChanged(int index);
    void on_Box_OS2_currentIndexChanged(int index);
    void on_TAB_model1_currentChanged(int index);
    void on_TAB_model2_currentChanged(int index);
    void on_list_model_currentRowChanged(int currentRow);
    void on_Box_locations1_currentIndexChanged(int index);
    void on_Box_locations2_currentIndexChanged(int index);
    void on_pushButton_clicked();
};

#endif // PAGEBUY_H
