#include "dialogtraduction.h"
#include "ui_dialogtraduction.h"
#include "QDebug"
#include "QComboBox"
#include "QApplication"
#include "QTranslator"
#include "dialogmeteo.h"


Dialogtraduction::Dialogtraduction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogtraduction)
{
    ui->setupUi(this);


    connect(ui->pushButton_FR,SIGNAL(clicked()),this,SLOT(loadfr()));
    connect(ui->pushButton_AR,SIGNAL(clicked()),this,SLOT(loadar()));
    connect(ui->pushButton_EN,SIGNAL(clicked()),this,SLOT(loaden()));


}

Dialogtraduction::~Dialogtraduction()
{
    delete ui;
}


void Dialogtraduction::loadfr()
{

    QString lang;
    lang = "fr";
    qDebug() << "fr";
    emit received(lang);

}

void Dialogtraduction::loadar()
{
    QString lang;
    lang = "ar";
    qDebug() << "ar";
    emit received(lang);

}

void Dialogtraduction::loaden()
{
    QString lang;
    lang = "en";
    qDebug() << "en";
    emit received(lang);

}




