#ifndef UIRATP_H
#define UIRATP_H

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

    void showFinishedStation(QJsonArray);

private:
    Ui::Uiratp *ui;

};

#endif // UIRATP_H
