
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

    vr->update_model(); //获取所有可用机型
    ui->list0->setMovement( QListView::Static );
    ui->list0->item(0)->setText( "cpu\tRAM\t硬盘\t分钟价格\t满月价格");

    int numModelFamilly = ui->list_model->currentRow();
    PageBuy::on_vpslist_currentChanged(numModelFamilly); //触发一次机型种类切换

    ui->Box_OS1->clear();
    for( int i=0; i<(OS_LIST_SIZE); i++ )
    {
        ui->Box_OS1->addItem( vr->os->at(i)->name() );
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
    ui->Box_locations1->clear();
    ui->Box_locations2->clear();
//    ui->Box_locations->addItem( now_model->introduce() );
    if( now_model->local->size() >1 )
    {
        ui->Box_locations1->setEnabled(true);
        for( int i = 0; i< now_model->local->size()-1 ; i++ )
        {
            ui->Box_locations1->addItem( now_model->local->at(i)->name() );
        }
    }
    else
        ui->Box_locations1->setEnabled(false);
    int size_other = now_model->local->at( now_model->local->size()-1 )->size();

    if( size_other>0 )
        ui->Box_locations1->addItem( now_model->local->at(now_model->local->size()-1)->name() );
}

void PageBuy::on_vpslist_tabBarClicked(int index)
{
    qDebug("click%d\n", index);
}



void PageBuy::on_pushButton_clicked()
{
    qDebug("购买机型id：%s",qPrintable( now_model->model_id()) );

}


void PageBuy::on_Box_OS1_currentIndexChanged(int index)
{
    if( ui->Box_OS2->count()>0 )
        ui->Box_OS2->clear();
    for( int i =0; i<  vr->os->at(index)->size() ; i++ )
    {
        ui->Box_OS2->addItem( vr->os->at(index)->at(i)->name);
    }
    qDebug("os1改变为%d",index);
}


void PageBuy::on_Box_OS2_currentIndexChanged(int index)
{
    int num_osfamilly = ui->Box_OS1->currentIndex();
//    int num_os = ui->Box_OS2->currentIndex();
    now_os = vr->os->at(num_osfamilly)->at(index );
    qDebug("现在选择的os是%s", qPrintable(now_os->name));
}


void PageBuy::on_Box_locations1_currentIndexChanged(int index)
{
    ui->Box_locations2->clear();
    for( int j = 0; j< now_model->local->at(index)->size() ; j++ )
    {
        ui->Box_locations2->addItem( now_model->local->at(index)->at(j)->name );
    }
    if( now_model->local->at(index)->size()<=1 ) //如果不到一个项目，则设为不可选
        ui->Box_locations2->setEnabled(false);
    else
        ui->Box_locations2->setEnabled(true);
    log(  now_model->introduce() );
}


void PageBuy::on_vpslist_currentChanged(int index)
{

//    update_model_locations(); //根据当前默认机型显示可部署位置栏
    qDebug("computer type change %d", index);
    if( ui->list_model->count()>0 )
        ui->list_model->clear();

    for( int i =0; i< vr->model->at(index)->size() ; i++ )
    {
        ui->list_model->addItem( vr->model->at(index)->at(i)->introduce() );
    }
    ui->list_model->setCurrentRow(0) ;
}


void PageBuy::on_list_model_currentRowChanged(int currentRow)
{
//    int num = item->listWidget()->currentRow();
    qDebug("currentRow=%d",currentRow);
    now_model = vr->model->at( ui->vpslist->currentIndex() )->at(currentRow);

    update_model_locations();
}

