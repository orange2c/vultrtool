
#include "pagebuy.h"
#include "ui_pagebuy.h"
#include <QListWidgetItem>

PageBuy::PageBuy( Vultr *vultr_p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageBuy),
    vultr( vultr_p ),
    os( vultr->get_os() ),
    model( vultr->get_model() )
{
    ui->setupUi(this);

}

PageBuy::~PageBuy()
{
    delete ui;
}

void PageBuy::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    ui->list0->setMovement( QListView::Static );

    ui->Box_OS1->clear();
    for( int i=0; i<(OS_LIST_SIZE); i++ )
    {
        ui->Box_OS1->addItem( os->at(i)->name() );
    }

    //设置一下两个机型类别选择的tab标签铺满
    int width = ui->TAB_model1->width() /3 ;
    ui->TAB_model1->setStyleSheet(QString("QTabBar::tab{width:%1px;}").arg(width));
    width = ui->TAB_model2->width() /4 ;
    ui->TAB_model2->setStyleSheet(QString("QTabBar::tab{width:%1px;}").arg(width));

    ui->TAB_model1->setCurrentIndex(0); //手动触发选择机型大类，刷新机型小类的选项，及机型列表
    emit ui->TAB_model1->currentChanged(0);

}


void PageBuy::on_Box_OS1_currentIndexChanged(int index)
{
    if( ui->Box_OS2->count()>0 )
        ui->Box_OS2->clear();
    for( int i =0; i<  os->at(index)->size() ; i++ )
    {
        ui->Box_OS2->addItem( os->at(index)->at(i)->name);
    }
    qDebug("os1改变为%d",index);
}
void PageBuy::on_Box_OS2_currentIndexChanged(int index)
{
    int num_osfamilly = ui->Box_OS1->currentIndex();
//    int num_os = ui->Box_OS2->currentIndex();
    select_os = os->at(num_osfamilly)->at(index );
    qDebug("现在选择的os是%s", qPrintable(select_os->name));
}

void PageBuy::on_TAB_model1_currentChanged(int index)
{
    qDebug("机型大类栏触发：%d", index );

    int index_p = index*4;

    switch (index) {
    case 0:
    case 1:
         ui->list0->item(0)->setText( "cpu\tRAM\t硬盘\t分钟价格\t满月价格");
        ui->TAB_model2->setHidden( false );
//        ui->list_model->setHidden( false );

        ui->TAB_model2->setTabText(0, model->at(index_p)->name());
        ui->TAB_model2->setTabText(1, model->at(index_p+1)->name());
        ui->TAB_model2->setTabText(2, model->at(index_p+2)->name());
        ui->TAB_model2->setTabText(3, model->at(index_p+3)->name());


        break;

    case 2:
         ui->list0->item(0)->setText( "cpu\t核心线程\tRAM\t硬盘\t分钟价格\t满月价格");
        ui->TAB_model2->setHidden(true);
//        ui->list_model->setHidden(true);
//        return;

    }
    ui->TAB_model2->setCurrentIndex(0); //手动触发机型小类选择，使机型列表更新信息
    emit ui->TAB_model2->currentChanged( ui->TAB_model2->currentIndex() );


}

void PageBuy::on_TAB_model2_currentChanged(int index)
{

    int num_model1 = ui->TAB_model1->currentIndex();
    int index_p = num_model1*4 + index;
    qDebug("机型小类栏触发：%d,index_p=%d", index, index_p );

    if( ui->list_model->count()>0 )
        ui->list_model->clear();

    for( int i =0; i< model->at( index_p )->size() ; i++ )
    {
        ui->list_model->addItem( model->at(index_p)->at(i)->introduce() );
    }
    ui->list_model->setHidden(false);

    ui->list_model->setCurrentRow(0); //手动触发一次机型选择，向后更新数据
}

void PageBuy::on_list_model_currentRowChanged(int currentRow)
{
    if( currentRow <0 ) return; //前面在更新本列表时会先clear，会导致传入一次-1
    qDebug("机型列表栏触发：%d", currentRow );

    int num_model_class = ui->TAB_model1->currentIndex()*4 + ui->TAB_model2->currentIndex();
    qDebug("model class = %d", num_model_class);

    select_model = model->at(num_model_class)->at(currentRow);

    //设置可部署地区的栏
    ui->Box_locations1->clear();
    ui->Box_locations2->clear();
    if( select_model->location->size() >1 )
    {
        ui->Box_locations1->setEnabled(true);
        for( int i = 0; i< select_model->location->size()-1 ; i++ )
        {
            ui->Box_locations1->addItem( select_model->location->at(i)->name() );
        }
    }
    else
        ui->Box_locations1->setEnabled(false);
    int size_other = select_model->location->at( select_model->location->size()-1 )->size();

    if( size_other>0 )
        ui->Box_locations1->addItem( select_model->location->at(select_model->location->size()-1)->name() );

    ui->label_cost->setText( select_model->cost_month()+ "美元/月" );
}

void PageBuy::on_Box_locations1_currentIndexChanged(int index)
{
     if( index <0 ) return; //前面在更新本列表时会先clear，会导致传入一次-1
    qDebug("地区选择：%d", index);


    ui->Box_locations2->clear();
    for( int j = 0; j< select_model->location->at(index)->size() ; j++ )
    {
        ui->Box_locations2->addItem( select_model->location->at(index)->at(j)->name );
    }
    if( select_model->location->at(index)->size()<=1 ) //如果不到一个项目，则设为不可选
        ui->Box_locations2->setEnabled(false);
    else
        ui->Box_locations2->setEnabled(true);

}


void PageBuy::on_Box_locations2_currentIndexChanged(int index)
{
    if( index <0 ) return; //前面在更新本列表时会先clear，会导致传入一次-1
    qDebug("选择地区小编号%d", index);
    int num_box1 = ui->Box_locations1->currentIndex();
    select_location = select_model->location->at(num_box1)->at(index);
    qDebug("选择地区为%s", qPrintable( select_location->airport));
}


void PageBuy::on_pushButton_clicked()
{

    qDebug("select model:%s", qPrintable(select_model->model_id()) );
    qDebug( "select os:%d", select_os->id );
    qDebug("select locations:%s", qPrintable(select_location->airport) );

}

