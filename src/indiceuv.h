#ifndef INDICEUV_H
#define INDICEUV_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


class IndiceUV:public QObject
{
    Q_OBJECT
public:
    IndiceUV();
    void setRequest();
    QHash <QString, QVariant> readJson();
    QHash <QString, QVariant> getHash() {return i_hash;}

private:
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QByteArray req;
    QHash <QString, QVariant> i_hash;


public slots:
   void replyFinished();

signals:
   void received();
};

#endif // INDICEUV_H
