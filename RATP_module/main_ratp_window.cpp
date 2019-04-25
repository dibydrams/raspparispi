
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
    connect(ui->ToNextPage_2, SIGNAL(clicked()), this, SLOT(ChangePage()));

    // End TEST

    perimetreStifJson = Tools::LoadJson(":/Data/Databases/perimetre-tr-plateforme-stif.json");
    PeriJson();
    referentielStifJson = Tools::LoadJson(":/Data/Databases/referentiel-des-lignes-stif.json");
    RefJson();

    connect(ui->radioBus, SIGNAL(clicked()), this, SLOT(ShowTransports()));
    connect(ui->radioMetro, SIGNAL(clicked()), this, SLOT(ShowTransports()));
    connect(ui->radioRer, SIGNAL(clicked()), this, SLOT(ShowTransports()));

    connect(ui->pushUniReq, SIGNAL(clicked()), this, SLOT(CleanUniRequestView()));

    manager = new QNetworkAccessManager(this);
    DoStationOnlyRequest();
}

void Main_RATP_Window::ChangePage()
{
    int newIndex = ui->stackedWidget->currentIndex() + 1;
    if (newIndex >= ui->stackedWidget->count())
        newIndex = 0;
    ui->stackedWidget->setCurrentIndex(newIndex);
}

Main_RATP_Window::~Main_RATP_Window()
{
    delete manager;
    delete ui;
}

void Main_RATP_Window::ShowTransports()
{
    ui->pushUniReq->setEnabled(false);
    disconnect(ui->comboTransport, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowTransportStopPoints(int)));
    disconnect(ui->comboTransport, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniTransportIndex(int)));

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
    connect(ui->comboTransport, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniTransportIndex(int)));
}

void Main_RATP_Window::ShowTransportStopPoints(int _code)
{
    disconnect(ui->comboStation, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniStationIndex(int)));
    disconnect(ui->pushUniReq, SIGNAL(clicked()), this, SLOT(DoUniRequest()));

    ui->comboStation->clear();
    _code -= 1;

    if (ui->radioBus->isChecked())
    {
        for (int i = 0; i < busList[_code].mySPList.count(); ++i)
        {
            ui->comboStation->addItem(busList[_code].mySPList[i].nomZDE);
        }
    }

    if (ui->radioMetro->isChecked())
    {
        for (int i = 0; i < metroList[_code].mySPList.count(); ++i)
        {
            ui->comboStation->addItem(metroList[_code].mySPList[i].nomZDE);
        }
    }

    if (ui->radioRer->isChecked())
    {
        for (int i = 0; i < rerList[_code].mySPList.count(); ++i)
        {
            ui->comboStation->addItem(rerList[_code].mySPList[i].nomZDE);
        }
    }

    ui->pushUniReq->setEnabled(true);
    connect(ui->comboStation, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniStationIndex(int)));
    connect(ui->pushUniReq, SIGNAL(clicked()), this, SLOT(DoUniRequest()));
}

void Main_RATP_Window::SetUniTransportIndex(int _codeT)
{
    if (_codeT != -1)
        indexTranspForUniReq = _codeT - 1;
}

void Main_RATP_Window::SetUniStationIndex(int _codeS)
{
    if(_codeS != -1)
        indexStationForUniReq = _codeS;
}


void Main_RATP_Window::DoGlobalRequest()
{
    requestGlobal = new QNetworkRequest () ;
    requestGlobal->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));
    requestGlobal->setUrl(QUrl("https://api-lab-trall-stif.opendata.stif.info/service/tr-globale-stif/estimated-timetable"));

    replyGlobal = manager->get(*requestGlobal);

    connect(replyGlobal, &QNetworkReply::finished, this, &Main_RATP_Window::replyFinishedGlobal);
}

