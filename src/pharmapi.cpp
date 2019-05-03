#include "pharmapi.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

pharmapi::pharmapi()
{

}

// Mon identifiant au sein de l'enumération (classe mère)
Abstract_API::API_index pharmapi::getId()
{
    return PHARMACIES;
}

void pharmapi::getInfo()
{
     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("/home/dibydrams/pharmloc.db");
     db.open();

     if(db.open())
     {
         qDebug() << "Vous êtes maintenant connecté à la base de donnée pharmloc.";
         QSqlQuery query;
         if(query.exec("SELECT * FROM pharmloc"))
         {
             while(query.next())
             {
                 qDebug() << "Ajout d'une nouvelle pharmacie";
                 // Récupère les valeurs dans des variables.
                 latitude = query.value(1).toDouble();
                 longitude = query.value(2).toDouble();
                 qDebug() << "Pharmlat : " << latitude;
                 qDebug() << "Pharmlong : "<< longitude;

                 GeoObj geo;

                 geo.longitude = longitude;
                 geo.latitude = latitude;
                 geo.pixmap = QPixmap(":/Icons/pharmloc-pointer.svg");

                 m_list << geo;
             }
         }
     }
    qDebug()<<"emit"<<PHARMACIES;
    emit callFinished(m_list, PHARMACIES);  // Signal de fin de traitement de l'API
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap pharmapi::getPixmap()
{
    return QPixmap(":/Icons/pharmicon.png"); // icône PNG préférable
}
