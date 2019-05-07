#include "dialoginfo.h"
#include "ui_dialoginfo.h"
#include <QVBoxLayout>
#include <QTableWidget>

dialoginfo::dialoginfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoginfo)
{
    ui->setupUi(this);

    tableWidgetDistance = new QTableWidget(this);
    ui->verticalLayout->addWidget(tableWidgetDistance);

}

dialoginfo::~dialoginfo()
{
    delete ui;
}
