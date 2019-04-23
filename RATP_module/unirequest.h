#ifndef UNIREQUEST_H
#define UNIREQUEST_H

#include "stoppoint.h"

#include <QDialog>
#include <QDebug>

namespace Ui {
class UniRequest;
}

class UniRequest : public QDialog
{
    Q_OBJECT

public:
    explicit UniRequest(QWidget *parent = nullptr);
    ~UniRequest();

    QList<StopPoint> UniStopPointList;
    int SavedIndex;
    QList<int> IndexTab;
public slots:
    void InitStopPointList();
    void SendRequest();
    void InitLastList(int);
private:
    Ui::UniRequest *ui;
};

#endif // UNIREQUEST_H
