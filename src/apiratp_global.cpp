#include "apiratp_global.h"

ApiRatp_Global::ApiRatp_Global()
{
    perimetreStifJson = LoadJson(":/Data/Databases/perimetre-tr-plateforme-stif.json");
    PeriStifJson();
}

void ApiRatp_Global::PeriStifJson()
{
    for (int i = 0; i < perimetreStifJson.array().count(); ++i)
    {
        // codifligne_line_externalcode = ID du Bus/Train/RER
        QString externalcodeLine = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["codifligne_line_externalcode"].toString();
        // reflex_zde_nom = Nom de l'arret,
        QString nomZDE = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["reflex_zde_nom"].toString();
        // monitoringref_zde = Stif ID de l'arret,
        QString monoRefZDE = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["monitoringref_zde"].toString();
        // gtfs_stop_id = ID de l'arret,
        QString idZDE = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["gtfs_stop_id"].toString();

        // xy = Coordonnées GPS de l'arret
        double coordX = perimetreStifJson.array().at(i).toObject()["geometry"].toObject()["coordinates"].toArray().at(0).toDouble();
        double coordY = perimetreStifJson.array().at(i).toObject()["geometry"].toObject()["coordinates"].toArray().at(1).toDouble();
        QPointF coordsZDE(coordX,coordY);


        pointList.append(coordsZDE);
        StopPoint newStopPoint(externalcodeLine, nomZDE, monoRefZDE, idZDE, coordsZDE, i);
        stopPointList.append(newStopPoint);
    }

    std::sort(stopPointList.begin(), stopPointList.end(), StopPoint::compareStopPoint);
}

void ApiRatp_Global::GeoPoints()
{
//    foreach(QPointF point, pointList)
//    {
//      compare Point is in coordonates
//        if ()
//        {
//          GeoObj geo;
//          geo.longitude = coordX;
//          geo.latitude = coordY;
//          geo.pixmap = QPixmap();
//          geo.id = getId();
//          geoList << geo;
//        }
//    }
//    emit callFinished(geoList);
}

QJsonDocument ApiRatp_Global::LoadJson(QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

// Mon identifiant au sein de l'enumération (classe mère)
int ApiRatp_Global::getId()
{
    return RATP;
}

void ApiRatp_Global::getInfo()
{
    if (stopPointList.isEmpty())
    {
        if (perimetreStifJson.isEmpty())
        {
            perimetreStifJson = LoadJson(":/Data/Databases/perimetre-tr-plateforme-stif.json");
        }
        PeriStifJson();
    }
    GeoPoints();
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiRatp_Global::getPixmap()
{
    return QPixmap(":/Icons/iconevents.png"); // icône PNG préférable
}
