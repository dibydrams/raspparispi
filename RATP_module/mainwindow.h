#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QAuthenticator>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString keyapi = "Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz";
    QNetworkAccessManager *manager;
    QNetworkRequest *requestGlobal;
    QNetworkRequest *requestUni;
    QNetworkReply *replyGlobal;
    QNetworkReply *replyUni;
    QByteArray *replydata;
    QJsonArray resultArray;
    QJsonObject rootObject;
    QList<QPointF> pointList;

    void ReadLocalJson();
    QJsonDocument LoadJson(QString fileName);
    //    void NetworkCleanup();
public slots:
    void replyFinishedGlobal();
    void replyFinishedUni();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
