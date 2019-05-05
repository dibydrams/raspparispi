#include "dialogtraduction.h"
#include "ui_dialogtraduction.h"
#include "QDebug"
#include "QComboBox"
#include "QApplication"
#include "QTranslator"


Dialogtraduction::Dialogtraduction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogtraduction)
{
    ui->setupUi(this);
    language();
    connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(loadlang()));


}

Dialogtraduction::~Dialogtraduction()
{
    delete ui;
}

void Dialogtraduction::language()
{


    ui->comboBox->insertItem(0,"Anglais");
    ui->comboBox->insertItem(1,"Arabe");
    ui->comboBox->insertItem(2,"Espagnole");


}

void Dialogtraduction::loadlang()
{

    QApplication *a;
    Dialogtraduction d;
    QTranslator translator;

    if(ui->comboBox->currentText() == "Anglais")

    {

        qDebug()<< translator.load("src_en.qm") ;
        a->installTranslator(&translator);

    }

    else if (ui->comboBox->currentText() == "Arabe")

    {

        qDebug()<< translator.load("src_ar.qm") ;
        a->installTranslator(&translator);

    }

    else

    {

        qDebug()<< translator.load("src_es.qm") ;
        a->installTranslator(&translator);

    }




}
