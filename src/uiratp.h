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

    void showFinishedStation(QJsonArray);
    void showFinishedUni(QJsonArray);

private slots:
    void SetUniStationIndex(int _codeS);
    void SetUniTransportIndex(int _codeT);
private:
    Ui::Uiratp *ui;

    void ShowTransports();
    void ShowTransportStopPoints(int _code);
};

#endif // UIRATP_H
