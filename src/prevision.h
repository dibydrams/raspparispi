#ifndef PREVISION_H
#define PREVISION_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class Prevision:public QObject
{

    Q_OBJECT

public:
    Prevision();

    void setRequest();
    QHash <QString, QVariant> readJson();
    QHash <QString, QVariant> getHash() { return pm_hash;}


private:
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QByteArray req;
    QHash <QString, QVariant> pm_hash;


public slots:
   void replyFinished();

signals:
   void received();
};

#endif // PREVISION_H
