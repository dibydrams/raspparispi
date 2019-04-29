#include "apiratp_global.h"

ApiRatp_Global::ApiRatp_Global()
{

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

void ApiRatp_Global::RefStifJson()
{
    for (int i = 0; i < referentielStifJson.array().count(); ++i)
    {
        // externalcode_line = ID du Bus/Train/RER
        QString codeLine = referentielStifJson.array().at(i).toObject()["fields"].toObject()["externalcode_line"].toString();
        // shortname_line = Nom commun
        QString shortnameLine = referentielStifJson.array().at(i).toObject()["fields"].toObject()["shortname_line"].toString();
        // shortname_groupoflines = Nom des principales destinations
        QString shortnameGroupoflines = referentielStifJson.array().at(i).toObject()["fields"].toObject()["shortname_groupoflines"].toString();
        // networkname = Nom du Réseau référent
        QString networkname = referentielStifJson.array().at(i).toObject()["fields"].toObject()["networkname"].toString();
        // transportmode = Catégorie du transport
        QString transportmode = referentielStifJson.array().at(i).toObject()["fields"].toObject()["transportmode"].toString();
        // accessibility = Accessible aux personnes en situation d'handicap ?
        int accessibility = referentielStifJson.array().at(i).toObject()["fields"].toObject()["accessibility"].toInt();

        // Liste des Arrêts du transport
        QList<StopPoint> mySPList;
        foreach (StopPoint sp, stopPointList) {
            if (sp.externalcodeLine == codeLine)
                mySPList.append(sp);
        }

        Transport newTransport(codeLine, shortnameLine, shortnameGroupoflines, networkname, transportmode, accessibility, i, mySPList);

        if(newTransport.transportMode == Transport::Modes::bus)
        {
            for (int j = 0; j < stopPointList.count(); ++j)
            {
                if(stopPointList[j].externalcodeLine == newTransport.codeLine)
                {
                    busList.append(newTransport);
                    break;
                }
            }
        }
        else if(newTransport.transportMode == Transport::Modes::metro)
        {
            metroList.append(newTransport);
        }
        else
        {
            railList.append(newTransport);
        }
    }

    std::sort(busList.begin(), busList.end(), Transport::compareTransports);
    std::sort(metroList.begin(), metroList.end(), Transport::compareTransports);
    std::sort(railList.begin(), railList.end(), Transport::compareTransports);
}

void ApiRatp_Global::GeoPoints()
{
    geoList.clear();

    foreach(QPointF point, pointList)
    {
//      compare Point with Map Coordonnates
        if ((point.x() > widgetmap.m_BBOXminLongitude && point.x() < widgetmap.m_BBOXmaxLongitude) &&
             (point.y() > widgetmap.m_BBOXminLatitude && point.y() < widgetmap.m_BBOXmaxLatitude))
        {
          GeoObj geo;
          geo.longitude = point.x();
          geo.latitude = point.y();
          geo.pixmap = QPixmap(":/Icons/iconRatpStationSpot.png");
          geoList << geo;
        }
    }
    emit callFinished(geoList, RATP);
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
            perimetreStifJson = LoadJson(":/Datas/perimetre-tr-plateforme-stif.json");
        }
        PeriStifJson();
    }
    GeoPoints();
//    if(busList.isEmpty())
//    {
//        if (referentielStifJson.isEmpty())
//        {
//            referentielStifJson = LoadJson(":/Datas/referentiel-des-lignes-stif.json");
//        }
//        RefStifJson();
//    }
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiRatp_Global::getPixmap()
{
    return QPixmap(":/Icons/iconStation.png"); // icône PNG préférable
}
