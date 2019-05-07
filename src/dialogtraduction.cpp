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

    ui->comboBox->insertItem(0,"Français");
    ui->comboBox->insertItem(1,"English");
    ui->comboBox->insertItem(2,"Arabe");



}

void Dialogtraduction::loadlang()
{


    QTranslator translator;

    if(ui->comboBox->currentText() == "Français")
    {

        qDebug() << "Français";
        qDebug()<< translator.load(":/Traduction/src_fr.qm") ;
        qApp->installTranslator(&translator);                               //qApp est un pointeur sur la classe QApplication
        ui->retranslateUi(this);

    }

    else if(ui->comboBox->currentText() == "English")

    {

        qDebug() << "English";
        qDebug()<< translator.load(":/Traduction/src_en.qm") ;
        qApp->installTranslator(&translator);                               //qApp est un pointeur sur la classe QApplication
        ui->retranslateUi(this);


    }

    else if (ui->comboBox->currentText() == "Arabe")

    {


        qDebug() << "Arabe";
        qDebug()<< translator.load(":/Traduction/src_ar.qm") ;
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);

    }



}
