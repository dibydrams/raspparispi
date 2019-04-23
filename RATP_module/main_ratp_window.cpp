#include "main_ratp_window.h"
#include "ui_main_ratp_window.h"

Main_RATP_Window::Main_RATP_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_RATP_Window)
{
    ui->setupUi(this);

    Q_INIT_RESOURCE(resources);

    perimetreStifJson = Tools::LoadJson(":/Data/Databases/perimetre-tr-plateforme-stif.json");
    ReadSaveStifJson();

    uniReqWindow = new UniRequest (this);

    connect(ui->pushUni, SIGNAL(clicked()), this, SLOT(ShowUni()));

    uniReqWindow->UniStopPointList = stopPointList;

    connect(uniReqWindow, SIGNAL(finished(int)), this, SLOT(GetUniReqIndex(int)));

    manager = new QNetworkAccessManager(this);
}

Main_RATP_Window::~Main_RATP_Window()
{
    delete manager;
    delete ui;
}

void Main_RATP_Window::ShowUni()
{
    uniReqWindow->show();
    uniReqWindow->InitStopPointList();
}

void Main_RATP_Window::GetUniReqIndex(int)
{
    DoUniRequest(uniReqWindow->SavedIndex);
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
    QByteArray encodedID = QUrl::toPercentEncoding(stopPointList[_index].idZDE);

    qDebug() << encodedID << encodedCodeline;

    requestUni->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-vianavigo/departures?line_id="+encodedCodeline+"&stop_point_id="+encodedID));

    replyUni = manager->get(*requestUni);

    connect(replyUni, &QNetworkReply::finished, this, &Main_RATP_Window::replyFinishedUni);
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
    rootObject = doc.object();

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

void Main_RATP_Window::ReadSaveStifJson()
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
        idZDE.replace(0,1,"s");

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
}
