#include "dialogmeteo.h"
#include "mainwindow.h"

#include "meteo.h"
#include "prevision.h"
#include "pollution.h"
#include "indiceuv.h"

#include <QDebug>
#include <QTableWidgetItem>
#include <QtCharts/QBarSet>
#include <QHorizontalStackedBarSeries>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QBarSeries>
#include <QList>
#include <QLineSeries>
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QChart>
#include <QBarSet>
#include <QtCharts>
#include <QtCharts/QBarSet>
#include <QStandardItem>
#include <QPixmap>
#include "dialogtraduction.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->labelDate->setText(QTime::currentTime().toString("hh:mm"));
    ui->labelDate->setText(QDate::currentDate().toString());
    ui->labelDate->setText(QDateTime::currentDateTime().toString(tr("ddd d MMMM  hh:mm ")));


    m_meteo = new meteo;
    p_pollution = new Pollution;
    i_indice = new IndiceUV;
    pm_prevision=new Prevision;
    l_lang = new Dialogtraduction(this);


    connect(m_meteo,SIGNAL(received()),this,SLOT(printHashmeteo()));
    connect(p_pollution,SIGNAL(received()),this,SLOT(printHashpollution()));
    connect(i_indice,SIGNAL(received()),this,SLOT(printHashindice()));
    connect(pm_prevision,SIGNAL(received()),this,SLOT(printHashprevision()));
    connect(p_pollution,SIGNAL(received()),this,SLOT(pollutionChart()));
    connect(p_pollution,SIGNAL(received()),this,SLOT(AQI()));
    connect(p_pollution,SIGNAL(received()),this,SLOT(Icon()));
    connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(close()));


    setvignette();

    QPixmap uvprotection;
    uvprotection.load(":/Icons_meteo/protectionUV.png");
    ui->label_UVprotection->setPixmap(uvprotection);


}

Dialog::~Dialog()
{

    delete ui;

}

void Dialog::setvignette()
{

    QString jours = (QDate::currentDate().toString("ddd"));
    QString heures = (QTime::currentTime().toString("hh"));


    QPixmap v1 ,v2,v3,v4,v5,v6;

    v1.load(":/Icons_meteo/vignette1.png");
    v2.load(":/Icons_meteo/vignette2.png");
    v3.load(":/Icons_meteo/vignette3.png");
    v4.load(":/Icons_meteo/vignette4.png");
    v5.load(":/Icons_meteo/vignette5.png");
    v6.load(":/Icons_meteo/vignette6.png");


    if (jours != "sam" || jours != "dim")
    {
        if (heures >="08" && heures <="20")

        {

            ui->label_vignette1->setPixmap(v1);
            ui->label_vignette2->setPixmap(v2);
            ui->label_vignette3->setPixmap(v3);
            ui->label_vignette4->setPixmap(v4);
            ui->label_vignette5->setPixmap(v5);

        }

        else
        {

            ui->label_vignette1->setPixmap(v1);
            ui->label_vignette2->setPixmap(v2);
            ui->label_vignette3->setPixmap(v3);
            ui->label_vignette4->setPixmap(v4);
            ui->label_vignette5->setPixmap(v5);
            ui->label_vignette6->setPixmap(v6);


        }

    }

}

