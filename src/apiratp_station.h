#ifndef APIRATP_STATION_H
#define APIRATP_STATION_H

#include "Abstract_API.h"
#include "apiratp_global.h"
#include "stoppoint.h"
#include "transport.h"
#include "uiratp.h"

#include <QDialog>
#include <QDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>


namespace Ui {
class Uiratp;
}

class ApiRatp_Station : public Abstract_API
{
public:
    ApiRatp_Station();
    int getId() override;
    QPixmap getPixmap() override;

    Uiratp *uiratp;
    ApiRatp_Global *ratpGlobal;

    QNetworkAccessManager *managerStation;
    QNetworkRequest *requestStation;
    QNetworkReply *replyStation;

private:
    void DoStationRequest();
    void PeriStifJson();

private slots:
    void getInfo() override;
    void replyFinishedStation();
    QJsonDocument LoadJson(QString fileName);

};

#endif // APIRATP_STATION_H
