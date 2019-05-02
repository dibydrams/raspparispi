#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Abstract_API.h"
#include "dialogmeteo.h"
#include "ui_dialogmeteo.h"
#include "apimeteo.h"
#include "apiterrasses.h"
#include "apiratp_station.h"
#include "apiespacesverts.h"
#include "apiratp_search.h"
#include "apivelib.h"

#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
    initButtons();
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

    ptr = new ApiMeteo;
    CustomButton *buttonMeteo = new CustomButton(ptr, this);
    ButtonList << buttonMeteo;
    ui->horizontalLayout->addWidget(buttonMeteo);
    buttonMeteo->setCheckable(false);
    connect(buttonMeteo, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(buttonMeteo, SIGNAL(clicked()), this, SLOT(dialog()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new ApiEvenementsMV;
    CustomButton *buttonEv = new CustomButton(ptr, this);
    ButtonList << buttonEv;
    ui->horizontalLayout->addWidget(buttonEv);
    connect(buttonEv, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new pharmapi;
    CustomButton *pharmButton = new CustomButton(ptr, this);
    ButtonList << pharmButton;
    ui->horizontalLayout->addWidget(pharmButton);
    connect(pharmButton, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new ApiBornes_Elec;
    CustomButton *bornesElecBtn = new CustomButton(ptr, this);
    ButtonList << bornesElecBtn;
    ui->horizontalLayout->addWidget(bornesElecBtn);
    connect(bornesElecBtn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new ApiQueFaire;
    CustomButton *QueFaire_btn = new CustomButton(ptr, this);
    ButtonList << QueFaire_btn;
    ui->horizontalLayout->addWidget(QueFaire_btn);
    connect(QueFaire_btn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new apikiosques; //bouton Kiosques
    CustomButton *Kiosques_btn=new CustomButton(ptr, this);
    ButtonList << Kiosques_btn;
    ui->horizontalLayout->addWidget(Kiosques_btn);
    connect(Kiosques_btn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new apifontaines;
    CustomButton *fontaines_btn=new CustomButton(ptr, this);
    ButtonList << fontaines_btn;
    ui->horizontalLayout->addWidget(fontaines_btn);
    connect(fontaines_btn, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new ApiTerrasses;
    CustomButton *terrassesBtn = new CustomButton(ptr, this);
    ButtonList << terrassesBtn;
    ui->horizontalLayout->addWidget(terrassesBtn);
    connect(terrassesBtn, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new sanisette;
    CustomButton *buttonToilette = new CustomButton(ptr, this);
    ButtonList << buttonToilette;
    ui->horizontalLayout->addWidget(buttonToilette);
    connect(buttonToilette, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index))); // 6

    ptr = new ApiRatp_Global;
    CustomButton *buttonRatpGlobal = new CustomButton (ptr, this);
    ButtonList << buttonRatpGlobal;
    ui->horizontalLayout->addWidget(buttonRatpGlobal);
    connect(buttonRatpGlobal, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

//    ptr = new ApiRatp_Search;
//    CustomButton *buttonRatpSearch = new CustomButton(ptr, this);
//    ui->horizontalLayout->addWidget(buttonRatpSearch);
//    buttonRatpSearch->setCheckable(false);
//    connect(buttonRatpSearch, SIGNAL(clicked()), this, SLOT(ratpDialog()));

    ptr = new ApiEspacesVerts;
    CustomButton *buttonEspacesVerts = new CustomButton (ptr, this);
    ButtonList << buttonEspacesVerts;
    ui->horizontalLayout->addWidget(buttonEspacesVerts);
    connect(buttonEspacesVerts, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new ApiBornesWifi;
    CustomButton *buttonWiFi = new CustomButton(ptr, this);
    ButtonList << buttonWiFi;
    ui->horizontalLayout->addWidget(buttonWiFi);
    connect(buttonWiFi, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new theatre;
    CustomButton *buttonTheatre = new CustomButton (ptr, this);
    ButtonList << buttonTheatre;
    ui->horizontalLayout->addWidget(buttonTheatre);
    connect(buttonTheatre, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

	ptr = new apiVelib;
    CustomButton *buttonVelib = new CustomButton(ptr, this);
    ButtonList << buttonVelib;
    ui->horizontalLayout->addWidget(buttonVelib);
    connect(buttonVelib, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new apiParkingPublic;
    CustomButton *buttonParkingPublic = new CustomButton(ptr, this);
    ButtonList << buttonParkingPublic;
    ui->horizontalLayout->addWidget(buttonParkingPublic);
    connect(buttonParkingPublic, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));

    ptr = new apiParkingPrive;
    CustomButton *buttonParkingPrive = new CustomButton(ptr, this);
    ButtonList << buttonParkingPrive;
    ui->horizontalLayout->addWidget(buttonParkingPrive);
    connect(buttonParkingPrive, SIGNAL(Clicked(Abstract_API *)), this, SLOT(GetInfo(Abstract_API *)));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>, Abstract_API::API_index)));
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
//    ui->widget->m_listePI = list;

    ui->widget->m_listePI_API.removeAt(apiIndex);
    ui->widget->m_listePI_API.insert(apiIndex,list);

    //qDebug()<<"ok recu";
    this->update();
}

void MainWindow::dialog()
{
    Dialog fenetre;
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

//void MainWindow::ratpDialog()
//{
//    Uiratp window;
//    window.exec();
//}
