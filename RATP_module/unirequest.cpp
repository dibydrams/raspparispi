#include "unirequest.h"
#include "ui_unirequest.h"

UniRequest::UniRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UniRequest)
{
    ui->setupUi(this);

    ui->comboFirstChoice->setInsertPolicy(QComboBox::InsertAlphabetically);

    ui->radioSortStation->setChecked(true);

    connect(ui->pushOK, SIGNAL(clicked()), this, SLOT(SendRequest()));
    connect(ui->pushCancel, SIGNAL(clicked()), this, SLOT(hide()));
    connect(ui->comboFirstChoice, SIGNAL(currentIndexChanged(int)), this, SLOT(InitLastList(int)));
    connect(ui->radioSortStation, SIGNAL(clicked()), this, SLOT(InitStopPointList()));
    connect(ui->radioSortVehicule, SIGNAL(clicked()), this, SLOT(InitStopPointList()));
}

UniRequest::~UniRequest()
{
    delete ui;
}

void UniRequest::InitStopPointList()
{
    if(ui->comboFirstChoice->count() != 0)
    {
        ui->comboFirstChoice->clear();
    }

    for (int i = 0; i < UniStopPointList.count(); ++i) //2.34575 48.8711687
    {
        if (UniStopPointList[i].coordsZDE.rx() > 2.34475 && UniStopPointList[i].coordsZDE.rx() < 2.34675)
        {
            if (ui->radioSortStation->isChecked())
            {
                ui->comboFirstChoice->addItem(UniStopPointList[i].nomZDE);
            }
            else
            {
                ui->comboFirstChoice->addItem(UniStopPointList[i].externalcodeLine.section(":",1,1));
            }
        }
    }
}

void UniRequest::InitLastList(int _index)
{
    if (_index != -1)
    {
        if(ui->comboLastChoice->count() != 0)
        {
            ui->comboLastChoice->clear();
            IndexTab.clear();
        }

        foreach (StopPoint point, UniStopPointList)
        {
            if (ui->radioSortStation->isChecked())
            {
                if (UniStopPointList[_index].nomZDE == point.nomZDE)
                {
                    ui->comboLastChoice->addItem(point.externalcodeLine.section(":",1,1));
                    IndexTab.append(point.myIndex);
                }
            }
            else
            {
                if (UniStopPointList[_index].externalcodeLine == point.externalcodeLine)
                {
                    ui->comboLastChoice->addItem(point.nomZDE);
                    IndexTab.append(point.myIndex);
                }
            }
        }
    }
    else
    {
        return;
    }
}

void UniRequest::SendRequest()
{
    int pre = ui->comboLastChoice->currentIndex();
    SavedIndex = IndexTab[pre];
    qDebug() << "Point index :" << SavedIndex << " & combo index :" << ui->comboLastChoice->currentIndex();
    accept();
}
