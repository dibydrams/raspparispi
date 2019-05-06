#ifndef APITERRASSES_H
#define APITERRASSES_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "Abstract_API.h"
#include "utilitaire.h"
#include "icon.h"

typedef struct{
    QString profession;
    QString type;
    QString adresse;
    QString typeIndice;
    double largeur;
    double latitude;
    double longitude;
}terrasse;

class ApiTerrasses :public Abstract_API
{
    Q_OBJECT
public:
    ApiTerrasses();
    ~ApiTerrasses() override;
    API_index getId() override;
    QPixmap getPixmap() override;
private slots:
    void API_Call();
    void API_Results(QNetworkReply *reply);
//ajout debut
    void slotError(QNetworkReply::NetworkError);
//ajout fin

public slots:
    void getInfo() override;

private:

    QNetworkAccessManager *API_Access;
    QNetworkReply *currentReply;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QList<GeoObj> m_list;
     QList<terrasse> *listTerrasse = new QList<terrasse>();


signals:
  void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APITERRASSES_H
