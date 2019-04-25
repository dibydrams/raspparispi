#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "custombutton.h"
#include "apievenementsmv.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMap();
    void initButtons();

private slots:
    void dataReceived(QList<Abstract_API::GeoObj> list);

private:
    Ui::MainWindow *ui;
    QList <CustomButton *> ButtonList;
};

#endif // MAINWINDOW_H
