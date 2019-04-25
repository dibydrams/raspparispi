#include "main_ratp_window.h"
#include "ui_main_ratp_window.h"

Main_RATP_Window::Main_RATP_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_RATP_Window)
{
    ui->setupUi(this);

    Q_INIT_RESOURCE(resources);


    /*
     * A faire
     *
     * 1) Créer une classe Transport qui faire des objets avec RefJSON
     * Utiliser les noms communs pour l'affichage (plus de CODE !!!!!)
     *
     *
     * Faire une recherche des gares proches GPS, faire la requete JustGare
     * pour avoir un affichage simple sur une premiere page
     *
     *
     * En fonction de la check box, afficher les transports
     * En fonction du transport choisi, afficher les gares
     * En fonction de la gare, faire la requete et afficher les prochains trains
     *
     *
     * 2) Gestion des erreurs de requêtes
     *
     */



    // TEST





    // End TEST

    perimetreStifJson = Tools::LoadJson(":/Data/Databases/perimetre-tr-plateforme-stif.json");
    PeriJson();
    referentielStifJson = Tools::LoadJson(":/Data/Databases/referentiel-des-lignes-stif.json");
    RefJson();

    connect(ui->radioBus, SIGNAL(clicked()), this, SLOT(ShowTransports()));
    connect(ui->radioMetro, SIGNAL(clicked()), this, SLOT(ShowTransports()));
    connect(ui->radioRer, SIGNAL(clicked()), this, SLOT(ShowTransports()));

    manager = new QNetworkAccessManager(this);
    DoStationOnlyRequest();
//    ShowUni();
}

Main_RATP_Window::~Main_RATP_Window()
{
    delete manager;
    delete ui;
}

void Main_RATP_Window::ShowTransports()
{
    disconnect(ui->comboTransport, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowTransportStopPoints(int)));

    ui->comboTransport->clear();
    ui->comboStation->clear();

    ui->comboTransport->addItem("");

    if (ui->radioBus->isChecked())
    {
        for (int i = 0; i < busList.count(); ++i)
        {
            ui->comboTransport->addItem(busList[i].nameShowed);
        }
    }

    if (ui->radioMetro->isChecked())
    {
        for (int i = 0; i < metroList.count(); ++i)
        {
            ui->comboTransport->addItem(metroList[i].nameShowed);
        }
    }

    if (ui->radioRer->isChecked())
    {
        for (int i = 0; i < rerList.count(); ++i)
        {
            ui->comboTransport->addItem(rerList[i].nameShowed);
        }
    }

    connect(ui->comboTransport, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowTransportStopPoints(int)));
}

void Main_RATP_Window::ShowTransportStopPoints(int _code)
{
    ui->comboStation->clear();
    _code -= 1;

    if (ui->radioBus->isChecked())
    {
        for (int i = 0; i < stopPointList.count(); ++i)
        {
            if (stopPointList[i].externalcodeLine == busList[_code].codeLine)
            {
                ui->comboStation->addItem(stopPointList[i].nomZDE);
            }
        }
    }

    if (ui->radioMetro->isChecked())
    {
        for (int i = 0; i < stopPointList.count(); ++i)
        {
            if (stopPointList[i].externalcodeLine == metroList[_code].codeLine)
            {
                ui->comboStation->addItem(stopPointList[i].nomZDE);
            }
        }
    }

    if (ui->radioRer->isChecked())
    {
        for (int i = 0; i < stopPointList.count(); ++i)
        {
            if (stopPointList[i].externalcodeLine == rerList[_code].codeLine)
            {
                ui->comboStation->addItem(stopPointList[i].nomZDE);
            }
        }
    }


}


void Main_RATP_Window::DoGlobalRequest()
{
    requestGlobal = new QNetworkRequest () ;
    requestGlobal->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));
    requestGlobal->setUrl(QUrl("https://api-lab-trall-stif.opendata.stif.info/service/tr-globale-stif/estimated-timetable"));

    replyGlobal = manager->get(*requestGlobal);

    connect(replyGlobal, &QNetworkReply::finished, this, &Main_RATP_Window::replyFinishedGlobal);
}

void Main_RATP_Window::DoUniRequest(int _index)
{
    requestUni = new QNetworkRequest () ;
    requestUni->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    QByteArray encodedCodeline = QUrl::toPercentEncoding(stopPointList[_index].externalcodeLine);
    QByteArray encodedID = QUrl::toPercentEncoding(stopPointList[_index].idZDE.replace(0,1,"s"));

    qDebug() << encodedID << encodedCodeline;

    requestUni->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-vianavigo/departures?line_id="+encodedCodeline+"&stop_point_id="+encodedID));

    replyUni = manager->get(*requestUni);

    connect(replyUni, &QNetworkReply::finished, this, &Main_RATP_Window::replyFinishedUni);
}

void Main_RATP_Window::DoStationOnlyRequest()
{
    requestStation = new QNetworkRequest () ;
    requestStation->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    QStringList monoRefList;
    for (int i = 0; i < stopPointList.count(); ++i) //2.34575 48.8711687
    {
        if (stopPointList[i].coordsZDE.rx() > 2.34505 && stopPointList[i].coordsZDE.rx() < 2.34605)
        {
            monoRefList.append(stopPointList[i].monoRefZDE);
        }
    }

//    foreach (QString code, monoRefList) {
        QByteArray encodedCode = "";//QUrl::toPercentEncoding(monoRefList[0]);
        requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef="+encodedCode+"STIF%3AStopPoint%3AQ%3A22102%3A"));

        replyStation = manager->get(*requestStation);

        connect(replyStation, &QNetworkReply::finished, this, &Main_RATP_Window::replyFinishedStation);
//    }
}

