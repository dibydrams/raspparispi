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
    lang = "Français";
    qDebug() << "Français";
    emit received(lang);

}

void Dialogtraduction::loadar()
{
    QString lang;
    lang = "Arabe";
    qDebug() << "Arabe";
    emit received(lang);

}

void Dialogtraduction::loaden()
{
    QString lang;
    lang = "Anglais";
    qDebug() << "Anglais";
    emit received(lang);

}




