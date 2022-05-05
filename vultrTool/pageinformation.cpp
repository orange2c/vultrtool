#include "pageinformation.h"
#include "ui_pageinformation.h"
#include "pagebuy.h"


PageInformation::PageInformation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageInformation)
{
    ui->setupUi(this);
    vr = new VULTR();
    QObject::connect( vr, SIGNAL(log(QString)), this, SLOT(log_slots(QString)) );

//    vr->update_message();
    ui->label_email->setText( vr->email);
    ui->label_name->setText( vr->username );
    ui->label_money->setText( QString::number(vr->Balance, 'f', 2) + "美元");

    PBuy = new PageBuy();
}

PageInformation::~PageInformation()
{
    delete ui;
    delete  vr;
    delete PBuy;
}
void PageInformation::log_slots(QString log_text)
{
    this->ui->logEdit->appendPlainText( log_text);
    qDebug ("%s\n",qPrintable(log_text));
}
void PageInformation::log(QString log_text)
{
    this->ui->logEdit->appendPlainText( log_text);
    qDebug ("%s",qPrintable(log_text));
}


void PageInformation::on_button_buy_clicked()
{
    PBuy->show();
//    log("yes");
}

