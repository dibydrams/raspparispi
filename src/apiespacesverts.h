#ifndef APIESPACESVERTS_H
#define APIESPACESVERTS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QList>
#include "icon.h"
#include <QEventLoop>
#include "widgetmap.h"
#include "Abstract_API.h"

/*Api traité par Thomas LY*/

typedef struct {
    double longitude;
    double latitude;
    QString typeVoie;
    QString nomVoie;
    QString nomEV;
    QString codePostal;
    QString categorie;
    QString presCloture;
    QString ouvertFerme;
}espacesverts;

class ApiEspacesVerts : public Abstract_API
{
    Q_OBJECT

public:
    ApiEspacesVerts();
    API_index getId() override;
    QPixmap getPixmap() override;

private slots:
    //void API_Call();
    void API_Results(QNetworkReply *reply);
    void copieGeoObj();
//    void slotErrorConnexion(QNetworkReply::NetworkError);

public slots:
    void getInfo() override;

private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *currentReply;
    QJsonDocument document;
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    QJsonValue val;
    QJsonObject jsObj;
    QJsonArray geoloc;
    QList<GeoObj> m_list;
    QList<espacesverts> *espverts = new QList<espacesverts>;
    QEventLoop loop;
    QString rayon = "1000";

    QString latCentre;
    QString lonCentre;

    void firstCall();
    double longit;
    double lat;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APIESPACESVERTS_H
