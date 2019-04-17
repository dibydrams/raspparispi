#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(onAuthenticationRequestSlot(QNetworkReply*,QAuthenticator*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    request = new QNetworkRequest () ;
    request->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request->setUrl(QUrl("https://api-lab-trall-stif.opendata.stif.info/service/tr-globale-stif/estimated-timetable"));
    userdata = new QByteArray ("40cd855f9c40cffde532f9409f94b9f3e36648cf6bec24d347e963d5");

    manager->post(*request,*userdata);
    manager->get(*request);
}

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

void MainWindow::onAuthenticationRequestSlot(QNetworkReply *_rep, QAuthenticator *authenticator)
{
    qDebug() << "auth" << _rep->error();
    authenticator->setUser(username);
    authenticator->setPassword(password);
}

void MainWindow::replyFinished(QNetworkReply* data)
{
    qDebug() << "hello" << data->error();
    qDebug() << "hello" << data->readAll();

}
