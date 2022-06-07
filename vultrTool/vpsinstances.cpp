#include "vpsinstances.h"

VpsInstances::VpsInstances(QObject *parent) : QObject(parent)
{
     qDebug("instances");
}

void VpsInstances::updata()
{
    if( spider == NULL )
    {
        spider = new Spider;
        connect( spider, SIGNAL(reply_ready()), SLOT(reply_instances()) );
        spider->get( "instances" );
    }

}
void VpsInstances::reply_instances()
{

    qDebug("收到恢复instances");
    delete  spider;
    spider = NULL;
}
