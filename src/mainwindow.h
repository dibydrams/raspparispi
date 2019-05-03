#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "custombutton.h"
#include "apievenementsmv.h"
#include "pharmapi.h"
#include "apibornes_elec.h"
#include "apiquefaire.h"
#include "apikiosques.h"
#include "sanisette.h"
#include "apiratp_station.h"
#include "apiratp_global.h"
#include "uiratp.h"
#include "apiborneswifi.h"
#include "theatre.h"
#include "apifontaines.h"
#include "apiparkingpublic.h"
#include "apiparkingprive.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initButtons();
    QList <CustomButton *> ButtonList;
    void resizeEvent(QResizeEvent *event);

private slots:
    void dataReceived(QList<Abstract_API::GeoObj> list, Abstract_API::API_index apiIndex);
    void dialog();
    void GetInfo(Abstract_API *ptr);
    void enableButtons();
    void RazSlot(Abstract_API::API_index);
//  void ratpDialog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
