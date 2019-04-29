#ifndef METEO_H
#define METEO_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


class meteo:public QObject
{
     Q_OBJECT

public:
    meteo();
    QVariantHash readJson();
    void setRequest();
    QHash <QString, QVariant> getHash() { return m_hash;}

private:
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QByteArray req;
    QVariantHash tableau;
    QHash <QString, QVariant> m_hash;


public slots:
   void replyFinished();

signals:
   void received();

};



#endif // METEO_H
