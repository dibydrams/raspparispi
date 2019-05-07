#ifndef APIVIGICRUES_H
#define APIVIGICRUES_H

#include "Abstract_API.h"
#include "vigicrueshauteur.h"
#include "vigicruesdebit.h"


class apiVigiCrues : public Abstract_API
{

    Q_OBJECT

public:
    apiVigiCrues();
    API_index getId() override;
    QPixmap getPixmap() override;

private slots:
    void API_Call();
    void API_Results(QNetworkReply *reply);

private:
    QNetworkAccessManager *API_AccessVigi;
    QNetworkReply *currentReply;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QList<GeoObj> m_list;
    double longitude;
    double latitude;
    VigiCruesHauteur *h_hauteur;
    VigiCruesDebit *d_debit;

public slots:
    void getInfo() override;

signals:
  void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APIVIGICRUES_H
