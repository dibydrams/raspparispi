#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meteo.h"
#include "prevision.h"
#include "pollution.h"
#include "dialog.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonMeteo,SIGNAL(clicked()),this,SLOT(dialog()));

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::dialog()
{

    Dialog fenetre;
    fenetre.exec();

}

