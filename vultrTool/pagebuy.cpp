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
void PageBuy::update_model_owidget()
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

    update_model_owidget();

}

void PageBuy::on_pushButton_clicked()
{
    qDebug("购买机型id：%s",qPrintable( now_model->model_id()) );
    int location_num = ui->Box_locations->currentIndex();
    qDebug("购买位置：%s", qPrintable( now_model->locationsEN().at(location_num)) );
}

