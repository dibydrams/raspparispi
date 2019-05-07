#include "dialoginfo.h"
#include "ui_dialoginfo.h"

dialoginfo::dialoginfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoginfo)
{
    ui->setupUi(this);
}

dialoginfo::~dialoginfo()
{
    delete ui;
}
