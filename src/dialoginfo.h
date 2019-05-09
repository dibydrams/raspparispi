#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <Abstract_API.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QScrollArea>
#include <QList>
#include "distance.h"

namespace Ui {
class dialoginfo;
}
/**
* \author   Jean-Sébastien , Tony
* \date     6 mai 2019
* \version  1.0
 * @brief The dialoginfo class
 * @details Class qui va permettre d'afficher des informations relatives aux point d'intérêt
 *          au clic sur les puces.
 */
class dialoginfo : public QDialog
{
    Q_OBJECT

public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableInfo;
    QString longitude;
    QString latitude;
    distance* dist;

    //    QTableWidget QList<QTableWidget>;
    void setData(const double cliclong, const double cliclat, QList<Abstract_API::GeoObj> list);

    explicit dialoginfo(QWidget *parent = nullptr);
    ~dialoginfo();

private:
    Ui::dialoginfo *ui;
};

#endif // DIALOGINFO_H
