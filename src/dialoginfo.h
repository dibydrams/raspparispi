#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <Abstract_API.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QScrollArea>
#include <QList>

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

//    QTableWidget QList<QTableWidget>;
    void setData(const double cliclong, const double cliclat, QList<Abstract_API::GeoObj> list);

    explicit dialoginfo(QWidget *parent = nullptr);
    ~dialoginfo();

private:
    Ui::dialoginfo *ui;
};

#endif // DIALOGINFO_H
