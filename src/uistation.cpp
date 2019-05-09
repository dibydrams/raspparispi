#include "uistation.h"
#include "ui_uistation.h"

UiStation::UiStation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UiStation)
{
    ui->setupUi(this);

    connect(ui->ButtonNextPage, SIGNAL(clicked()), this, SLOT(ChangePage()));
}

UiStation::~UiStation()
{
    delete ui;
}

void UiStation::ChangePage()
{
    int newIndex = ui->StackedView->currentIndex() + 1;
    if (newIndex >= ui->StackedView->count())
        newIndex = 0;
    ui->StackedView->setCurrentIndex(newIndex);
}

void UiStation::DoStationRequest()
{
    managerStation = new QNetworkAccessManager(this);
    requestStation = new QNetworkRequest ();
    requestStation->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    /*
     *  Get ID (STIF:StopPoint:...) by clicked (parameters or for in ratpGlobal.stopPointList);
     */

//    QByteArray encodedCode = QUrl::toPercentEncoding(Get ID);
    requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef=STIF%3AStopPoint%3AQ%3A411414%3A"));
//    requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef="+encodedCode));

    replyStation = managerStation->get(*requestStation);

    connect(replyStation, &QNetworkReply::finished, this, &UiStation::replyFinishedStation);
}

void UiStation::DoStationRequest(QString _stationId)
{
    managerStation = new QNetworkAccessManager(this);
    requestStation = new QNetworkRequest ();
    requestStation->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    QByteArray encodedCode = QUrl::toPercentEncoding(_stationId);
    requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef="+encodedCode));

    replyStation = managerStation->get(*requestStation);

    connect(replyStation, &QNetworkReply::finished, this, &UiStation::replyFinishedStation);
}

void UiStation::replyFinishedStation()
{
//    qDebug() << replyStation->error();

    QJsonDocument doc = QJsonDocument::fromJson(replyStation->readAll());

    QJsonValue Siri = doc.object().value("Siri");

    // Object from Stop Monitoring Delivery
    QJsonArray SMDarray = Siri.toObject()["ServiceDelivery"].toObject()["StopMonitoringDelivery"].toArray();
    // Object from Monitored Stop Visit
    QJsonArray MSVarray = SMDarray[0].toObject()["MonitoredStopVisit"].toArray();

    showFinishedStation(MSVarray);
    replyStation->deleteLater();
    show();
}


void UiStation::showFinishedStation(QJsonArray resultArray)
{
    CleanView();

    ui->StackedView->hide();

    for (int i = 0; i < resultArray.count(); ++i)
    {
        bool isWidgetCreated = false;
        int widgetIndex = i;
        int span = 40;

        QString lineName = resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["MonitoredCall"].toObject()["StopPointName"].toArray().at(0).toObject()["value"].toString();
        ui->TitleLabel->setText(lineName);

        for (int id = 0; id < ui->StackedView->count(); ++id) {
            if (ui->StackedView->children().at(id)->objectName().contains(lineName))
            {
                isWidgetCreated = true;
                widgetIndex = id;
                break;
            }
        }

        if (!isWidgetCreated)
        {
            // Create new Widget in StackedWidget
            QWidget *newWidget = new QWidget(ui->StackedView);
            newWidget->setObjectName("page_" + lineName + "_" + QString::number(widgetIndex));
            ui->StackedView->addWidget(newWidget);

            widgetIndex = ui->StackedView->indexOf(newWidget);

            // Create Page Follower
            QLabel *pagination = new QLabel(ui->StackedView->widget(widgetIndex));
            pagination->setText("Page : " + QString::number(widgetIndex));
            pagination->move(ui->StackedView->geometry().topLeft());
        }


        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->StackedView->widget(widgetIndex));
        QLabel *labelForTime = new QLabel("Next train : ", ui->StackedView->widget(widgetIndex));
        QLabel *labelDest = new QLabel(ui->StackedView->widget(widgetIndex));
        QLabel *labelTime = new QLabel(ui->StackedView->widget(widgetIndex));

        labelForDest->move(ui->StackedView->geometry().left() + span, 0 + (span * (ui->StackedView->widget(widgetIndex)->children().count() / 4)));
        labelForTime->move(ui->StackedView->geometry().left() + span,  15 + (span * (ui->StackedView->widget(widgetIndex)->children().count() / 4)));
        labelDest->move(ui->StackedView->geometry().left() + labelForDest->geometry().width() + span, 0 + (span * (ui->StackedView->widget(widgetIndex)->children().count() / 4)));
        labelTime->move(ui->StackedView->geometry().left() + labelForTime->geometry().width() + span, 15 + (span * (ui->StackedView->widget(widgetIndex)->children().count() / 4)));

        labelDest->setText(resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationName"].toArray().at(0).toObject().value("value").toString());

        // Calcul next train
        QString str_arrivalTimeUTC = resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["MonitoredCall"].toObject()["ExpectedDepartureTime"].toString();
        QString str_nowUTC = resultArray[i].toObject()["RecordedAtTime"].toString();

        QDateTime arrivalTimeUTC = QDateTime::fromString(str_arrivalTimeUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        QDateTime nowUTC = QDateTime::fromString(str_nowUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        arrivalTimeUTC.setTimeSpec(Qt::UTC);
        nowUTC.setTimeSpec(Qt::UTC);
        qint64 remainingTime = nowUTC.secsTo(arrivalTimeUTC);

        labelTime->setText(QDateTime::fromTime_t(remainingTime).toUTC().toString("mm") + " min");

    }
    ui->StackedView->show();
}

void UiStation::CleanView()
{
    if (ui->StackedView->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly).count() > 0)
    {
        qDeleteAll(ui->StackedView->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));
    }
}
