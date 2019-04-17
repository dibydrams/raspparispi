#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QAuthenticator>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString username = "francoisflorian4@gmail.com";
    QString password = "floflo123";
    QString keyapi = "40cd855f9c40cffde532f9409f94b9f3e36648cf6bec24d347e963d5";
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QByteArray *userdata;

public slots:
    void replyFinished(QNetworkReply *_rep);
    void onAuthenticationRequestSlot(QNetworkReply *reply, QAuthenticator *authenticator);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