void Dialog::pollutionChart()                           //Création et remplissage du graphique
{


    /* Ajout des titres des sets*/

    set0 = new QBarSet(tr("Taux Actuel"));
    set1 = new QBarSet(tr("Objectifs de Qualité"));
    set2 = new QBarSet(tr("Valeurs Limites"));

    /*Récupération des taux de pollutions grace à la fonction prinHashpollution */

    QHash <QString, QVariant> pol=printHashpollution();

    int p1,p2,p3,p4,p5,p6;

    p1 = pol.value("PM25").toInt();
    p2 = pol.value("PM10").toInt();
    p3 = pol.value("O3").toInt();
    p4 = pol.value("NO2").toInt();
    p5 = (pol.value("CO").toInt())/100;
    p6 = pol.value("SO2").toInt();


    *set0 << p1 << p2 << p3 << p4 << p5 << p6;     //Taux actuels récupérer par l'API pollution
    *set1 << 10 << 30 << 120 << 40 << 10000/100 << 50;                                                                                                                                                        //Normes de ces polluants
    *set2 << 25 << 50 << 240 << 200<< 10000/100 << 125 ;


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Pollution par polluant"));
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList categories;
    categories << "PM25" << "PM10" << "O3" << "NO2" << "CO" << "SO2";

    /* Définiton du max*/

    QValueAxis *axisY = new QValueAxis();

    int mymax[] = {p1,p2,p3,p4,p5,p6};
    int *max;
    max = std::max_element (mymax,mymax+6);

    if (*max <= 240)
    {
        axisY->setRange(0,240+10);                       //240 correspond au maximum des valeurs limites des polluants.
    }

    else {
        axisY->setRange(0,*max+10);
    }

    axisY->setTitleText(tr("Concentration (µg/m³)"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    gridLayout = new QGridLayout(ui->widgetPollution);
    gridLayout->addWidget(chartView);

    chart->setAnimationDuration(2000);
    chart->setAnimationOptions(QChart::AllAnimations);

    QFont font;
    font.setPixelSize(20);
    font.setBold(1);
    chart->setTitleFont(font);



}

void Dialog::AQI()                                  //affichage de l'AQI et l'icone correspondante
{

    QPixmap fondPlan;
    QHash <QString, QVariant> aqi=printHashpollution();
    int aqi_value= aqi.value("AQI").toInt();
    QString aq=tr("Indice Qualité Air ");

    if (aqi_value>=0 && aqi_value<=50)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#39962e\">%0: %1</font>").arg(tr("Bon: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_g.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#39962e\">%1</font>").arg(aq));
    }

    else if (aqi_value>=51 && aqi_value<=100)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#eded2d\">%0 %1</font>").arg(tr("Modéré: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_m.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#eded2d\">%1</font>").arg(aq));
    }

    else if (aqi_value>=101 && aqi_value<=150)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#f99c2a\">%0 %1</font>").arg(tr("Malsain pour sensible: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_u1.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#f99c2a\">%1</font>").arg(aq));
    }

    else if (aqi_value>=151 && aqi_value<=200)
    {
        ui->label_DAQI->setText(QString("<font color=\"#ef2121\">%0 %1</font>").arg(tr("Malsain: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_u2.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#ef2121\">%1</font>").arg(aq));
    }

    else if (aqi_value>=201 && aqi_value<=300)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#9920ef\">%0 %1</font>").arg(tr("Très Malsain!: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_vu.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#9920ef\">%1</font>").arg(aq));
    }

    else
    {
        ui->label_DAQI->setText(QString ("<font color=\"#c11b1b\">%0 %1</font>").arg(tr("Risqué!!: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_h.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#c11b1b\">%1</font>").arg(aq));

    }



}

void Dialog::Icon()                                        //affichage de l'icone meteo
{

    QHash <QString, QVariant>hash_meteo;
    hash_meteo=m_meteo->getHash();
    QString icon=hash_meteo.value("icon").toString();
    QPixmap ic;

    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->labelIcon->setPixmap(ic);

}

