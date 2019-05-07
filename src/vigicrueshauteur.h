#ifndef VIGICRUESHAUTEUR_H
#define VIGICRUESHAUTEUR_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantHash>
#include <QJsonObject>


class VigiCruesHauteur : public QObject
{

    Q_OBJECT

public:
    VigiCruesHauteur();
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

#endif // VIGICRUESHAUTEUR_H
