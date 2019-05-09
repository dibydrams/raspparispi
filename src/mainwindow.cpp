#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Abstract_API.h"
#include "dialogmeteo.h"
#include "dialoginfo.h"
#include "ui_dialogmeteo.h"
#include "apimeteo.h"
#include "apiterrasses.h"
#include "apiespacesverts.h"
#include "apiratp_search.h"
#include "apivelib.h"
#include "traduction.h"
#include "dialogtraduction.h"
#include "resetbuttons.h"
#include "QString"

#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    initButtons();

    l_lang = new Dialogtraduction(this);
    connect(l_lang,SIGNAL(received(QString)),this,SLOT(loadlanguage(QString)));

}
MainWindow::~MainWindow()
{
    delete ui;
}


/* ##   FONCTION COMMUNE : initButtons()  ##
 *
 * Fonction permettant d'initier les boutons sur l'interface.
 * Etapes précises à suivre pour la création de chacun des boutons.
 *
 *
 * -------------------- ETAPES A SUIVRE --------------------
 * ---- 1. Initiation du pointeur sur votre classe gérant vos datas
 * ---- 2. Création du bouton. Choisir un nom en rapport avec vos datas (ex: buttonMetro, buttonVelib)
 * ---- 3. Ajout du bouton au sein de l'interface principale
 * ---- 4. Connection du clic avec la fonction permettant de lancer la récupération des datas
 * ---- 5. Ajout du bouton à la liste des boutons (cela permet de les gérer tous en même temps par la suite)
 * ---- 6. Une fois le signal de traitement des data récupéré, redirection vers la méthode contenant les datas prêtes à être affichées
 *
 * FORMAT : Les boutons auront tous le même format standardisé. Il n'est donc pas nécessaire que vous appliquiez votre propre design à ceux-ci, il sera global.
 * BONUS : Si vous n'avez pas de localisations à afficher (lat/long) sur la map, vous pouvez connecter votre bouton directement à votre QDialog ici (ex: Météo) */

