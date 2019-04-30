#ifndef UIRATP_H
#define UIRATP_H

#include "apiratp_global.h"

#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class Uiratp;
}

class Uiratp : public QDialog
{
    Q_OBJECT

public:
    explicit Uiratp(QWidget *parent = nullptr);
    ~Uiratp();

    ApiRatp_Global ratpGlobal;
    class ApiRatp_Search;

    void showFinishedStation(QJsonArray);
    void showFinishedUni(QJsonArray);

private slots:
    void SetUniTransportIndex(int _codeT);
    void SetUniStationIndex(int _codeS);
    void ShowTransports();
    void ShowTransportStopPoints(int _code);

private:
    Ui::Uiratp *ui;

};

#endif // UIRATP_H
