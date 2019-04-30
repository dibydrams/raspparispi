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
<<<<<<< HEAD
#include "apiborneswifi.h"


=======
#include "theatre.h"
>>>>>>> 4b73b71ce409c496e20896f6043de95349b7ed7a

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

private slots:
    void dataReceived(QList<Abstract_API::GeoObj> list);
    void dialog();
//    void ratpDialog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
