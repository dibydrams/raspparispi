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

    flag();

}

Dialogtraduction::~Dialogtraduction()
{
    delete ui;
}

void Dialogtraduction::flag()
{

    QIcon flagic1, flagic2, flagic3;
    QPixmap flag1, flag2, flag3;

    flag1.load(":/Traduction/egypt.png");
    flagic1.addPixmap(flag1);
    ui->pushButton_AR->setIcon(flagic1);

    flag2.load(":/Traduction/usa.png");
    flagic2.addPixmap(flag2);
    ui->pushButton_EN->setIcon(flagic2);

    flag3.load(":/Traduction/france.png");
    flagic3.addPixmap(flag3);
    ui->pushButton_FR->setIcon(flagic3);


}



void Dialogtraduction::loadfr()
{

    QString lang;
    lang = "fr";
    //qDebug() << "fr";
    emit received(lang);

}

void Dialogtraduction::loadar()
{
    QString lang;
    lang = "ar";
    //qDebug() << "ar";
    emit received(lang);

}

void Dialogtraduction::loaden()
{
    QString lang;
    lang = "en";
    //qDebug() << "en";
    emit received(lang);

}