void Main_RATP_Window::DoUniRequest()
{
    requestUni = new QNetworkRequest () ;
    requestUni->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    QByteArray encodedCodeline;
    QByteArray encodedIdZde;
//    qDebug() << "code Transport" << indexTranspForUniReq << "code Station" << indexStationForUniReq;

    if (ui->radioBus->isChecked())
    {
        encodedCodeline = QUrl::toPercentEncoding(busList[indexTranspForUniReq].codeLine);
        encodedIdZde = QUrl::toPercentEncoding(busList[indexTranspForUniReq].mySPList[indexStationForUniReq].idZDE.replace(0,1,"s"));
    }
    else if (ui->radioMetro->isChecked())
    {
        encodedCodeline = QUrl::toPercentEncoding(metroList[indexTranspForUniReq].codeLine);
        encodedIdZde = QUrl::toPercentEncoding(metroList[indexTranspForUniReq].mySPList[indexStationForUniReq].idZDE.replace(0,1,"s"));
    }
    else
    {
        encodedCodeline = QUrl::toPercentEncoding(rerList[indexTranspForUniReq].codeLine);
        encodedIdZde = QUrl::toPercentEncoding(rerList[indexTranspForUniReq].mySPList[indexStationForUniReq].idZDE.replace(0,1,"s"));
    }

    qDebug() << encodedIdZde << encodedCodeline;

    requestUni->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-vianavigo/departures?line_id="+encodedCodeline+"&stop_point_id="+encodedIdZde));

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
        if (stopPointList[i].coordsZDE.rx() > 2.34405 && stopPointList[i].coordsZDE.rx() < 2.34605)
        {
//            qDebug() << stopPointList[i].monoRefZDE;
            monoRefList.append(stopPointList[i].monoRefZDE);
        }
    }

//    foreach (QString code, monoRefList) {
        QByteArray encodedCode = "";//QUrl::toPercentEncoding(code);
        requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef="+encodedCode+"STIF%3AStopPoint%3AQ%3A411414%3A"));
//        requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef="+encodedCode));

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

    int span = 20;

    for (int i = 0; i < arrayDoc.count(); i++)
    {
        ui->widgetTimeView->hide();
        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->widgetTimeView);
        QLabel *labelForTime = new QLabel("Next train : ", ui->widgetTimeView);
        QLabel *labelDest = new QLabel(ui->widgetTimeView);
        QLabel *labelTime = new QLabel(ui->widgetTimeView);

        labelForDest->move(ui->widgetTimeView->geometry().left() + labelDest->geometry().size().width(), ui->widgetTimeView->geometry().center().ry() - (span * i));
        labelForTime->move(ui->widgetTimeView->geometry().center().rx() - labelTime->geometry().size().width(), ui->widgetTimeView->geometry().center().ry());
        labelDest->move(ui->widgetTimeView->geometry().center().rx(), ui->widgetTimeView->geometry().center().ry() - (span * i));
        labelTime->move(ui->widgetTimeView->geometry().center().rx(), ui->widgetTimeView->geometry().center().ry());

        labelDest->setText(arrayDoc[i].toObject().value("lineDirection").toString());

        qDebug() << "Code" << arrayDoc[i].toObject().value("code").toString();
        qDebug() << "Line Direction" << arrayDoc[i].toObject().value("lineDirection").toString();
        qDebug() << "Sens" << arrayDoc[i].toObject().value("sens").toString();
        qDebug() << "Short Name" << arrayDoc[i].toObject().value("shortName").toString();

        if (arrayDoc[i].toObject().value("time").toString() == "")
        {
            qDebug() << "Schedule" << arrayDoc[i].toObject().value("schedule").toString() << endl;
            labelTime->setText(arrayDoc[i].toObject().value("schedule").toString());
        }
        else
        {
            qDebug() << "Time" << arrayDoc[i].toObject().value("time").toString() << endl;
            labelTime->setText(arrayDoc[i].toObject().value("time").toString());
        }

        ui->widgetTimeView->show();
    }
}