void Main_RATP_Window::replyFinishedGlobal()
{
    QJsonDocument doc = QJsonDocument::fromJson(replyGlobal->readAll());
    rootObject = doc.object();

    QJsonValue Siri = rootObject.value("Siri");

    // Object from Service Delivery
    QJsonObject SDObj = Siri.toObject()["ServiceDelivery"].toObject();

    // Array from Estimated Timetable Delivery
    QJsonArray ETtDArray = SDObj["EstimatedTimetableDelivery"].toArray();

    // Array from Estimated Journey Version Frame
    QJsonArray EJVFArray = ETtDArray[0].toObject()["EstimatedJourneyVersionFrame"].toArray();

    // Array from Estimated Vehicle Journey
    QJsonArray EVJArray = EJVFArray[0].toObject()["EstimatedVehicleJourney"].toArray();

    for (int i = 0; i < EVJArray.count(); i++)
    {
        if(i == 0)
        {
            qDebug() << "keys" << EVJArray[i].toObject().keys();

        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("DatedVehicleJourneyRef").toObject().value("value").toString();
        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("DestinationName").toObject();
        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("DestinationRef").toObject().value("value").toString();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("DirectionName").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("DirectionRef").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("EstimatedCalls").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("FirstOrLastJourney").toObject().value("value").toInt();
        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("JourneyNote").toObject().value("value").toInt();
        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("LineRef").toObject().value("value").toString();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("OperatorRef").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("OriginRef").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("ProductCategoryRef").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("PublishedLineName").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("RecordedAtTime").toObject().value("value").toInt();
//        qDebug() << "Truc :"<< i << " " << EVJArray[i].toObject().value("RouteRef").toObject().value("value").toInt() << endl;
        }
    }

    qDebug() << "end Finished Global" << endl;
}

void Main_RATP_Window::replyFinishedUni()
{
    qDebug() << replyUni->error();
    QJsonDocument doc = QJsonDocument::fromJson(replyUni->readAll());

    QJsonArray arrayDoc = doc.array();

    for (int i = 0; i < arrayDoc.count(); i++)
    {
        qDebug() << "Code" << arrayDoc[i].toObject().value("code").toString();
        qDebug() << "Line Direction" << arrayDoc[i].toObject().value("lineDirection").toString();
        qDebug() << "Sens" << arrayDoc[i].toObject().value("sens").toString();
        qDebug() << "Short Name" << arrayDoc[i].toObject().value("shortName").toString();

        if (arrayDoc[i].toObject().value("time").toString() == "")
        {
            qDebug() << "Schedule" << arrayDoc[i].toObject().value("schedule").toString() << endl;
        }
        else
        {
            qDebug() << "Time" << arrayDoc[i].toObject().value("time").toString() << endl;
        }
    }
}

void Main_RATP_Window::replyFinishedStation()
{
    qDebug() << replyStation->error();
    QJsonDocument doc = QJsonDocument::fromJson(replyStation->readAll());
    rootObject = doc.object();

    QJsonValue Siri = rootObject.value("Siri");

    // Object from Service Delivery
    QJsonArray SDObj = Siri.toObject()["ServiceDelivery"].toObject()["StopMonitoringDelivery"].toArray();
    QJsonArray truc = SDObj[0].toObject()["MonitoredStopVisit"].toArray();

    for (int i = 0; i < truc.count(); ++i) {
        qDebug() << "arrayDoc" << truc[i].toObject();
    }
}

void Main_RATP_Window::PeriJson()
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

//        if (i == 1324)
//        {
////            qDebug() << "Coordonnées: " <<  coordX;
////            qDebug() << "Coordonnées: " <<  QString::number(coordX, 'g', 16) << "\t" << QString::number(coordY, 'g', 16) << "\n";
//        }
//        QString blabla = QString::number(coordX, 'g', 16);
//        bool ok = false;
//        blabla.toLong(&ok, 16);

        pointList.append(coordsZDE);
        StopPoint newStopPoint(externalcodeLine, nomZDE, monoRefZDE, idZDE, coordsZDE, i);
        stopPointList.append(newStopPoint);
    }

    std::sort(stopPointList.begin(), stopPointList.end(), StopPoint::compareStopPoint);
}

void Main_RATP_Window::RefJson()
{
    for (int i = 0; i < referentielStifJson.array().count(); ++i)
    {
        QString codeLine = referentielStifJson.array().at(i).toObject()["fields"].toObject()["externalcode_line"].toString();
        QString shortnameLine = referentielStifJson.array().at(i).toObject()["fields"].toObject()["shortname_line"].toString();
        QString shortnameGroupoflines = referentielStifJson.array().at(i).toObject()["fields"].toObject()["shortname_groupoflines"].toString();
        QString networkname = referentielStifJson.array().at(i).toObject()["fields"].toObject()["networkname"].toString();
        QString transportmode = referentielStifJson.array().at(i).toObject()["fields"].toObject()["transportmode"].toString();
        int accessibility = referentielStifJson.array().at(i).toObject()["fields"].toObject()["accessibility"].toInt();

        Transport newTransport(codeLine, shortnameLine, shortnameGroupoflines, networkname, transportmode, accessibility, i);

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
            rerList.append(newTransport);
        }
    }

    std::sort(busList.begin(), busList.end(), Transport::compareTransports);
    std::sort(metroList.begin(), metroList.end(), Transport::compareTransports);
    std::sort(rerList.begin(), rerList.end(), Transport::compareTransports);
}

