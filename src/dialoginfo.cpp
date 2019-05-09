#include "dialoginfo.h"
#include "ui_dialoginfo.h"
#include "widgetmap.h"
#include "distance.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

void dialoginfo::setData(const QString cliclong, const QString cliclat)
{
    QString longitude = cliclong;
    QString latitude = cliclat;
    tableWidgetDistance = new QTableWidget(this);
    ui->verticalLayout->addWidget(tableWidgetDistance);
    tableWidgetDistance->setColumnCount(2);
    int row;
    row = tableWidgetDistance->rowCount() - 1;
    tableWidgetDistance->insertRow(tableWidgetDistance->rowCount());
//    tableWidgetDistance->setItem(row, 2, new QTableWidgetItem((QVariant(WidgetMap::centreLongitude)).toString()));
    tableWidgetDistance->setItem(row, 2, new QTableWidgetItem(longitude));
    tableWidgetDistance->setItem(row, 3, new QTableWidgetItem(latitude));
    qDebug()<<"longitude : :"<<longitude;
    qDebug()<<"latitude : :"<<latitude;
    dist=new distance(qApp,latitude,longitude,"pedestrian");
    qDebug()<<"ditance : : "<<dist->getDistanceInMeters();
}

dialoginfo::dialoginfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoginfo)
{
    ui->setupUi(this);
    setWindowTitle("Informations");

}

dialoginfo::~dialoginfo()
{
    delete ui;
}
