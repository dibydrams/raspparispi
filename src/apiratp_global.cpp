#include "apiratp_global.h"

ApiRatp_Global::ApiRatp_Global()
{
    m_settings = new QSettings("raspparispi", "raspparispi");
    if (referentielStifJson.isEmpty())
    {
        if (m_settings->value("Datas/Referentiel").isNull())
        {
            QStringList splitList = m_settings->fileName().split("/");
            m_settings->setValue("Datas/Referentiel", QDir().homePath() + "/" + splitList[3] + "/" + splitList[4] + "/referentiel-des-lignes-stif.json");
        }
        QString filename = m_settings->value("Datas/Referentiel").toString();
        referentielStifJson =  LoadJson(filename);
    }

    if (stopPointList.isEmpty())
    {
        if (perimetreStifJson.isEmpty())
        {
            if (m_settings->value("Datas/Perimetre").isNull())
            {
                QStringList splitList = m_settings->fileName().split("/");
                m_settings->setValue("Datas/Perimetre", QDir().homePath() + "/" + splitList[3] + "/" + splitList[4] + "/perimetre-tr-plateforme-stif.json");
            }
            QString filename = m_settings->value("Datas/Perimetre").toString();
            perimetreStifJson =  LoadJson(filename);
        }
        PeriStifJson();
    }
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
        // codifligne_network_name = Nom du network gérant
        QString networkName = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["codifligne_network_name"].toString();

        // xy = Coordonnées GPS de l'arret
        double coordX = perimetreStifJson.array().at(i).toObject()["geometry"].toObject()["coordinates"].toArray().at(0).toDouble();
        double coordY = perimetreStifJson.array().at(i).toObject()["geometry"].toObject()["coordinates"].toArray().at(1).toDouble();
        QPointF coordsZDE(coordX,coordY);

        pointList.append(coordsZDE);
        StopPoint newStopPoint(externalcodeLine, nomZDE, monoRefZDE, idZDE, coordsZDE, networkName, i);
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

        Transport newTransport(codeLine, shortnameLine, shortnameGroupoflines, networkname, transportmode, accessibility, i, mySPList);
        transportList << newTransport;
    }
}

void ApiRatp_Global::GeoPoints(QNetworkReply * reply)
{
    geoList.clear();

    foreach(StopPoint stop, stopPointList)
    {
        if (utilitaire::inMap(stop.coordsZDE.y(), stop.coordsZDE.x()))
        {
            GeoObj geo;
            geo.longitude = stop.coordsZDE.x();
            geo.latitude = stop.coordsZDE.y();
            if (stop.networkName == "METRO")
            {
                geo.pixmap = Icon::iconMapOffStr(getPixmap(), "M", QColor(25, 130, 80));
            }
            else if (stop.networkName == "RER")
            {
                geo.pixmap = Icon::iconMapOffStr(getPixmap(), "R", QColor(110, 100, 90));
            }
            else if (stop.networkName == "TRAMWAY")
            {
                geo.pixmap = Icon::iconMapOffStr(getPixmap(), "T", QColor(210, 210, 115));
            }
            else
            {
                geo.pixmap = Icon::iconMapOffStr(getPixmap(), "B", QColor(0, 170, 145));
            }
            geo.info.insert("ID",stop.idZDE);
            geoList << geo;
        }
    }
//    uistation.DoStationRequest();
    emit callFinished(geoList, RATP);
    reply->deleteLater();
}

void ApiRatp_Global::GotoStation()
{
    uistation.DoStationRequest(stationId);
}

void ApiRatp_Global::FilledTransportLists()
{
    RefStifJson();
}

QJsonDocument ApiRatp_Global::LoadJson(QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

// Mon identifiant au sein de l'enumération (classe mère)
Abstract_API::API_index ApiRatp_Global::getId()
{
    return RATP;
}

void ApiRatp_Global::getInfo()
{
    API_Access = new QNetworkAccessManager(this);

    QUrl url("");
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(GeoPoints(QNetworkReply *)));

    QApplication::setOverrideCursor(Qt::WaitCursor);
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiRatp_Global::getPixmap()
{
    return QPixmap(":/Icons/iconStation.png"); // icône PNG préférable
}
