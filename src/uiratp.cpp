#include "uiratp.h"
#include "ui_uiratp.h"

Uiratp::Uiratp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Uiratp)
{
    ui->setupUi(this);

    this->setWindowTitle("Search Page");

    if (ratpGlobal.transportList.count() <= 0)
    {
        ratpGlobal.FilledTransportLists();
    }

    connect(ui->CloseButton, SIGNAL(clicked()), this, SLOT(hide()));

    connect(&ratpSearch, SIGNAL(ShowErrorUni(QString)), this, SLOT(ShowErrorUni(QString)));
    connect(&ratpSearch, SIGNAL(ShowFinishedUni(QJsonArray)), this, SLOT(ShowFinishedUni(QJsonArray)));

    connect(ui->BusRadio, SIGNAL(clicked()), this, SLOT(ShowTransports()));
    connect(ui->MetroRadio, SIGNAL(clicked()), this, SLOT(ShowTransports()));
    connect(ui->RailRadio, SIGNAL(clicked()), this, SLOT(ShowTransports()));
}

Uiratp::~Uiratp()
{
    delete ui;
}

void Uiratp::ShowTransports()
{
    ui->RequestButton->setEnabled(false);
    disconnect(ui->TransportCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowTransportStopPoints(int)));
    disconnect(ui->TransportCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniTransportIndex(int)));

    ui->TransportCombo->clear();
    ui->StationCombo->clear();

    ui->TransportCombo->addItem("");

    if (ratpGlobal.busList.count() <= 0)
    {
        foreach (Transport objTran, ratpGlobal.transportList)
        {
            if (objTran.transportMode == Transport::Modes::bus)
            {
                ratpGlobal.busList << objTran;
            }
        }

        std::sort(ratpGlobal.busList.begin(), ratpGlobal.busList.end(), Transport::compareTransports);
    }

    if (ratpGlobal.metroList.count() <= 0)
    {
        foreach (Transport objTran, ratpGlobal.transportList) {
            if (objTran.transportMode == Transport::Modes::metro)
            {
                ratpGlobal.metroList << objTran;
            }
        }

        std::sort(ratpGlobal.metroList.begin(), ratpGlobal.metroList.end(), Transport::compareTransports);
    }

    if (ratpGlobal.railList.count() <= 0)
    {
        foreach (Transport objTran, ratpGlobal.transportList) {
            if (objTran.transportMode != Transport::Modes::bus && objTran.transportMode != Transport::Modes::metro)
            {
                ratpGlobal.railList << objTran;
            }
        }

        std::sort(ratpGlobal.railList.begin(), ratpGlobal.railList.end(), Transport::compareTransports);
    }

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
    disconnect(ui->RequestButton, SIGNAL(clicked()), this, SLOT(PrepareUniRequest()));

    ui->StationCombo->clear();
    _code -= 1;

    if (ui->BusRadio->isChecked())
    {
        foreach (StopPoint sp, ratpGlobal.stopPointList)
        {
            if (sp.externalcodeLine == ratpGlobal.busList[_code].codeLine)
            {
                ratpGlobal.busList[_code].mySPList << sp;
                ui->StationCombo->addItem(sp.nomZDE);
            }
        }
    }

    if (ui->MetroRadio->isChecked())
    {
        foreach (StopPoint sp, ratpGlobal.stopPointList)
        {
            if (sp.externalcodeLine == ratpGlobal.metroList[_code].codeLine)
            {
                ratpGlobal.metroList[_code].mySPList << sp;
                ui->StationCombo->addItem(sp.nomZDE);
            }
        }
    }

    if (ui->RailRadio->isChecked())
    {
        foreach (StopPoint sp, ratpGlobal.stopPointList)
        {
            if (sp.externalcodeLine == ratpGlobal.railList[_code].codeLine)
            {
                ratpGlobal.railList[_code].mySPList << sp;
                ui->StationCombo->addItem(sp.nomZDE);
            }
        }
    }

    ui->RequestButton->setEnabled(true);
    connect(ui->StationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SetUniStationIndex(int)));
    connect(ui->RequestButton, SIGNAL(clicked()), this, SLOT(PrepareUniRequest()));
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

void Uiratp::PrepareUniRequest()
{
    QString transport;
    QString station;

    if (ui->BusRadio->isChecked())
    {
        transport = ratpGlobal.busList[ratpGlobal.indexTranspForUniReq].codeLine;
        station = ratpGlobal.busList[ratpGlobal.indexTranspForUniReq].mySPList[ratpGlobal.indexStationForUniReq].idZDE;
    }

    if (ui->MetroRadio->isChecked())
    {
        transport = ratpGlobal.metroList[ratpGlobal.indexTranspForUniReq].codeLine;
        station = ratpGlobal.metroList[ratpGlobal.indexTranspForUniReq].mySPList[ratpGlobal.indexStationForUniReq].idZDE;
    }

    if (ui->RailRadio->isChecked())
    {
        transport = ratpGlobal.railList[ratpGlobal.indexTranspForUniReq].codeLine;
        station = ratpGlobal.railList[ratpGlobal.indexTranspForUniReq].mySPList[ratpGlobal.indexStationForUniReq].idZDE;
    }

    ratpSearch.DoUniRequest(transport, station);
}

void Uiratp::ShowErrorUni(QString error)
{

    ui->ScrollAreaContents->hide();
    CleanView();

        // Create Text Slot
        QLabel *labelDest = new QLabel(ui->ScrollAreaContents);
        labelDest->move(ui->ScrollAreaContents->geometry().left(), ui->ScrollAreaContents->geometry().center().y());

        labelDest->setText(error);

    ui->ScrollAreaContents->show();
}

void Uiratp::ShowFinishedUni(QJsonArray resultArray)
{

    ui->ScrollAreaContents->hide();
    CleanView();

    int span = 40;

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
            labelTime->setText(resultArray[i].toObject().value("schedule").toString());
        }
        else
        {
            labelTime->setText(resultArray[i].toObject().value("time").toString());
        }

    }
    ui->ScrollAreaContents->show();
}


void Uiratp::CleanView()
{
    if (ui->ScrollAreaContents->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly).count() > 0)
    {
        qDeleteAll(ui->ScrollAreaContents->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));
    }
}

