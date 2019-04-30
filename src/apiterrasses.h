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

class ApiTerrasses :public Abstract_API
{
    Q_OBJECT
public:
    ApiTerrasses();
    int getId() override;
    QPixmap getPixmap() override;
private slots:
    void API_Call();
    void API_Results(QNetworkReply *reply);

public slots:
    void getInfo() override;

private:

    QNetworkAccessManager *API_Access;
    QNetworkReply *currentReply;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QList<GeoObj> m_list;

    double longitude;
    double latitude;
signals:
  void callFinished(QList<Abstract_API::GeoObj>, API_index);
};

#endif // APITERRASSES_H
