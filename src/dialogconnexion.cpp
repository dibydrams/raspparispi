#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"
#include <QDebug>

DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);

}

DialogConnexion::~DialogConnexion()
{
    delete ui;

}

void DialogConnexion::afficherConnexion()
{

DialogConnexion *fenetr = new DialogConnexion;
fenetr->ui->label->setText("Problème de connexion !!");
fenetr->show();

}
