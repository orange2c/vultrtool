
#include "pageinformation.h"
#include "ui_pageinformation.h"
#include "pagebuy.h"


PageInformation::PageInformation( Vultr *vultr_p,  QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageInformation),
    vultr( vultr_p )
{
    ui->setupUi(this);

    int pagecount = sizeof( page )  /  sizeof( page[0] );
    for( pagecount--; pagecount >= 0; pagecount-- )
        page[ pagecount ] = new PageBuy( vultr );

    ui->label_email->setText( vultr->email);
    ui->label_name->setText( vultr->username );
    ui->label_money->setText( QString::number(vultr->Balance, 'f', 2) + "美元");

}

PageInformation::~PageInformation()
{
    qDebug("delete pagebug");
    int pagecount = sizeof( page )  /  sizeof( page[0] );
    for( pagecount--; pagecount >= 0; pagecount-- )
    {
        qDebug("delete pagebug");
        page[ pagecount ]->close();
        delete page[ pagecount ];
    }

    delete ui;

}


void PageInformation::on_button_buy_clicked()
{
    int pagecount = sizeof( page )  /  sizeof( page[0] );
    for( pagecount--; pagecount >= 0; pagecount-- )
    {
        if( page[ pagecount ]->isHidden() )
        {
            page[ pagecount ]->show();
            return;
        }
    }
}