void Dialog::loadlanguage(QString lang)
{

    qDebug() << "Iciiiiiiiii!!!!!";

    qDebug() << lang;
    QTranslator translator;

    if(lang == "Anglais")
    {
        qDebug()<< translator.load(":/Traduction/src_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }

    else if(lang == "Français")
    {
        qDebug()<< translator.load(":/Traduction/src_fr.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }

    else if(lang == "Arabe")
    {
        qDebug()<< translator.load(":/Traduction/src_ar.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }



    l_lang->hide();


}



void Dialog::printHashmeteo()                              //création et remplissage du tableWidget
{

    QHash <QString, QVariant>hash_meteo;
    hash_meteo=m_meteo->getHash();


    /*Remplissage du QTableView avec les données*/


    QStandardItemModel *model=new QStandardItemModel(7,2,this);

    item1->setData(tr("Température max (°C)"),0);
    model->setItem(0, 0, item1);
    item2->setData(tr("Température min (°C)"),0);
    model->setItem(1, 0, item2);
    item3->setData(tr("Ciel "),0);
    model->setItem(2, 0, item3);
    item4->setData(tr("Humidité (%)"),0);
    model->setItem(3, 0, item4);
    item5->setData(tr("Vitesse du vent (km/h)"),0);
    model->setItem(4, 0, item5);
    item6->setData(tr("Direction du vent (°)"),0);
    model->setItem(5, 0, item6);
    item7->setData(tr("Pression (hPa)"),0);
    model->setItem(6, 0, item7);


    for (int i=0;i<=6;i++)
    {

        QStandardItem *m = new QStandardItem;
        m->setText(hash_meteo.value(QString ("%1").arg(i)).toString());
        model->setItem(i,1,m);


    }


    /*Configuration du tableView*/

    ui->tableView->setModel(model);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnWidth(0,400);
    ui->tableView->setColumnWidth(1,200);


    //ui->tableView->setDisabled(1);
    ui->tableView->setFont(QFont("Ubuntu", 16, QFont::Bold));


    QString t = hash_meteo.value("temp").toString();
    ui->labelTemp->setText(QString ("%1 °C").arg(t));
    ui->labelCiel->setText(hash_meteo.value("main").toString());



}

void Dialog::printHashprevision()
{

    QHash <QString, QVariant>hash_prevision;
    hash_prevision=pm_prevision->getHash();


    QPixmap ic;
    QString icon;
    double t1,t2,t3,t4,t5,t6,t7,t8;
    QDateTime dh1,dh2,dh3,dh4,dh5,dh6,dh7,dh8;
    QString h1,h2,h3,h4,h5,h6,h7,h8;


    /*Affichage des icones dans l'onglet prévision*/

    icon=hash_prevision.value("Icon1").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon1->setPixmap(ic);

    icon=hash_prevision.value("Icon2").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon2->setPixmap(ic);

    icon=hash_prevision.value("Icon3").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon3->setPixmap(ic);

    icon=hash_prevision.value("Icon4").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon4->setPixmap(ic);

    icon=hash_prevision.value("Icon5").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon5->setPixmap(ic);

    icon=hash_prevision.value("Icon6").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon6->setPixmap(ic);

    icon=hash_prevision.value("Icon7").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon7->setPixmap(ic);

    icon=hash_prevision.value("Icon8").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon8->setPixmap(ic);





    /*Affichage des températures dans l'onglet prévision*/

    t1 = hash_prevision.value("Temp1").toDouble();
    ui->label_value1->setText(QString ("%1 °C").arg(t1));

    t2 = hash_prevision.value("Temp2").toDouble();
    ui->label_value2->setText(QString ("%1 °C").arg(t2));

    t3 = hash_prevision.value("Temp3").toDouble();
    ui->label_value3->setText(QString ("%1 °C").arg(t3));

    t4 = hash_prevision.value("Temp4").toDouble();
    ui->label_value4->setText(QString ("%1 °C").arg(t4));

    t5 = hash_prevision.value("Temp5").toDouble();
    ui->label_value5->setText(QString ("%1 °C").arg(t5));

    t6 = hash_prevision.value("Temp6").toDouble();
    ui->label_value6->setText(QString ("%1 °C").arg(t6));

    t7 = hash_prevision.value("Temp7").toDouble();
    ui->label_value7->setText(QString ("%1 °C").arg(t7));

    t8 = hash_prevision.value("Temp8").toDouble();
    ui->label_value8->setText(QString ("%1 °C").arg(t8));



    /*Affichage des dates dans l'onglet prévision*/


    dh1 = hash_prevision.value("Date_heure1").toDateTime();
    h1 = dh1.toString("hh:mm");
    ui->label_date1->setText(h1);

    dh2 = hash_prevision.value("Date_heure2").toDateTime();
    h2 = dh2.toString("hh:mm");
    ui->label_date2->setText(h2);

    dh3 = hash_prevision.value("Date_heure3").toDateTime();
    h3 = dh3.toString("hh:mm");
    ui->label_date3->setText(h3);

    dh4 = hash_prevision.value("Date_heure4").toDateTime();
    h4 = dh4.toString("hh:mm");
    ui->label_date4->setText(h4);

    dh5 = hash_prevision.value("Date_heure5").toDateTime();
    h5 = dh5.toString("hh:mm");
    ui->label_date5->setText(h5);

    dh6 = hash_prevision.value("Date_heure6").toDateTime();
    h6 = dh6.toString("hh:mm");
    ui->label_date6->setText(h6);

    dh7 = hash_prevision.value("Date_heure7").toDateTime();
    h7 = dh7.toString("hh:mm");
    ui->label_date7->setText(h7);

    dh8 = hash_prevision.value("Date_heure8").toDateTime();
    h8 = dh8.toString("hh:mm");
    ui->label_date8->setText(h8);


    /*Création du graphique de l'onglet prévision*/

    QChart *chart = new QChart();

    /*Définiton de Line Series pour courbe température*/

    QLineSeries *series = new QLineSeries();

    series->append(0, t1);
    series->append(1, t2);
    series->append(2, t3);
    series->append(3, t4);
    series->append(4, t5);
    series->append(5, t6);
    series->append(6, t7);
    series->append(7, t8);

    /*Récupération précipitation en mm*/


    double r1, r2, r3, r4, r5, r6, r7, r8;
    r1 = hash_prevision.value("Rain1").toDouble();
    r2 = hash_prevision.value("Rain2").toDouble();
    r3 = hash_prevision.value("Rain3").toDouble();
    r4 = hash_prevision.value("Rain4").toDouble();
    r5 = hash_prevision.value("Rain5").toDouble();
    r6 = hash_prevision.value("Rain6").toDouble();
    r7 = hash_prevision.value("Rain7").toDouble();
    r8 = hash_prevision.value("Rain8").toDouble();

    /*Création d'un QBarSet*/

    QBarSet *set4;
    set4 = new QBarSet(tr("Précipitation"));
    *set4 << r1 << r2 << r3 << r4 << r5 << r6 << r7 << r8;
    set4->setColor(QColor(39, 114, 234));

    /*Création d'un QBarSeries*/

    QBarSeries *series1 = new QBarSeries();
    series1->append(set4);
    chart->addSeries(series1);

    /*Création de l'axe Y1 (précipitation)*/

    QValueAxis *axisY1 = new QValueAxis();

    /*Définition du max de l'axe Y1*/

    double mymaxp[] = {r1,r2,r3,r4,r5,r6,r7,r8};
    double *maxp;
    maxp = std::max_element (mymaxp,mymaxp+8);

    axisY1->setRange(0,*maxp+1);
    axisY1->setTitleText(tr("Précipitaion en mm"));
    axisY1->setLabelsColor(QColor(39, 114, 234));
    chart->addAxis(axisY1, Qt::AlignRight);
    series1->attachAxis(axisY1);


    /*Création de l'axe Y (température)*/

    QValueAxis *axisY = new QValueAxis();

    /*Définition du max de l'axe Y*/

    double mymax[] = {t1,t2,t3,t4,t5,t6,t7,t8};
    double *max;
    max = std::max_element (mymax,mymax+8);
    int rmax= int (*max);

    /*Définition du min de l'axe Y*/

    double mymin[] = {t1,t2,t3,t4,t5,t6,t7,t8};
    double *min;
    min = std::min_element (mymin,mymin+8);
    int rmin= int (*min);

    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(series);

    series->attachAxis(axisY);
    series->setColor(QColor(234, 114, 39));

    axisY->setRange(rmin-5,rmax+5);
    axisY->setTitleText(tr("Température en °C"));
    axisY->setLabelsColor(Qt::blue);
    axisY->setLabelsColor(QColor(234, 114, 39));
    axisY->setLabelFormat("%.1f");


    /*Création de l'axe X (heure)*/


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QStringList categories;
    categories << h1 << h2 << h3 << h4 << h5 << h6 << h7 << h8;
    axisX->append(categories);
    axisX->setTitleText(tr("Heure"));
    //axisX->setLabelsColor(255);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    gridLayout = new QGridLayout(ui->widgetPrevision);
    gridLayout->addWidget(chartView);

    /*Option du graphique*/
    chart->setAnimationDuration(2000);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(0);
    chart->setTitle(tr("Prévision météo pour les prochaines 24h"));

    QFont font;
    font.setPixelSize(20);
    font.setBold(1);
    chart->setTitleFont(font);



}

QHash <QString, QVariant> Dialog::printHashpollution()        //récupération des données pollution
{

    QHash <QString, QVariant>hash_pollution;
    hash_pollution=p_pollution->getHash();
    return hash_pollution;

}

void Dialog::printHashindice()                                 //Affichage de l'indice UV et de l'icon correspondante
{


    QHash <QString, QVariant>indice;
    indice=i_indice->getHash();
    int indice_value=indice.value("UV").toInt();
    QString ind=tr("Indice UV ");



    if (indice_value>=0 && indice_value<=2)
    {
        ui->label_DUV->setText(QString ("<font color=\"#0fc133\">%0 %1</font>").arg(tr("Faible: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#0fc133\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#0fc133\">%1</font>").arg(ind));

    }

    else if (indice_value>=3 && indice_value<=5)
    {
        ui->label_DUV->setText(QString ("<font color=\"#f9eb25\">%0 %1</font>").arg(tr("Moyen: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#f9eb25\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#f9eb25\">%1</font>").arg(ind));
    }

    else if (indice_value>=6 && indice_value<=7)
    {
        ui->label_DUV->setText(QString ("<font color=\"#ff9011\">%0 %1</font>").arg(tr("Élevé!: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#ff9011\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#ff9011\">%1</font>").arg(ind));
    }

    else if (indice_value>=8 && indice_value<=10)
    {
        ui->label_DUV->setText(QString ("<font color=\"#e00f0f\">%0 %1</font>").arg(tr("Très Élevé!!: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#e00f0f\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#e00f0f\">%1</font>").arg(ind));
    }

    else {

        ui->label_DUV->setText(QString ("<font color=\"#c669e5\">%0 %1</font>").arg(tr("Extreme!!!: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#c669e5\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#c669e5\">%1</font>").arg(ind));
    }

    ui->label_DUV->setFont(QFont("Ubuntu",16,QFont::Bold));
}




/*Unité
 *
 * Longitude(°,')
 * Latitude(°,')
 * Pression(hPa)
 * Température(°C)
 * Humidité(%)
 * Vitesse du vent(km/h)
 * Direction du vent(°)
 * Heure levé du Soleil
 * Heure couché du Soleil
 * Temps
 *
 * */

