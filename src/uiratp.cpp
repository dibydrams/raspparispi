#include "uiratp.h"
#include "ui_uiratp.h"

Uiratp::Uiratp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Uiratp)
{
    ui->setupUi(this);

}

Uiratp::~Uiratp()
{
    delete ui;
}

void Uiratp::showFinishedStation(QJsonArray resultArray)
{
    ui->MainStackedWidget->setCurrentWidget(ui->StationPage);
    show();

    for (int i = 0; i < resultArray.count(); ++i)
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
        QString lineName = resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["LineRef"].toObject().value("value").toString();

        for (int id = 0; id < ui->StationWidget->count(); ++id) {
            if (ui->StationWidget->children().at(id)->objectName().contains(lineName))
            {
                isWidgetCreated = true;
                widgetIndex = id;
//                qDebug() << "Count " << ui->StationWidget->count() << "Index of Widg" << widgetIndex << "is Created ?" << isWidgetCreated;
                break;
            }
        }

        if (!isWidgetCreated)
        {
            // Create new Widget in StackedWidget
            QWidget *newWidget = new QWidget(ui->StationWidget);
            newWidget->setObjectName("page_" + lineName);
//            qDebug() << "Widget Name" << newWidget->objectName() << endl;
            ui->StationWidget->addWidget(newWidget);

            widgetIndex = ui->StationWidget->indexOf(newWidget);

            // Create Page Follower
            QLabel *pagination = new QLabel(ui->StationWidget->widget(widgetIndex));
            pagination->setText(QString::number(widgetIndex));
            pagination->move(ui->StationWidget->geometry().right() - 50, ui->StationWidget->geometry().bottom() - 50);

            QLabel *title = new QLabel (lineName, ui->StationWidget->widget(widgetIndex));
            title->move(ui->StationWidget->widget(widgetIndex)->geometry().center().x(), 0);
        }

        ui->StationWidget->widget(widgetIndex)->hide();

        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->StationWidget->widget(widgetIndex));
        QLabel *labelForTime = new QLabel("Next train : ", ui->StationWidget->widget(widgetIndex));
        QLabel *labelDest = new QLabel(ui->StationWidget->widget(widgetIndex));
        QLabel *labelTime = new QLabel(ui->StationWidget->widget(widgetIndex));

        labelForDest->move(ui->StationWidget->geometry().left() + span, 20 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));
        labelForTime->move(ui->StationWidget->geometry().left() + span,  35 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));
        labelDest->move(ui->StationWidget->geometry().left() + labelForDest->geometry().width() + span, 20 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));
        labelTime->move(ui->StationWidget->geometry().left() + labelForTime->geometry().width() + span, 35 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));

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

        ui->StationWidget->widget(widgetIndex)->show();
    }
}


void Uiratp::ShowTransports()
{
    ui->RequestButton->setEnabled(false);
    disconnect(ui->TransportCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowTransportStopPoints(int)));
    disconnect(ui->TransportCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniTransportIndex(int)));

    ui->TransportCombo->clear();
    ui->StationCombo->clear();

    ui->TransportCombo->addItem("");

    if (ui->BusRadio->isChecked())
    {
        for (int i = 0; i < ratpGlobal.busList.count(); ++i)
        {
            ui->TransportCombo->addItem(ratpGlobal.busList[i].nameShowed);
        }
    }

    if (ui->MetroRadio->isChecked())
    {
        for (int i = 0; i < ratpGlobal.metroList.count(); ++i)
        {
            ui->TransportCombo->addItem(ratpGlobal.metroList[i].nameShowed);
        }
    }

    if (ui->RailRadio->isChecked())
    {
        for (int i = 0; i < ratpGlobal.railList.count(); ++i)
        {
            ui->TransportCombo->addItem(ratpGlobal.railList[i].nameShowed);
        }
    }

    connect(ui->TransportCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowTransportStopPoints(int)));
    connect(ui->TransportCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniTransportIndex(int)));
}

void Uiratp::ShowTransportStopPoints(int _code)
{
    disconnect(ui->StationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniStationIndex(int)));
    disconnect(ui->RequestButton, SIGNAL(clicked()), this, SLOT(ratpGlobal.DoUniRequest()));

    ui->StationCombo->clear();
    _code -= 1;

    if (ui->BusRadio->isChecked())
    {
        for (int i = 0; i < ratpGlobal.busList[_code].mySPList.count(); ++i)
        {
            ui->StationCombo->addItem(ratpGlobal.busList[_code].mySPList[i].nomZDE);
        }
    }

    if (ui->MetroRadio->isChecked())
    {
        for (int i = 0; i < ratpGlobal.metroList[_code].mySPList.count(); ++i)
        {
            ui->StationCombo->addItem(ratpGlobal.metroList[_code].mySPList[i].nomZDE);
        }
    }

    if (ui->RailRadio->isChecked())
    {
        for (int i = 0; i < ratpGlobal.railList[_code].mySPList.count(); ++i)
        {
            ui->StationCombo->addItem(ratpGlobal.railList[_code].mySPList[i].nomZDE);
        }
    }

    ui->RequestButton->setEnabled(true);
    connect(ui->StationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniStationIndex(int)));
    connect(ui->RequestButton, SIGNAL(clicked()), this, SLOT(ratpGlobal.DoUniRequest()));
}

void Uiratp::SetUniTransportIndex(int _codeT)
{
    if (_codeT != -1)
        ratpGlobal.indexTranspForUniReq = _codeT - 1;
}

void Uiratp::SetUniStationIndex(int _codeS)
{
    if(_codeS != -1)
        ratpGlobal.indexStationForUniReq = _codeS;
}

void Uiratp::showFinishedUni(QJsonArray resultArray)
{
    ui->MainStackedWidget->setCurrentWidget(ui->UniPage);

    int span = 40;

    ui->UniPage->hide();
    for (int i = 0; i < resultArray.count(); i++)
    {

        /*
         * TODO
         *
         * Faire une view Scrollable
         *
         */


        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->ScrollAreaContents);
        QLabel *labelForTime = new QLabel("Next train : ", ui->ScrollAreaContents);
        QLabel *labelDest = new QLabel(ui->ScrollAreaContents);
        QLabel *labelTime = new QLabel(ui->ScrollAreaContents);

        labelForDest->move(ui->ScrollAreaContents->geometry().left() + span, 0 + (span * i));
        labelForTime->move(ui->ScrollAreaContents->geometry().left() + span, 15 + (span * i));
        labelDest->move(ui->ScrollAreaContents->geometry().left() + labelForDest->geometry().width() + span, 0 + (span * i));
        labelTime->move(ui->ScrollAreaContents->geometry().left() + labelForTime->geometry().width() + span, 15 + (span * i));

        labelDest->setText(resultArray[i].toObject().value("lineDirection").toString());

//        qDebug() << "Code" << arrayDoc[i].toObject().value("code").toString();
//        qDebug() << "Line Direction" << arrayDoc[i].toObject().value("lineDirection").toString();
//        qDebug() << "Sens" << arrayDoc[i].toObject().value("sens").toString();
//        qDebug() << "Short Name" << arrayDoc[i].toObject().value("shortName").toString();

        if (resultArray[i].toObject().value("time").toString() == "")
        {
            qDebug() << "Schedule" << resultArray[i].toObject().value("schedule").toString() << endl;
            labelTime->setText(resultArray[i].toObject().value("schedule").toString());
        }
        else
        {
            qDebug() << "Time" << resultArray[i].toObject().value("time").toString() << endl;
            labelTime->setText(resultArray[i].toObject().value("time").toString());
        }

    }
    ui->UniPage->show();
}

