#ifndef POLLUTION_H
#define POLLUTION_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class Pollution:public QObject
{

    Q_OBJECT

public:   
    Pollution();
    void setRequest();
    QHash <QString, QVariant> getHash() { return p_hash;}
    QVariantHash readJson();

private:
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QByteArray req;
    QHash <QString, QVariant> p_hash;

public slots:
    void replyFinished();

signals:
    void received();


};

#endif // POLLUTION_H
