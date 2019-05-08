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
#include "apiratp_global.h"
#include "uiratp.h"
#include "apiborneswifi.h"
#include "theatre.h"
#include "apifontaines.h"
#include "apiparkingpublic.h"
#include "apiparkingprive.h"
#include "resetbuttons.h"
#include "apivigicrues.h"
#include "dialogvigicrues.h"
#include "dialogtraduction.h"
#include "dialogmeteo.h"

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
    QList<Abstract_API::GeoObj> emptyList;
    void resizeEvent(QResizeEvent *event);


private slots:
    void dataReceived(QList<Abstract_API::GeoObj> list, Abstract_API::API_index apiIndex);
    void dialog();
    void dialogInfo();
    void dialogtraduction();
    void dialogvigicrues();
    void GetInfo(Abstract_API *ptr);
    void enableButtons();
    void RazSlot(Abstract_API::API_index);
    void resetAllButtons();
//  void ratpDialog();


public slots:
    void loadlanguage(QString lang);

private:
    Ui::MainWindow *ui;
    Dialogtraduction *l_lang;
    //Dialog *meteo;

signals:
    void open();

};

#endif // MAINWINDOW_H
