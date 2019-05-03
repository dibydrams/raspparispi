/********************************************************************************
** Form generated from reading UI file 'dialogmeteo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMETEO_H
#define UI_DIALOGMETEO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *meteo;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_close;
    QLabel *labeltitre;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelIcon;
    QLabel *labelTemp;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelCiel;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelDate;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_10;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_13;
    QLabel *label_TUV;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_indUV;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_DUV;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QLabel *label_UVprotection;
    QWidget *prevision;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_13;
    QWidget *widgetPrevision;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer_35;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_32;
    QLabel *label_date1;
    QLabel *label_icon1;
    QLabel *label_value1;
    QSpacerItem *horizontalSpacer_12;
    QVBoxLayout *verticalLayout_33;
    QLabel *label_date2;
    QLabel *label_icon2;
    QLabel *label_value2;
    QSpacerItem *horizontalSpacer_13;
    QVBoxLayout *verticalLayout_34;
    QLabel *label_date3;
    QLabel *label_icon3;
    QLabel *label_value3;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout_35;
    QLabel *label_date4;
    QLabel *label_icon4;
    QLabel *label_value4;
    QSpacerItem *horizontalSpacer_15;
    QVBoxLayout *verticalLayout_36;
    QLabel *label_date5;
    QLabel *label_icon5;
    QLabel *label_value5;
    QSpacerItem *horizontalSpacer_16;
    QVBoxLayout *verticalLayout_37;
    QLabel *label_date6;
    QLabel *label_icon6;
    QLabel *label_value6;
    QSpacerItem *horizontalSpacer_17;
    QVBoxLayout *verticalLayout_38;
    QLabel *label_date7;
    QLabel *label_icon7;
    QLabel *label_value7;
    QSpacerItem *horizontalSpacer_18;
    QVBoxLayout *verticalLayout_39;
    QLabel *label_date8;
    QLabel *label_icon8;
    QLabel *label_value8;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_36;
    QWidget *pollution;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_12;
    QWidget *widgetPollution;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_IAQI;
    QLabel *label_DAQI;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label_vignette1;
    QSpacerItem *horizontalSpacer;
    QLabel *label_vignette2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_vignette3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_vignette4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_vignette5;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_vignette6;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *verticalSpacer_6;
    QFrame *line;
    QSpacerItem *verticalSpacer_11;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1162, 558);
        verticalLayout_6 = new QVBoxLayout(Dialog);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(1144, 540));
        tabWidget->setMaximumSize(QSize(1144, 540));
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setIconSize(QSize(25, 16));
        meteo = new QWidget();
        meteo->setObjectName(QString::fromUtf8("meteo"));
        verticalLayout_4 = new QVBoxLayout(meteo);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pushButton_close = new QPushButton(meteo);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setMinimumSize(QSize(30, 30));
        pushButton_close->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons_meteo/close_1-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_close->setIcon(icon);
        pushButton_close->setIconSize(QSize(20, 20));

        horizontalLayout_10->addWidget(pushButton_close);

        labeltitre = new QLabel(meteo);
        labeltitre->setObjectName(QString::fromUtf8("labeltitre"));
        QFont font;
        font.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        labeltitre->setFont(font);

        horizontalLayout_10->addWidget(labeltitre, 0, Qt::AlignHCenter);


        verticalLayout->addLayout(horizontalLayout_10);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(68, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        labelIcon = new QLabel(meteo);
        labelIcon->setObjectName(QString::fromUtf8("labelIcon"));

        horizontalLayout_2->addWidget(labelIcon);

        labelTemp = new QLabel(meteo);
        labelTemp->setObjectName(QString::fromUtf8("labelTemp"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font1.setPointSize(24);
        font1.setBold(true);
        font1.setWeight(75);
        labelTemp->setFont(font1);

        horizontalLayout_2->addWidget(labelTemp);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_8 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        labelCiel = new QLabel(meteo);
        labelCiel->setObjectName(QString::fromUtf8("labelCiel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        labelCiel->setFont(font2);

        horizontalLayout_3->addWidget(labelCiel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_9 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        labelDate = new QLabel(meteo);
        labelDate->setObjectName(QString::fromUtf8("labelDate"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        labelDate->setFont(font3);

        horizontalLayout_4->addWidget(labelDate);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_10 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_10);

        tableView = new QTableView(meteo);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMinimumSize(QSize(602, 212));
        tableView->setMaximumSize(QSize(602, 212));

        verticalLayout->addWidget(tableView);


        horizontalLayout_16->addLayout(verticalLayout);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_13 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_13);

        label_TUV = new QLabel(meteo);
        label_TUV->setObjectName(QString::fromUtf8("label_TUV"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font4.setPointSize(17);
        font4.setBold(true);
        font4.setWeight(75);
        label_TUV->setFont(font4);

        verticalLayout_5->addWidget(label_TUV, 0, Qt::AlignHCenter);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        label_indUV = new QLabel(meteo);
        label_indUV->setObjectName(QString::fromUtf8("label_indUV"));
        QFont font5;
        font5.setPointSize(50);
        font5.setBold(true);
        font5.setWeight(75);
        label_indUV->setFont(font5);

        verticalLayout_5->addWidget(label_indUV, 0, Qt::AlignHCenter);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        label_DUV = new QLabel(meteo);
        label_DUV->setObjectName(QString::fromUtf8("label_DUV"));
        QFont font6;
        font6.setPointSize(18);
        font6.setBold(true);
        font6.setWeight(75);
        label_DUV->setFont(font6);
        label_DUV->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_DUV);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        verticalLayout_7->addLayout(verticalLayout_5);

        line_2 = new QFrame(meteo);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_2);

        label_UVprotection = new QLabel(meteo);
        label_UVprotection->setObjectName(QString::fromUtf8("label_UVprotection"));
        label_UVprotection->setMinimumSize(QSize(461, 201));
        label_UVprotection->setMaximumSize(QSize(461, 201));

        verticalLayout_7->addWidget(label_UVprotection);


        horizontalLayout_16->addLayout(verticalLayout_7);


        verticalLayout_4->addLayout(horizontalLayout_16);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons_meteo/s2.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(meteo, icon1, QString());
        prevision = new QWidget();
        prevision->setObjectName(QString::fromUtf8("prevision"));
        horizontalLayout_14 = new QHBoxLayout(prevision);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        widgetPrevision = new QWidget(prevision);
        widgetPrevision->setObjectName(QString::fromUtf8("widgetPrevision"));
        widgetPrevision->setMinimumSize(QSize(900, 350));
        widgetPrevision->setMaximumSize(QSize(1100, 370));

        horizontalLayout_13->addWidget(widgetPrevision);

        horizontalSpacer_22 = new QSpacerItem(10, 40, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_22);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalSpacer_35 = new QSpacerItem(105, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_35);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        label_date1 = new QLabel(prevision);
        label_date1->setObjectName(QString::fromUtf8("label_date1"));

        verticalLayout_32->addWidget(label_date1, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        label_icon1 = new QLabel(prevision);
        label_icon1->setObjectName(QString::fromUtf8("label_icon1"));

        verticalLayout_32->addWidget(label_icon1, 0, Qt::AlignHCenter);

        label_value1 = new QLabel(prevision);
        label_value1->setObjectName(QString::fromUtf8("label_value1"));

        verticalLayout_32->addWidget(label_value1, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_32);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        verticalLayout_33 = new QVBoxLayout();
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        label_date2 = new QLabel(prevision);
        label_date2->setObjectName(QString::fromUtf8("label_date2"));

        verticalLayout_33->addWidget(label_date2, 0, Qt::AlignHCenter);

        label_icon2 = new QLabel(prevision);
        label_icon2->setObjectName(QString::fromUtf8("label_icon2"));

        verticalLayout_33->addWidget(label_icon2, 0, Qt::AlignHCenter);

        label_value2 = new QLabel(prevision);
        label_value2->setObjectName(QString::fromUtf8("label_value2"));

        verticalLayout_33->addWidget(label_value2, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_33);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        verticalLayout_34 = new QVBoxLayout();
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        label_date3 = new QLabel(prevision);
        label_date3->setObjectName(QString::fromUtf8("label_date3"));

        verticalLayout_34->addWidget(label_date3, 0, Qt::AlignHCenter);

        label_icon3 = new QLabel(prevision);
        label_icon3->setObjectName(QString::fromUtf8("label_icon3"));

        verticalLayout_34->addWidget(label_icon3, 0, Qt::AlignHCenter);

        label_value3 = new QLabel(prevision);
        label_value3->setObjectName(QString::fromUtf8("label_value3"));

        verticalLayout_34->addWidget(label_value3, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_34);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);

        verticalLayout_35 = new QVBoxLayout();
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        label_date4 = new QLabel(prevision);
        label_date4->setObjectName(QString::fromUtf8("label_date4"));

        verticalLayout_35->addWidget(label_date4, 0, Qt::AlignHCenter);

        label_icon4 = new QLabel(prevision);
        label_icon4->setObjectName(QString::fromUtf8("label_icon4"));

        verticalLayout_35->addWidget(label_icon4, 0, Qt::AlignHCenter);

        label_value4 = new QLabel(prevision);
        label_value4->setObjectName(QString::fromUtf8("label_value4"));

        verticalLayout_35->addWidget(label_value4, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_35);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        verticalLayout_36 = new QVBoxLayout();
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        label_date5 = new QLabel(prevision);
        label_date5->setObjectName(QString::fromUtf8("label_date5"));

        verticalLayout_36->addWidget(label_date5, 0, Qt::AlignHCenter);

        label_icon5 = new QLabel(prevision);
        label_icon5->setObjectName(QString::fromUtf8("label_icon5"));

        verticalLayout_36->addWidget(label_icon5, 0, Qt::AlignHCenter);

        label_value5 = new QLabel(prevision);
        label_value5->setObjectName(QString::fromUtf8("label_value5"));

        verticalLayout_36->addWidget(label_value5, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_36);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);

        verticalLayout_37 = new QVBoxLayout();
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        label_date6 = new QLabel(prevision);
        label_date6->setObjectName(QString::fromUtf8("label_date6"));

        verticalLayout_37->addWidget(label_date6, 0, Qt::AlignHCenter);

        label_icon6 = new QLabel(prevision);
        label_icon6->setObjectName(QString::fromUtf8("label_icon6"));

        verticalLayout_37->addWidget(label_icon6, 0, Qt::AlignHCenter);

        label_value6 = new QLabel(prevision);
        label_value6->setObjectName(QString::fromUtf8("label_value6"));

        verticalLayout_37->addWidget(label_value6, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_37);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        verticalLayout_38 = new QVBoxLayout();
        verticalLayout_38->setObjectName(QString::fromUtf8("verticalLayout_38"));
        label_date7 = new QLabel(prevision);
        label_date7->setObjectName(QString::fromUtf8("label_date7"));

        verticalLayout_38->addWidget(label_date7, 0, Qt::AlignHCenter);

        label_icon7 = new QLabel(prevision);
        label_icon7->setObjectName(QString::fromUtf8("label_icon7"));

        verticalLayout_38->addWidget(label_icon7, 0, Qt::AlignHCenter);

        label_value7 = new QLabel(prevision);
        label_value7->setObjectName(QString::fromUtf8("label_value7"));

        verticalLayout_38->addWidget(label_value7, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_38);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);

        verticalLayout_39 = new QVBoxLayout();
        verticalLayout_39->setObjectName(QString::fromUtf8("verticalLayout_39"));
        label_date8 = new QLabel(prevision);
        label_date8->setObjectName(QString::fromUtf8("label_date8"));

        verticalLayout_39->addWidget(label_date8, 0, Qt::AlignHCenter);

        label_icon8 = new QLabel(prevision);
        label_icon8->setObjectName(QString::fromUtf8("label_icon8"));

        verticalLayout_39->addWidget(label_icon8, 0, Qt::AlignHCenter);

        label_value8 = new QLabel(prevision);
        label_value8->setObjectName(QString::fromUtf8("label_value8"));

        verticalLayout_39->addWidget(label_value8, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_39);


        verticalLayout_2->addLayout(horizontalLayout_8);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout_19->addLayout(verticalLayout_2);

        horizontalSpacer_36 = new QSpacerItem(115, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_36);


        verticalLayout_3->addLayout(horizontalLayout_19);


        horizontalLayout_14->addLayout(verticalLayout_3);

        tabWidget->addTab(prevision, QString());
        pollution = new QWidget();
        pollution->setObjectName(QString::fromUtf8("pollution"));
        verticalLayout_12 = new QVBoxLayout(pollution);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        widgetPollution = new QWidget(pollution);
        widgetPollution->setObjectName(QString::fromUtf8("widgetPollution"));
        widgetPollution->setMinimumSize(QSize(550, 461));
        widgetPollution->setMaximumSize(QSize(550, 461));

        horizontalLayout_12->addWidget(widgetPollution);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalSpacer_12 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_11 = new QSpacerItem(32, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        label = new QLabel(pollution);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(214, 0));
        label->setMaximumSize(QSize(214, 31));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font7.setPointSize(13);
        font7.setBold(true);
        font7.setWeight(75);
        label->setFont(font7);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label);

        horizontalSpacer_19 = new QSpacerItem(33, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_19);


        verticalLayout_9->addLayout(horizontalLayout_7);

        label_IAQI = new QLabel(pollution);
        label_IAQI->setObjectName(QString::fromUtf8("label_IAQI"));

        verticalLayout_9->addWidget(label_IAQI, 0, Qt::AlignHCenter);

        label_DAQI = new QLabel(pollution);
        label_DAQI->setObjectName(QString::fromUtf8("label_DAQI"));
        QFont font8;
        font8.setPointSize(13);
        font8.setBold(true);
        font8.setWeight(75);
        label_DAQI->setFont(font8);
        label_DAQI->setFrameShape(QFrame::NoFrame);
        label_DAQI->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_DAQI, 0, Qt::AlignHCenter);


        horizontalLayout_11->addLayout(verticalLayout_9);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_10 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_2 = new QLabel(pollution);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font9.setPointSize(15);
        font9.setBold(true);
        font9.setWeight(75);
        label_2->setFont(font9);

        verticalLayout_10->addWidget(label_2, 0, Qt::AlignHCenter);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_vignette1 = new QLabel(pollution);
        label_vignette1->setObjectName(QString::fromUtf8("label_vignette1"));
        label_vignette1->setMinimumSize(QSize(51, 51));
        label_vignette1->setMaximumSize(QSize(51, 51));

        horizontalLayout->addWidget(label_vignette1);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_vignette2 = new QLabel(pollution);
        label_vignette2->setObjectName(QString::fromUtf8("label_vignette2"));
        label_vignette2->setMinimumSize(QSize(51, 51));
        label_vignette2->setMaximumSize(QSize(51, 51));

        horizontalLayout->addWidget(label_vignette2);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_vignette3 = new QLabel(pollution);
        label_vignette3->setObjectName(QString::fromUtf8("label_vignette3"));
        label_vignette3->setMinimumSize(QSize(51, 51));
        label_vignette3->setMaximumSize(QSize(51, 51));

        horizontalLayout_5->addWidget(label_vignette3);

        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_vignette4 = new QLabel(pollution);
        label_vignette4->setObjectName(QString::fromUtf8("label_vignette4"));
        label_vignette4->setMinimumSize(QSize(51, 51));
        label_vignette4->setMaximumSize(QSize(51, 51));

        horizontalLayout_5->addWidget(label_vignette4);


        verticalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_vignette5 = new QLabel(pollution);
        label_vignette5->setObjectName(QString::fromUtf8("label_vignette5"));
        label_vignette5->setMinimumSize(QSize(51, 51));
        label_vignette5->setMaximumSize(QSize(51, 51));

        horizontalLayout_6->addWidget(label_vignette5);

        horizontalSpacer_9 = new QSpacerItem(28, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        label_vignette6 = new QLabel(pollution);
        label_vignette6->setObjectName(QString::fromUtf8("label_vignette6"));
        label_vignette6->setMinimumSize(QSize(51, 51));
        label_vignette6->setMaximumSize(QSize(51, 51));

        horizontalLayout_6->addWidget(label_vignette6);


        verticalLayout_8->addLayout(horizontalLayout_6);


        verticalLayout_10->addLayout(verticalLayout_8);


        horizontalLayout_9->addLayout(verticalLayout_10);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_20);


        horizontalLayout_11->addLayout(horizontalLayout_9);


        verticalLayout_11->addLayout(horizontalLayout_11);

        verticalSpacer_6 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer_6);

        line = new QFrame(pollution);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_11->addWidget(line);

        verticalSpacer_11 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer_11);

        textBrowser = new QTextBrowser(pollution);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QFont font10;
        font10.setPointSize(9);
        textBrowser->setFont(font10);
        textBrowser->setContextMenuPolicy(Qt::DefaultContextMenu);
        textBrowser->setAutoFillBackground(false);
        textBrowser->setFrameShape(QFrame::NoFrame);
        textBrowser->setFrameShadow(QFrame::Sunken);
        textBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_11->addWidget(textBrowser);


        horizontalLayout_12->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_12);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons_meteo/pollution.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(pollution, icon2, QString());

        verticalLayout_6->addWidget(tabWidget);


        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "M\303\251t\303\251o de Paris", nullptr));
        pushButton_close->setText(QString());
        labeltitre->setText(QApplication::translate("Dialog", "M\303\251t\303\251o de Paris", nullptr));
        labelIcon->setText(QApplication::translate("Dialog", "Icon", nullptr));
        labelTemp->setText(QApplication::translate("Dialog", "Temp\303\251rature", nullptr));
        labelCiel->setText(QApplication::translate("Dialog", "Ciel", nullptr));
        labelDate->setText(QApplication::translate("Dialog", "DATE et heure", nullptr));
        label_TUV->setText(QApplication::translate("Dialog", "Indice UV", nullptr));
        label_indUV->setText(QApplication::translate("Dialog", "UV", nullptr));
        label_DUV->setText(QApplication::translate("Dialog", "Indice Uv", nullptr));
        label_UVprotection->setText(QApplication::translate("Dialog", "ProtectionUV", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(meteo), QApplication::translate("Dialog", "M\303\251t\303\251o", nullptr));
        label_date1->setText(QApplication::translate("Dialog", "Date1", nullptr));
        label_icon1->setText(QApplication::translate("Dialog", "Icon1", nullptr));
        label_value1->setText(QApplication::translate("Dialog", "Temp1", nullptr));
        label_date2->setText(QApplication::translate("Dialog", "Date2", nullptr));
        label_icon2->setText(QApplication::translate("Dialog", "Icon2", nullptr));
        label_value2->setText(QApplication::translate("Dialog", "Temp2", nullptr));
        label_date3->setText(QApplication::translate("Dialog", "Date3", nullptr));
        label_icon3->setText(QApplication::translate("Dialog", "Icon3", nullptr));
        label_value3->setText(QApplication::translate("Dialog", "Temp3", nullptr));
        label_date4->setText(QApplication::translate("Dialog", "Date4", nullptr));
        label_icon4->setText(QApplication::translate("Dialog", "Icon4", nullptr));
        label_value4->setText(QApplication::translate("Dialog", "Temp4", nullptr));
        label_date5->setText(QApplication::translate("Dialog", "Date5", nullptr));
        label_icon5->setText(QApplication::translate("Dialog", "Icon5", nullptr));
        label_value5->setText(QApplication::translate("Dialog", "Temp5", nullptr));
        label_date6->setText(QApplication::translate("Dialog", "Date6", nullptr));
        label_icon6->setText(QApplication::translate("Dialog", "Icon6", nullptr));
        label_value6->setText(QApplication::translate("Dialog", "Temp6", nullptr));
        label_date7->setText(QApplication::translate("Dialog", "Date7", nullptr));
        label_icon7->setText(QApplication::translate("Dialog", "Icon7", nullptr));
        label_value7->setText(QApplication::translate("Dialog", "Temp7", nullptr));
        label_date8->setText(QApplication::translate("Dialog", "Date8", nullptr));
        label_icon8->setText(QApplication::translate("Dialog", "Icon8", nullptr));
        label_value8->setText(QApplication::translate("Dialog", "Temp8", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(prevision), QApplication::translate("Dialog", "Pr\303\251vision", nullptr));
#ifndef QT_NO_TOOLTIP
        pollution->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("Dialog", "Indice Qualit\303\251 de l'air", nullptr));
        label_IAQI->setText(QApplication::translate("Dialog", "Image AQI", nullptr));
        label_DAQI->setText(QApplication::translate("Dialog", "LABEL", nullptr));
        label_2->setText(QApplication::translate("Dialog", "Crit'Air", nullptr));
        label_vignette1->setText(QString());
        label_vignette2->setText(QString());
        label_vignette3->setText(QString());
        label_vignette4->setText(QString());
        label_vignette5->setText(QString());
        label_vignette6->setText(QString());
        textBrowser->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">PM (Particules en suspension) :</span></p>\n"
"<table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\">\n"
"<tr>\n"
"<td width=\"20\"></td>\n"
"<td>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">- les particules PM10, (taille inf\303\251rieure \303\240 10 \302\265m), p\303\251n\303\250trent da"
                        "ns l'appareil respiratoire.</span></p></td></tr>\n"
"<tr>\n"
"<td></td>\n"
"<td>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">- les particules fines ou PM2,5 (inf\303\251rieures ou \303\251gales \303\240 2,5 \302\265m),p\303\251n\303\250trent dans les ramifications des voies respiratoires (alv\303\251oles).</span></p></td></tr></table>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">O3 (Ozone) : </span><span style=\" font-size:8pt;\">polluant qui irrite les yeux et l'appareil respiratoire, et qui a des effets sur la v\303\251g\303\251tation.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600"
                        ";\">NO2 (Oxydes d'azote) : </span><span style=\" font-size:8pt;\">gaz irritant pour les bronches (\303\251mis principalement par le trafic routier).</span></p>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">CO (Monoxyde de carbone) : </span><span style=\" font-size:8pt;\">gaz provennant majoritairement des gaz d'\303\251chappement des v\303\251hicules. Peut provoquer des intoxications.</span></p>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">SO2 (Dioxyde de soufre) : </span><span style=\" font-size:8pt;\">gaz qui irrite les muqueuses de la peau et des voies respiratoires sup\303\251rieures.</span><span style=\" font-size:8pt; font-weight:600;\"><br /></span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pollution), QApplication::translate("Dialog", "Pollution", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMETEO_H
