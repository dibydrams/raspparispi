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
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_7;
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
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_IUV;
    QLabel *label_DUV;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_12;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_IAQI;
    QLabel *label_DAQI;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_9;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_vignette1;
    QLabel *label_vignette2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_vignette3;
    QLabel *label_vignette4;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_vignette5;
    QLabel *label_vignette6;
    QWidget *widgetPollution;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QWidget *widgetPrevision;
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

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1253, 720);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_7 = new QHBoxLayout(tab);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        labeltitre = new QLabel(tab);
        labeltitre->setObjectName(QString::fromUtf8("labeltitre"));
        QFont font;
        font.setFamily(QString::fromUtf8("Droid Sans Fallback"));
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        labeltitre->setFont(font);

        verticalLayout_7->addWidget(labeltitre, 0, Qt::AlignHCenter);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(68, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        labelIcon = new QLabel(tab);
        labelIcon->setObjectName(QString::fromUtf8("labelIcon"));

        horizontalLayout_2->addWidget(labelIcon);

        labelTemp = new QLabel(tab);
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


        verticalLayout_7->addLayout(horizontalLayout_2);

        verticalSpacer_8 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        labelCiel = new QLabel(tab);
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


        verticalLayout_7->addLayout(horizontalLayout_3);

        verticalSpacer_9 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        labelDate = new QLabel(tab);
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


        verticalLayout_7->addLayout(horizontalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalSpacer_10 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 7)
            tableWidget->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QBrush brush1(QColor(239, 41, 41, 255));
        brush1.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setBackground(brush1);
        tableWidget->setItem(0, 0, __qtablewidgetitem8);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMinimumSize(QSize(270, 233));
        tableWidget->setMaximumSize(QSize(270, 233));
        tableWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setIconSize(QSize(0, 0));
        tableWidget->setTextElideMode(Qt::ElideLeft);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout->addWidget(tableWidget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        verticalLayout_7->addLayout(verticalLayout_6);


        verticalLayout_13->addLayout(verticalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_5);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_IUV = new QLabel(tab);
        label_IUV->setObjectName(QString::fromUtf8("label_IUV"));

        verticalLayout_5->addWidget(label_IUV, 0, Qt::AlignHCenter);

        label_DUV = new QLabel(tab);
        label_DUV->setObjectName(QString::fromUtf8("label_DUV"));
        QFont font4;
        font4.setPointSize(13);
        font4.setBold(true);
        font4.setWeight(75);
        label_DUV->setFont(font4);
        label_DUV->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_DUV, 0, Qt::AlignHCenter);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_5->addWidget(label_4, 0, Qt::AlignHCenter);


        verticalLayout_11->addLayout(verticalLayout_5);


        horizontalLayout_5->addLayout(verticalLayout_11);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_6);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_IAQI = new QLabel(tab);
        label_IAQI->setObjectName(QString::fromUtf8("label_IAQI"));

        verticalLayout_10->addWidget(label_IAQI, 0, Qt::AlignHCenter);

        label_DAQI = new QLabel(tab);
        label_DAQI->setObjectName(QString::fromUtf8("label_DAQI"));
        label_DAQI->setFont(font4);
        label_DAQI->setFrameShape(QFrame::NoFrame);
        label_DAQI->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_DAQI, 0, Qt::AlignHCenter);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_10->addWidget(label_3, 0, Qt::AlignHCenter);


        verticalLayout_12->addLayout(verticalLayout_10);


        horizontalLayout_5->addLayout(verticalLayout_12);

        horizontalSpacer_9 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_vignette1 = new QLabel(tab);
        label_vignette1->setObjectName(QString::fromUtf8("label_vignette1"));
        label_vignette1->setMinimumSize(QSize(51, 51));
        label_vignette1->setMaximumSize(QSize(51, 51));

        horizontalLayout_14->addWidget(label_vignette1, 0, Qt::AlignHCenter);

        label_vignette2 = new QLabel(tab);
        label_vignette2->setObjectName(QString::fromUtf8("label_vignette2"));
        label_vignette2->setMinimumSize(QSize(51, 51));
        label_vignette2->setMaximumSize(QSize(51, 51));

        horizontalLayout_14->addWidget(label_vignette2, 0, Qt::AlignHCenter);


        verticalLayout_8->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_vignette3 = new QLabel(tab);
        label_vignette3->setObjectName(QString::fromUtf8("label_vignette3"));
        label_vignette3->setMinimumSize(QSize(51, 51));
        label_vignette3->setMaximumSize(QSize(51, 51));

        horizontalLayout_15->addWidget(label_vignette3);

        label_vignette4 = new QLabel(tab);
        label_vignette4->setObjectName(QString::fromUtf8("label_vignette4"));
        label_vignette4->setMinimumSize(QSize(51, 51));
        label_vignette4->setMaximumSize(QSize(51, 51));

        horizontalLayout_15->addWidget(label_vignette4, 0, Qt::AlignHCenter);


        verticalLayout_8->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_vignette5 = new QLabel(tab);
        label_vignette5->setObjectName(QString::fromUtf8("label_vignette5"));
        label_vignette5->setMinimumSize(QSize(51, 51));
        label_vignette5->setMaximumSize(QSize(51, 51));

        horizontalLayout_16->addWidget(label_vignette5, 0, Qt::AlignHCenter);

        label_vignette6 = new QLabel(tab);
        label_vignette6->setObjectName(QString::fromUtf8("label_vignette6"));
        label_vignette6->setMinimumSize(QSize(51, 51));
        label_vignette6->setMaximumSize(QSize(51, 51));

        horizontalLayout_16->addWidget(label_vignette6, 0, Qt::AlignHCenter);


        verticalLayout_8->addLayout(horizontalLayout_16);


        verticalLayout_9->addLayout(verticalLayout_8);


        horizontalLayout_5->addLayout(verticalLayout_9);


        verticalLayout_13->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_13);

        widgetPollution = new QWidget(tab);
        widgetPollution->setObjectName(QString::fromUtf8("widgetPollution"));
        widgetPollution->setMinimumSize(QSize(781, 621));

        horizontalLayout_6->addWidget(widgetPollution);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widgetPrevision = new QWidget(tab_2);
        widgetPrevision->setObjectName(QString::fromUtf8("widgetPrevision"));
        widgetPrevision->setMinimumSize(QSize(1211, 501));

        verticalLayout_3->addWidget(widgetPrevision);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalSpacer_35 = new QSpacerItem(128, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_35);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        label_date1 = new QLabel(tab_2);
        label_date1->setObjectName(QString::fromUtf8("label_date1"));

        verticalLayout_32->addWidget(label_date1, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        label_icon1 = new QLabel(tab_2);
        label_icon1->setObjectName(QString::fromUtf8("label_icon1"));

        verticalLayout_32->addWidget(label_icon1, 0, Qt::AlignHCenter);

        label_value1 = new QLabel(tab_2);
        label_value1->setObjectName(QString::fromUtf8("label_value1"));

        verticalLayout_32->addWidget(label_value1, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_32);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        verticalLayout_33 = new QVBoxLayout();
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        label_date2 = new QLabel(tab_2);
        label_date2->setObjectName(QString::fromUtf8("label_date2"));

        verticalLayout_33->addWidget(label_date2, 0, Qt::AlignHCenter);

        label_icon2 = new QLabel(tab_2);
        label_icon2->setObjectName(QString::fromUtf8("label_icon2"));

        verticalLayout_33->addWidget(label_icon2, 0, Qt::AlignHCenter);

        label_value2 = new QLabel(tab_2);
        label_value2->setObjectName(QString::fromUtf8("label_value2"));

        verticalLayout_33->addWidget(label_value2, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_33);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        verticalLayout_34 = new QVBoxLayout();
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        label_date3 = new QLabel(tab_2);
        label_date3->setObjectName(QString::fromUtf8("label_date3"));

        verticalLayout_34->addWidget(label_date3, 0, Qt::AlignHCenter);

        label_icon3 = new QLabel(tab_2);
        label_icon3->setObjectName(QString::fromUtf8("label_icon3"));

        verticalLayout_34->addWidget(label_icon3, 0, Qt::AlignHCenter);

        label_value3 = new QLabel(tab_2);
        label_value3->setObjectName(QString::fromUtf8("label_value3"));

        verticalLayout_34->addWidget(label_value3, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_34);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);

        verticalLayout_35 = new QVBoxLayout();
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        label_date4 = new QLabel(tab_2);
        label_date4->setObjectName(QString::fromUtf8("label_date4"));

        verticalLayout_35->addWidget(label_date4, 0, Qt::AlignHCenter);

        label_icon4 = new QLabel(tab_2);
        label_icon4->setObjectName(QString::fromUtf8("label_icon4"));

        verticalLayout_35->addWidget(label_icon4, 0, Qt::AlignHCenter);

        label_value4 = new QLabel(tab_2);
        label_value4->setObjectName(QString::fromUtf8("label_value4"));

        verticalLayout_35->addWidget(label_value4, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_35);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        verticalLayout_36 = new QVBoxLayout();
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        label_date5 = new QLabel(tab_2);
        label_date5->setObjectName(QString::fromUtf8("label_date5"));

        verticalLayout_36->addWidget(label_date5, 0, Qt::AlignHCenter);

        label_icon5 = new QLabel(tab_2);
        label_icon5->setObjectName(QString::fromUtf8("label_icon5"));

        verticalLayout_36->addWidget(label_icon5, 0, Qt::AlignHCenter);

        label_value5 = new QLabel(tab_2);
        label_value5->setObjectName(QString::fromUtf8("label_value5"));

        verticalLayout_36->addWidget(label_value5, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_36);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);

        verticalLayout_37 = new QVBoxLayout();
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        label_date6 = new QLabel(tab_2);
        label_date6->setObjectName(QString::fromUtf8("label_date6"));

        verticalLayout_37->addWidget(label_date6, 0, Qt::AlignHCenter);

        label_icon6 = new QLabel(tab_2);
        label_icon6->setObjectName(QString::fromUtf8("label_icon6"));

        verticalLayout_37->addWidget(label_icon6, 0, Qt::AlignHCenter);

        label_value6 = new QLabel(tab_2);
        label_value6->setObjectName(QString::fromUtf8("label_value6"));

        verticalLayout_37->addWidget(label_value6, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_37);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        verticalLayout_38 = new QVBoxLayout();
        verticalLayout_38->setObjectName(QString::fromUtf8("verticalLayout_38"));
        label_date7 = new QLabel(tab_2);
        label_date7->setObjectName(QString::fromUtf8("label_date7"));

        verticalLayout_38->addWidget(label_date7, 0, Qt::AlignHCenter);

        label_icon7 = new QLabel(tab_2);
        label_icon7->setObjectName(QString::fromUtf8("label_icon7"));

        verticalLayout_38->addWidget(label_icon7, 0, Qt::AlignHCenter);

        label_value7 = new QLabel(tab_2);
        label_value7->setObjectName(QString::fromUtf8("label_value7"));

        verticalLayout_38->addWidget(label_value7, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout_8->addLayout(verticalLayout_38);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);

        verticalLayout_39 = new QVBoxLayout();
        verticalLayout_39->setObjectName(QString::fromUtf8("verticalLayout_39"));
        label_date8 = new QLabel(tab_2);
        label_date8->setObjectName(QString::fromUtf8("label_date8"));

        verticalLayout_39->addWidget(label_date8, 0, Qt::AlignHCenter);

        label_icon8 = new QLabel(tab_2);
        label_icon8->setObjectName(QString::fromUtf8("label_icon8"));

        verticalLayout_39->addWidget(label_icon8, 0, Qt::AlignHCenter);

        label_value8 = new QLabel(tab_2);
        label_value8->setObjectName(QString::fromUtf8("label_value8"));

        verticalLayout_39->addWidget(label_value8, 0, Qt::AlignHCenter);


        horizontalLayout_8->addLayout(verticalLayout_39);


        verticalLayout_2->addLayout(horizontalLayout_8);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout_19->addLayout(verticalLayout_2);

        horizontalSpacer_36 = new QSpacerItem(128, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_36);


        verticalLayout_3->addLayout(horizontalLayout_19);


        verticalLayout_4->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "M\303\251t\303\251o de Paris", nullptr));
        labeltitre->setText(QApplication::translate("Dialog", "M\303\251t\303\251o de Paris", nullptr));
        labelIcon->setText(QApplication::translate("Dialog", "Icon", nullptr));
        labelTemp->setText(QApplication::translate("Dialog", "Temp\303\251rature", nullptr));
        labelCiel->setText(QApplication::translate("Dialog", "Ciel", nullptr));
        labelDate->setText(QApplication::translate("Dialog", "DATE et heure", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Dialog", "Temp\303\251rature max \302\260C", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Dialog", "Temp\303\251rature min \302\260C", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Dialog", "Ciel", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Dialog", "Humidit\303\251 (%)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Dialog", "Vitesse du Vent (km/h)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Dialog", "DIrection du Vent (\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Dialog", "Pression (hPa)", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_IUV->setText(QApplication::translate("Dialog", "Image UV", nullptr));
        label_DUV->setText(QApplication::translate("Dialog", "Indice Uv", nullptr));
        label_4->setText(QApplication::translate("Dialog", "Indice UV", nullptr));
        label_IAQI->setText(QApplication::translate("Dialog", "Image AQI", nullptr));
        label_DAQI->setText(QApplication::translate("Dialog", "LABEL", nullptr));
        label_3->setText(QApplication::translate("Dialog", "AQI", nullptr));
        label_vignette1->setText(QString());
        label_vignette2->setText(QString());
        label_vignette3->setText(QString());
        label_vignette4->setText(QString());
        label_vignette5->setText(QString());
        label_vignette6->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Dialog", "Main Widget", nullptr));
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
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Dialog", "Pr\303\251vision", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMETEO_H