void MainWindow::initButtons()
{
    Abstract_API *ptr ; // Pointeur sur classe mère, ne pas changer.

    // ##   INITIATION DE CHAQUE BOUTON CI-DESSOUS  ##
    /* Chaque type de data doit initier son bouton sur l'interface en se basant sur du bouton principal : ButtonEv (le premier de la liste)
     *  Ne pas changer le code du premier bouton */

    ptr = new traduction;
    CustomButton *buttonTraduction = new CustomButton(ptr,this);
    ButtonList << buttonTraduction;
    ui->horizontalLayout->addWidget(buttonTraduction);
    buttonTraduction->setCheckable(false);
    buttonTraduction->setToolTip(tr("Traduction"));
    connect(buttonTraduction,SIGNAL(clicked()),this,SLOT(dialogtraduction()));


    ptr = new ApiMeteo;
    CustomButton *buttonMeteo = new CustomButton(ptr, this);
    ButtonList << buttonMeteo;
    ui->horizontalLayout->addWidget(buttonMeteo);
    buttonMeteo->setToolTip(tr("Météo"));
    buttonMeteo->setCheckable(false);
    connect(buttonMeteo, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(buttonMeteo, SIGNAL(clicked()), this, SLOT(dialog()));
    //connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new ApiEvenementsMV;
    CustomButton *buttonEv = new CustomButton(ptr, this);
    ButtonList << buttonEv;
    ui->horizontalLayout->addWidget(buttonEv);
    buttonEv->setToolTip(tr("Evénements"));
    connect(buttonEv, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonEv, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new pharmapi;
    CustomButton *pharmButton = new CustomButton(ptr, this);
    ButtonList << pharmButton;
    ui->horizontalLayout->addWidget(pharmButton);
    pharmButton->setToolTip(tr("Pharmacies"));
    connect(pharmButton, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(pharmButton, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new ApiBornes_Elec;
    CustomButton *bornesElecBtn = new CustomButton(ptr, this);
    ButtonList << bornesElecBtn;
    bornesElecBtn->setToolTip(tr("Bornes Electriques"));
    ui->horizontalLayout->addWidget(bornesElecBtn);
    connect(bornesElecBtn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(bornesElecBtn, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new ApiQueFaire;
    CustomButton *QueFaire_btn = new CustomButton(ptr, this);
    ButtonList << QueFaire_btn;
    ui->horizontalLayout->addWidget(QueFaire_btn);
    QueFaire_btn->setToolTip(tr("Animations"));
    connect(QueFaire_btn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(QueFaire_btn, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new apikiosques; //bouton Kiosques
    CustomButton *Kiosques_btn=new CustomButton(ptr, this);
    ButtonList << Kiosques_btn;
    ui->horizontalLayout->addWidget(Kiosques_btn);
    Kiosques_btn->setToolTip(tr("Kiosques"));
    connect(Kiosques_btn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(Kiosques_btn, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new apifontaines;
    CustomButton *fontaines_btn=new CustomButton(ptr, this);
    ButtonList << fontaines_btn;
    ui->horizontalLayout->addWidget(fontaines_btn);
    fontaines_btn->setToolTip(tr("Fontaines"));
    connect(fontaines_btn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(fontaines_btn, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new ApiTerrasses;
    CustomButton *terrassesBtn = new CustomButton(ptr, this);
    ButtonList << terrassesBtn;
    ui->horizontalLayout->addWidget(terrassesBtn);
    terrassesBtn->setToolTip(tr("Terrasses"));
    connect(terrassesBtn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(terrassesBtn, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new sanisette;
    CustomButton *buttonToilette = new CustomButton(ptr, this);
    ButtonList << buttonToilette;
    ui->horizontalLayout->addWidget(buttonToilette);
    buttonToilette->setToolTip(tr("Toilettes"));
    connect(buttonToilette, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index))); // 6
    connect(buttonToilette, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new ApiRatp_Global;
    CustomButton *buttonRatpGlobal = new CustomButton (ptr, this);
    ButtonList << buttonRatpGlobal;
    ui->horizontalLayout->addWidget(buttonRatpGlobal);
    buttonRatpGlobal->setToolTip(tr("Transports"));
    connect(buttonRatpGlobal, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonRatpGlobal, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    //    ptr = new ApiRatp_Search;
    //    CustomButton *buttonRatpSearch = new CustomButton(ptr, this);
    //    ui->horizontalLayout->addWidget(buttonRatpSearch);
    //    buttonRatpSearch->setCheckable(false);
    //    connect(buttonRatpSearch, SIGNAL(clicked()), this, SLOT(ratpDialog()));

    ptr = new ApiEspacesVerts;
    CustomButton *buttonEspacesVerts = new CustomButton (ptr, this);
    ButtonList << buttonEspacesVerts;
    ui->horizontalLayout->addWidget(buttonEspacesVerts);
    buttonEspacesVerts->setToolTip(tr("Parcs & Espaces Verts"));
    connect(buttonEspacesVerts, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonEspacesVerts, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new ApiBornesWifi;
    CustomButton *buttonWiFi = new CustomButton(ptr, this);
    ButtonList << buttonWiFi;
    ui->horizontalLayout->addWidget(buttonWiFi);
    buttonWiFi->setToolTip(tr("Bornes WiFi"));
    connect(buttonWiFi, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonWiFi, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new theatre;
    CustomButton *buttonTheatre = new CustomButton (ptr, this);
    ButtonList << buttonTheatre;
    ui->horizontalLayout->addWidget(buttonTheatre);
    buttonTheatre->setToolTip(tr("Théâtres"));
    connect(buttonTheatre, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonTheatre, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new apiVelib;
    CustomButton *buttonVelib = new CustomButton(ptr, this);
    ButtonList << buttonVelib;
    ui->horizontalLayout->addWidget(buttonVelib);
    buttonVelib->setToolTip(tr("Bornes Vélib'"));
    connect(buttonVelib, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonVelib, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new apiParkingPublic;
    CustomButton *buttonParkingPublic = new CustomButton(ptr, this);
    ButtonList << buttonParkingPublic;
    ui->horizontalLayout->addWidget(buttonParkingPublic);
    buttonParkingPublic->setToolTip(tr("Parkings Publics"));
    connect(buttonParkingPublic, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonParkingPublic, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new apiParkingPrive;
    CustomButton *buttonParkingPrive = new CustomButton(ptr, this);
    ButtonList << buttonParkingPrive;
    ui->horizontalLayout->addWidget(buttonParkingPrive);
    buttonParkingPrive->setToolTip(tr("Parkings Privés"));
    connect(buttonParkingPrive, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
    connect(buttonParkingPrive, SIGNAL(RazSig(Abstract_API::API_index)), this, SLOT(RazSlot(Abstract_API::API_index)));

    ptr = new apiVigiCrues;
    CustomButton *buttonVigiCrues = new CustomButton(ptr, this);
    ButtonList << buttonVigiCrues;
    ui->horizontalLayout->addWidget(buttonVigiCrues);
    buttonVigiCrues->setToolTip(tr("VigiCrues"));
    buttonVigiCrues->setCheckable(false);
    connect(buttonVigiCrues, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(buttonVigiCrues, SIGNAL(clicked()), this, SLOT(dialogvigicrues()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));


    // Bouton servant à réinitialiser la map et les boutons
    ptr = new resetButtons;
    CustomButton *resetButtons = new CustomButton(ptr, this);
    ButtonList << resetButtons;
    ui->horizontalLayout->addWidget(resetButtons);
    resetButtons->setCheckable(false);
    resetButtons->setToolTip(tr("Réinitialiser les Filtres"));
    connect(resetButtons, SIGNAL(clicked()), this, SLOT(resetAllButtons()));

    ui->widget->setIconCount(ButtonList.count());



}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    int btnNb = ButtonList.count();
    int sizebtn = this->width() / btnNb - 10;

    for ( auto val : ButtonList ) {
        val->setIconSize(QSize(sizebtn,sizebtn));
        val->setFixedSize(sizebtn,sizebtn);
    }
}

/* ##   FONCTION D'APPEL DE LA MAP : dataReceived(QList)  ##
 *
 * Explications : Cette fonction renvoie la liste complète de GeoObj afin de les afficher sur la map.
 * Il ne devrait pas être nécessaire de modifier cette fonction. Elle sera utilisée pour positionner les points d'intérêts sur la map. */

void MainWindow::dataReceived(QList<Abstract_API::GeoObj> list, Abstract_API::API_index apiIndex)
{
    ui->widget->m_listePI_API.removeAt(apiIndex);
    ui->widget->m_listePI_API.insert(apiIndex,list);
    this->update();
    QApplication::restoreOverrideCursor();
}

void MainWindow::dialog()
{
    Dialog fenetre(this);
    //fenetre.loadlanguage("en");
    fenetre.exec();


}

void MainWindow::dialogtraduction()
{
    l_lang->show();
}

void MainWindow::dialogInfo()
{
    dialoginfo fenetre;
    fenetre.exec();
}

void MainWindow::dialogvigicrues()
{
    DialogVigicrues fenetre;
    fenetre.exec();
}

void MainWindow::GetInfo(Abstract_API *ptr)
{
    for (auto button : ButtonList) {
        button->setEnabled(false); }

    ptr->getInfo();
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(enableButtons()));
}

void MainWindow::enableButtons()
{
    for (auto button : ButtonList) {
        button->setEnabled(true);
    }
}

void MainWindow::RazSlot(Abstract_API::API_index button_ID)
{
    dataReceived(emptyList, button_ID);
}

void MainWindow::resetAllButtons()
{
    for (auto button : ButtonList) {
        button->setChecked(false);
        dataReceived(emptyList, button->buttonID);
    }
}

void MainWindow::loadlanguage(QString lang)
{

    qDebug() << "MainWindow";
    qDebug() << lang;
    QTranslator translator;

    translator.load((QString(":/Traduction/src_%1.qm").arg(lang)));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);

    l_lang->hide();

}

//void MainWindow::ratpDialog()
//{
//    Uiratp window;
//    window.exec();
//}
