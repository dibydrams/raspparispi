#include "unirequest.h"
#include "ui_unirequest.h"
#include "mainwindow.h"

UniRequest::UniRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UniRequest)
{
    ui->setupUi(this);

    QStringList list;
    for (int i = 0; i < UniStopPointList.count(); ++i) {
        ui->comboFirstChoice->addItem(UniStopPointList[i].codeLine);
    }

    connect(ui->pushOK, SIGNAL(clicked()), this, SLOT(SendRequest()));
}

UniRequest::~UniRequest()
{
    delete ui;
}

void UniRequest::SendRequest()
{
    qDebug() << ui->comboFirstChoice->currentText();
//    MainWindow::DoUniRequest();
}
