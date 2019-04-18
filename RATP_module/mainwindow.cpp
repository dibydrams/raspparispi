#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Q_INIT_RESOURCE(resources);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    requestGlobal = new QNetworkRequest () ;
    requestGlobal->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));
    requestGlobal->setUrl(QUrl("https://api-lab-trall-stif.opendata.stif.info/service/tr-globale-stif/estimated-timetable"));

    requestUni = new QNetworkRequest () ;
    requestUni->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));
    requestUni->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-vianavigo/departures?line_id=100110012%3A12&stop_point_id=stopPoint%3A59520"));

//    replyGlobal = manager->get(*requestGlobal);
//    replyUni = manager->get(*requestUni);

//    connect(replyGlobal, &QNetworkReply::finished, this, &MainWindow::replyFinishedGlobal);
//    connect(replyUni, &QNetworkReply::finished, this, &MainWindow::replyFinishedUni);

    ReadLocalJson();
}

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

void MainWindow::replyFinishedGlobal()
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

    for (int i = 0; i < EVJArray.count(); i++) {
        if(i == 0){
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

//    NetworkCleanup();
    qDebug() << "end Finished Global" << endl;
}

void MainWindow::replyFinishedUni()
{
    QJsonDocument doc = QJsonDocument::fromJson(replyUni->readAll());
    rootObject = doc.object();

    QJsonArray arrayDoc = doc.array();

    for (int i = 0; i < arrayDoc.count(); i++) {
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

void MainWindow::ReadLocalJson()
{
    qDebug() << "start ReadJson";
    QFile doc(":/Data/Databases/perimetre-tr-plateforme-stif.json");
    qDebug() << doc.fileName();

}

//void MainWindow::NetworkCleanup()
//{
//    reply->deleteLater();
//    reply = nullptr;

//    replydata->clear();
//}
