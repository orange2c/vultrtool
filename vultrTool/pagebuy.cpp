
#include "pagebuy.h"
#include "ui_pagebuy.h"
#include <QListWidgetItem>

PageBuy::PageBuy(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageBuy)
{
    ui->setupUi(this);
    vr = new VULTR();
    QObject::connect( vr, SIGNAL(log(QString)), this, SLOT(log_slots(QString)) );

    vr->update_model();
    ui->list0->setMovement( QListView::Static );
    ui->list0->item(0)->setText( "cpu\tRAM\t硬盘\t分钟价格\t满月价格");
    for( int i =0; i< vr->vc2->size(); i++ )
    {
        ui->list_model->addItem( vr->vc2->at(i)->introduce() );
    }
    ui->list_model->setCurrentRow(0) ;
    PageBuy::on_list_model_itemClicked(ui->list_model->currentItem());


    for( int i=0; i<(OS_LIST_SIZE); i++ )
    {
        ui->Box_OS1->addItem( vr->OSlist[i]->name() );
    }
}

PageBuy::~PageBuy()
{
    delete ui;
    delete vr;
}
void PageBuy::log_slots(QString log_text)
{
    this->ui->logEdit->appendPlainText( log_text);
    qDebug ("%s\n",qPrintable(log_text));
}
void PageBuy::log(QString log_text)
{
    this->ui->logEdit->appendPlainText( log_text);
    qDebug ("%s",qPrintable(log_text));
}

void PageBuy::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    log("showevent");

}
void PageBuy::update_model_locations()
{
    ui->Box_locations->clear();
//    ui->Box_locations->addItem( now_model->introduce() );
    for( int i = 0; i<now_model->locationsCN().size(); i++ )
    {
        ui->Box_locations->addItem( now_model->locationsCN().at(i) );
    }

    log(  now_model->introduce() );
}

void PageBuy::on_vpslist_tabBarClicked(int index)
{
    qDebug("click%d\n", index);
}

void PageBuy::on_list_model_itemClicked(QListWidgetItem *item)
{
    int num = item->listWidget()->currentRow();
    qDebug("%d",item->listWidget()->currentRow());
    now_model = vr->vc2->at(num);

    update_model_locations();

}

void PageBuy::on_pushButton_clicked()
{
    qDebug("购买机型id：%s",qPrintable( now_model->model_id()) );
    int location_num = ui->Box_locations->currentIndex();
    qDebug("购买位置：%s", qPrintable( now_model->locationsEN().at(location_num)) );
//    qDebug("部署系统：%s",qPrintable(  ));
}


void PageBuy::on_Box_OS1_currentIndexChanged(int index)
{
    if( ui->Box_OS2->count()>0 )
        ui->Box_OS2->clear();
    for( int i =0; i< vr->OSlist[index]->size(); i++ )
    {
        ui->Box_OS2->addItem(vr->OSlist[index]->at(i)->name);
    }
    qDebug("os1改变为%d",index);
}


void PageBuy::on_Box_OS2_currentIndexChanged(int index)
{
    int num_osfamilly = ui->Box_OS1->currentIndex();
//    int num_os = ui->Box_OS2->currentIndex();
    now_os = vr->OSlist[ num_osfamilly ]->at(index );
    qDebug("现在选择的os是%s", qPrintable(now_os->name));
}

