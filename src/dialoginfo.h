#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QScrollArea>
#include <QList>
#include "distance.h"

namespace Ui {
class dialoginfo;
}

class dialoginfo : public QDialog
{
    Q_OBJECT

public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetDistance;
    QString longitude;
    QString latitude;
    distance* dist;
//    QTableWidget QList<QTableWidget>;
    void setData(const QString cliclong, const QString cliclat);
    explicit dialoginfo(QWidget *parent = nullptr);
    ~dialoginfo();

private:
    Ui::dialoginfo *ui;
};

#endif // DIALOGINFO_H
