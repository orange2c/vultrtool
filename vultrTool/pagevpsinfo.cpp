#include "pagevpsinfo.h"
#include "ui_pagevpsinfo.h"

PageVPSinfo::PageVPSinfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageVPSinfo)
{
    ui->setupUi(this);
}

PageVPSinfo::~PageVPSinfo()
{
    delete ui;
}
