#include "pharmapi.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

pharmapi::pharmapi()
{

}

// Mon identifiant au sein de l'enumération (classe mère)
int pharmapi::getId()
{
    return PHARMACIES;
}

void pharmapi::getInfo()
{
     qDebug() << "coucou";
     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("/home/dibydrams/pharmloc.db");
     db.open();

     if(db.open())
     {
         qDebug() << "Vous êtes maintenant connecté";
         QSqlQuery query;
         if(query.exec("SELECT * FROM pharmloc"))
         {
             while(query.next())
             {
                 qDebug() << "Nouvelle pharmacie";
                     // Récupère les valeurs dans des variables.
                     latitude = query.value(1).toDouble();
                     longitude = query.value(2).toDouble();
                     qDebug() << "Pharmlat : " << latitude;
                     qDebug() << "Pharmlong : "<< longitude;

                     GeoObj geo;

                     geo.longitude = longitude;
                     geo.latitude = latitude;
                     geo.pixmap = QPixmap();

                     m_list << geo;
             }
         }
     }
    qDebug()<<"emit"<<PHARMACIES;
    emit callFinished(m_list, PHARMACIES);  // Signal de fin de traitement de l'API

}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap pharmapi::getPixmap()
{
    return QPixmap(":/Icons/pharmicon.png"); // icône PNG préférable
}