void Main_RATP_Window::replyFinishedStation()
{
//    qDebug() << replyStation->error();
    QJsonDocument doc = QJsonDocument::fromJson(replyStation->readAll());
    rootObject = doc.object();
    QJsonValue Siri = rootObject.value("Siri");


    // Object from Service Delivery
    QJsonArray SDObj = Siri.toObject()["ServiceDelivery"].toObject()["StopMonitoringDelivery"].toArray();
    QJsonArray truc = SDObj[0].toObject()["MonitoredStopVisit"].toArray();

    for (int i = 0; i < truc.count(); ++i)
    {
        /*
         * foreach widget in stackedwidget
         *  if widget.name.contains( truc.trainID)
         *      add labels
         *      at good pos (center + (span * nbOfDuoLabels)
         *  else
         *      create newWidget
         *      newWidget.name = page_ + truc.trainID
         *      add labels
         *      at good pos
         */





        // Create new Widget in StackedWidget
        QWidget *newWidget = new QWidget(ui->stackedWidget);
        newWidget->setObjectName("page_" + QString::number(i));
        ui->stackedWidget->addWidget(newWidget);
        newWidget->hide();

        // Create Page Follower
        QLabel *pagination = new QLabel(newWidget);
        pagination->setText(QString::number(i + 1) + " / " + QString::number(truc.count()));
        pagination->move(ui->stackedWidget->currentWidget()->geometry().right() - 50, ui->stackedWidget->currentWidget()->geometry().bottom() - 50);

        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", newWidget);
        QLabel *labelForTime = new QLabel("Next train : ", newWidget);
        QLabel *labelDest = new QLabel(newWidget);
        QLabel *labelTime = new QLabel(newWidget);

        labelForDest->move(ui->stackedWidget->currentWidget()->geometry().center().rx() - labelDest->geometry().size().width(), ui->stackedWidget->currentWidget()->geometry().center().ry() - 25);
        labelForTime->move(ui->stackedWidget->currentWidget()->geometry().center().rx() - labelTime->geometry().size().width(), ui->stackedWidget->currentWidget()->geometry().center().ry());
        labelDest->move(ui->stackedWidget->currentWidget()->geometry().center().rx(), ui->stackedWidget->currentWidget()->geometry().center().ry() - 25);
        labelTime->move(ui->stackedWidget->currentWidget()->geometry().center().rx(), ui->stackedWidget->currentWidget()->geometry().center().ry());

        labelDest->setText(truc[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationName"].toArray().at(0).toObject().value("value").toString());

        // Calcul prochain train
        QString str_arrivalTimeUTC = truc[i].toObject()["MonitoredVehicleJourney"].toObject()["MonitoredCall"].toObject()["ExpectedDepartureTime"].toString();
        QString str_nowUTC = truc[i].toObject()["RecordedAtTime"].toString();

        QDateTime arrivalTimeUTC = QDateTime::fromString(str_arrivalTimeUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        QDateTime nowUTC = QDateTime::fromString(str_nowUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        arrivalTimeUTC.setTimeSpec(Qt::UTC);
        nowUTC.setTimeSpec(Qt::UTC);
        qint64 remainingTime = nowUTC.secsTo(arrivalTimeUTC);

        labelTime->setText(QDateTime::fromTime_t(remainingTime).toUTC().toString("mm") + " min");
        newWidget->show();

//        qDebug() << "PRINCIPAL " << truc[i].toObject() << endl;

//        qDebug() << "111" << truc[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationName"].toArray().at(0).toObject().value("value").toString() << endl;
//        qDebug() << "222 " << truc[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationRef"] << endl;
//        qDebug() << "333 " << truc[i].toObject()["MonitoredVehicleJourney"].toObject()["LineRef"] << endl;
//        qDebug() << "444 " << truc[i].toObject()["MonitoredVehicleJourney"].toObject()["MonitoredCall"] << endl;
//        qDebug() << "444 " << truc[i].toObject()["RecordedAtTime"].toString() << endl
    }

    qDebug() << "Fini !" << endl;

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
            rerList.append(newTransport);
        }
    }

    std::sort(busList.begin(), busList.end(), Transport::compareTransports);
    std::sort(metroList.begin(), metroList.end(), Transport::compareTransports);
    std::sort(rerList.begin(), rerList.end(), Transport::compareTransports);
}

void Main_RATP_Window::CleanUniRequestView()
{
    qDeleteAll(ui->widgetTimeView->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
}

