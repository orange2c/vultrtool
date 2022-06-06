#ifndef PAGEVPSINFO_H
#define PAGEVPSINFO_H

#include <QMainWindow>
#include "vultr.h"

namespace Ui {
class PageVPSinfo;
}

class PageVPSinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageVPSinfo(QWidget *parent = nullptr);
    ~PageVPSinfo();

private:
    Ui::PageVPSinfo *ui;
};

#endif // PAGEVPSINFO_H
