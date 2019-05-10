#include "dialoginfo.h"
#include "ui_dialoginfo.h"
#include "widgetmap.h"
#include "distance.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

/**
 * @brief dialoginfo::dialoginfo
 * @param parent
 */
dialoginfo::dialoginfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoginfo)
{
    ui->setupUi(this);
    setWindowTitle("Informations");
}

/**
 * @brief dialoginfo::setData
 * @param cliclong type double ; la longitude réelle correspondante au niveau du clic sur la map
 * @param cliclat  type double ; la latitude réelle correspondante au niveau du clic sur la map
 * @param list de GeoObj qui contiennent eux même une QMap contenant
 *        les informations remplies relatives aux point d'intérêts cliqués
 * @details La fonction rempli des QtableWidget qui seront rempli avec les données des QMap<QString,QString>
 *          Les QTableWidget sont ensuite incorporé au layout de la Qdialog.
 */
void dialoginfo::setData(const double cliclong, const double cliclat, QList<Abstract_API::GeoObj> list)
{
    QVariant longitude = cliclong;
    QVariant latitude = cliclat;
    dist=new distance(qApp,latitude.toString(),longitude.toString(),"pedestrian");
    QString distanceInMeters=distance::kilometers_meters(dist->getDistanceInMeters());
    QString timeTravel=distance::time_hours_minutes_seconds(dist->getTimetravel());
    dist->~distance();
    dist=new distance(qApp,latitude.toString(),longitude.toString(),"car");
    QString timeTravelCar=distance::time_hours_minutes_seconds(dist->getTimetravelWithTraffic());
    dist->~distance();
    dist=new distance(qApp,latitude.toString(),longitude.toString(),"bus");
    QString timeTravelbus=distance::time_hours_minutes_seconds(dist->getTimetravelWithTraffic());
    dist->~distance();

    // si la list contient au moins 1 géoObj, on va chercher les informations contenu dans la Qmap de ce dernier
    if(!list.isEmpty()){
        for (int i = 0; i < list.size(); ++i){
            tableInfo = new QTableWidget(this);
            tableInfo->setColumnCount(2);
            tableInfo->setRowCount(list.at(i).info.size()+4);
            ui->verticalLayout->addWidget(tableInfo);
            QMap <QString,QString> info=list.at(i).info;
            QMapIterator<QString, QString> j(info);
            int k=-1;
            while (j.hasNext()) {
                j.next();
                // qDebug() << j.key() << ": " << j.value() << endl;
                QTableWidgetItem *newkey = new QTableWidgetItem(j.key());
                QTableWidgetItem *newvalue = new QTableWidgetItem(j.value());
                tableInfo->setItem(k,2,newkey);
                tableInfo->setItem(k,3,newvalue);
                k++;
            }
            QTableWidgetItem *distance = new QTableWidgetItem("distance");
            QTableWidgetItem *klm = new QTableWidgetItem(distanceInMeters);
            tableInfo->setItem(k,2,distance);
            tableInfo->setItem(k,3,klm);
            QTableWidgetItem *timTravelped = new QTableWidgetItem("Temps de trajet à pied");
            QTableWidgetItem *time = new QTableWidgetItem(timeTravel);
            tableInfo->setItem(k+1,2,timTravelped);
            tableInfo->setItem(k+1,3,time);
            QTableWidgetItem *timeTravelgow = new QTableWidgetItem("Temps de trajet voiture");
            QTableWidgetItem *timeWidCar = new QTableWidgetItem(timeTravelCar);
            tableInfo->setItem(k+2,2,timeTravelgow);
            tableInfo->setItem(k+2,3,timeWidCar);
            QTableWidgetItem *timeTravelB = new QTableWidgetItem("Temps de trajet en bus");
            QTableWidgetItem *timeWidBus = new QTableWidgetItem(timeTravelbus);
            tableInfo->setItem(k+3,2,timeTravelB);
            tableInfo->setItem(k+3,3,timeWidBus);
        }
    }else{ // si la list est vide, on ne renvoie que le temps de trajet jusqu'au point cliqué
        tableInfo = new QTableWidget(this);
        tableInfo->setColumnCount(2);
        tableInfo->setRowCount(4);
        ui->verticalLayout->addWidget(tableInfo);
        QTableWidgetItem *distance = new QTableWidgetItem("distance");
        QTableWidgetItem *klm = new QTableWidgetItem(distanceInMeters);
        tableInfo->setItem(-1,2,distance);
        tableInfo->setItem(-1,3,klm);
        QTableWidgetItem *timTravelped = new QTableWidgetItem("Temps de trajet à pied");
        QTableWidgetItem *time = new QTableWidgetItem(timeTravel);
        tableInfo->setItem(0,2,timTravelped);
        tableInfo->setItem(0,3,time);
        QTableWidgetItem *timeTravelgow = new QTableWidgetItem("Temps de trajet voiture");
        QTableWidgetItem *timeWidCar = new QTableWidgetItem(timeTravelCar);
        tableInfo->setItem(1,2,timeTravelgow);
        tableInfo->setItem(1,3,timeWidCar);
        QTableWidgetItem *timeTravelB = new QTableWidgetItem("Temps de trajet en bus");
        QTableWidgetItem *timeWidBus = new QTableWidgetItem(timeTravelbus);
        tableInfo->setItem(2,2,timeTravelB);
        tableInfo->setItem(2,3,timeWidBus);
    }
}

dialoginfo::~dialoginfo()
{
    delete ui;
}
