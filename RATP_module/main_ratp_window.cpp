
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
     *
     * Faire une recherche des gares proches GPS, faire la requete JustGare
     * Afficher une page par transport pour la gare concernée
     *
     *
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

//    qDebug() << encodedIdZde << encodedCodeline;

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

    int span = 40;

    ui->widgetTimeView->hide();
    for (int i = 0; i < arrayDoc.count(); i++)
    {

        /*
         * TODO
         *
         * Faire une view Scrollable
         *
         */


        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->widgetTimeView);
        QLabel *labelForTime = new QLabel("Next train : ", ui->widgetTimeView);
        QLabel *labelDest = new QLabel(ui->widgetTimeView);
        QLabel *labelTime = new QLabel(ui->widgetTimeView);

        labelForDest->move(ui->widgetTimeView->geometry().left() + span, 0 + (span * i));
        labelForTime->move(ui->widgetTimeView->geometry().left() + span, 15 + (span * i));
        labelDest->move(ui->widgetTimeView->geometry().left() + labelForDest->geometry().width() + span, 0 + (span * i));
        labelTime->move(ui->widgetTimeView->geometry().left() + labelForTime->geometry().width() + span, 15 + (span * i));

        labelDest->setText(arrayDoc[i].toObject().value("lineDirection").toString());

//        qDebug() << "Code" << arrayDoc[i].toObject().value("code").toString();
//        qDebug() << "Line Direction" << arrayDoc[i].toObject().value("lineDirection").toString();
//        qDebug() << "Sens" << arrayDoc[i].toObject().value("sens").toString();
//        qDebug() << "Short Name" << arrayDoc[i].toObject().value("shortName").toString();

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

    }
    ui->widgetTimeView->show();
}

void Main_RATP_Window::replyFinishedStation()
{
//    qDebug() << replyStation->error();
    QJsonDocument doc = QJsonDocument::fromJson(replyStation->readAll());
    rootObject = doc.object();
    QJsonValue Siri = rootObject.value("Siri");


    // Object from Stop Monitoring Delivery
    QJsonArray SMDarray = Siri.toObject()["ServiceDelivery"].toObject()["StopMonitoringDelivery"].toArray();
    // Object from Monitored Stop Visit
    QJsonArray MSVarray = SMDarray[0].toObject()["MonitoredStopVisit"].toArray();

    for (int i = 0; i < MSVarray.count(); ++i)
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

        bool isWidgetCreated = false;
        int widgetIndex = i;
        int span = 40;
        QString lineName = MSVarray[i].toObject()["MonitoredVehicleJourney"].toObject()["LineRef"].toObject().value("value").toString();

        for (int id = 0; id < ui->stackedWidget->count(); ++id) {
            if (ui->stackedWidget->children().at(id)->objectName().contains(lineName))
            {
                isWidgetCreated = true;
                widgetIndex = id;
                qDebug() << "Count " << ui->stackedWidget->count() << "Index of Widg" << widgetIndex << "is Created ?" << isWidgetCreated;
                break;
            }
        }

        if (!isWidgetCreated)
        {
            // Create new Widget in StackedWidget
            QWidget *newWidget = new QWidget(ui->stackedWidget);
            newWidget->setObjectName("page_" + lineName);
            qDebug() << "Widget Name" << newWidget->objectName() << endl;
            ui->stackedWidget->addWidget(newWidget);

            widgetIndex = ui->stackedWidget->indexOf(newWidget);

            // Create Page Follower
            QLabel *pagination = new QLabel(ui->stackedWidget->widget(widgetIndex));
            pagination->setText(QString::number(widgetIndex));
            pagination->move(ui->stackedWidget->geometry().right() - 50, ui->stackedWidget->geometry().bottom() - 50);

            QLabel *title = new QLabel (lineName, ui->stackedWidget->widget(widgetIndex));
            title->move(ui->stackedWidget->widget(widgetIndex)->geometry().center().x(), 0);
        }

        ui->stackedWidget->widget(widgetIndex)->hide();

        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->stackedWidget->widget(widgetIndex));
        QLabel *labelForTime = new QLabel("Next train : ", ui->stackedWidget->widget(widgetIndex));
        QLabel *labelDest = new QLabel(ui->stackedWidget->widget(widgetIndex));
        QLabel *labelTime = new QLabel(ui->stackedWidget->widget(widgetIndex));

        labelForDest->move(ui->stackedWidget->geometry().left() + span, 20 + (span * (ui->stackedWidget->widget(widgetIndex)->children().count() / 4)));
        labelForTime->move(ui->stackedWidget->geometry().left() + span,  35 + (span * (ui->stackedWidget->widget(widgetIndex)->children().count() / 4)));
        labelDest->move(ui->stackedWidget->geometry().left() + labelForDest->geometry().width() + span, 20 + (span * (ui->stackedWidget->widget(widgetIndex)->children().count() / 4)));
        labelTime->move(ui->stackedWidget->geometry().left() + labelForTime->geometry().width() + span, 35 + (span * (ui->stackedWidget->widget(widgetIndex)->children().count() / 4)));

        labelDest->setText(MSVarray[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationName"].toArray().at(0).toObject().value("value").toString());

        // Calcul prochain train
        QString str_arrivalTimeUTC = MSVarray[i].toObject()["MonitoredVehicleJourney"].toObject()["MonitoredCall"].toObject()["ExpectedDepartureTime"].toString();
        QString str_nowUTC = MSVarray[i].toObject()["RecordedAtTime"].toString();

        QDateTime arrivalTimeUTC = QDateTime::fromString(str_arrivalTimeUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        QDateTime nowUTC = QDateTime::fromString(str_nowUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        arrivalTimeUTC.setTimeSpec(Qt::UTC);
        nowUTC.setTimeSpec(Qt::UTC);
        qint64 remainingTime = nowUTC.secsTo(arrivalTimeUTC);

        labelTime->setText(QDateTime::fromTime_t(remainingTime).toUTC().toString("mm") + " min");

        ui->stackedWidget->widget(widgetIndex)->show();

//        qDebug() << "PRINCIPAL " << truc[i].toObject() << endl;

//        qDebug() << "111" << truc[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationName"].toArray().at(0).toObject().value("value").toString() << endl;
//        qDebug() << "222 " << truc[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationRef"] << endl;
//        qDebug() << "333 " << MSVarray[i].toObject()["MonitoredVehicleJourney"].toObject()["LineRef"].toObject().value("value").toString() << endl;
//        qDebug() << "444 " << MSVarray[i].toObject()["MonitoredVehicleJourney"] << endl;
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
            rerList.append(newTransport);
        }
    }

    std::sort(busList.begin(), busList.end(), Transport::compareTransports);
    std::sort(metroList.begin(), metroList.end(), Transport::compareTransports);
    std::sort(rerList.begin(), rerList.end(), Transport::compareTransports);
}

void Main_RATP_Window::CleanUniRequestView()
{
    if (ui->widgetTimeView->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly).count() > 0)
    {
        qDeleteAll(ui->widgetTimeView->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));
    }
}

