#include "uiratp.h"
#include "ui_uiratp.h"

Uiratp::Uiratp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Uiratp)
{
    ui->setupUi(this);

}

Uiratp::~Uiratp()
{
    delete ui;
}

void Uiratp::showFinishedStation(QJsonArray resultArray)
{
    for (int i = 0; i < resultArray.count(); ++i)
    {
        /*
         * foreach widget in stackedwidget
         *  if widget.name.contains( truc.trainID)
         *      add labels
         *      at good pos (center + (span * nbOfDuoLabels)
         *  else
         *      create newWidget
         *      newWidget.name = page_ + truc.trainID
         *      add labels
         *      at good pos
         */

        bool isWidgetCreated = false;
        int widgetIndex = i;
        int span = 40;
        QString lineName = resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["LineRef"].toObject().value("value").toString();

        for (int id = 0; id < ui->StationWidget->count(); ++id) {
            if (ui->StationWidget->children().at(id)->objectName().contains(lineName))
            {
                isWidgetCreated = true;
                widgetIndex = id;
//                qDebug() << "Count " << ui->StationWidget->count() << "Index of Widg" << widgetIndex << "is Created ?" << isWidgetCreated;
                break;
            }
        }

        if (!isWidgetCreated)
        {
            // Create new Widget in StackedWidget
            QWidget *newWidget = new QWidget(ui->StationWidget);
            newWidget->setObjectName("page_" + lineName);
//            qDebug() << "Widget Name" << newWidget->objectName() << endl;
            ui->StationWidget->addWidget(newWidget);

            widgetIndex = ui->StationWidget->indexOf(newWidget);

            // Create Page Follower
            QLabel *pagination = new QLabel(ui->StationWidget->widget(widgetIndex));
            pagination->setText(QString::number(widgetIndex));
            pagination->move(ui->StationWidget->geometry().right() - 50, ui->StationWidget->geometry().bottom() - 50);

            QLabel *title = new QLabel (lineName, ui->StationWidget->widget(widgetIndex));
            title->move(ui->StationWidget->widget(widgetIndex)->geometry().center().x(), 0);
        }

        ui->StationWidget->widget(widgetIndex)->hide();

        // Create Text Slot
        QLabel *labelForDest = new QLabel("Destination : ", ui->StationWidget->widget(widgetIndex));
        QLabel *labelForTime = new QLabel("Next train : ", ui->StationWidget->widget(widgetIndex));
        QLabel *labelDest = new QLabel(ui->StationWidget->widget(widgetIndex));
        QLabel *labelTime = new QLabel(ui->StationWidget->widget(widgetIndex));

        labelForDest->move(ui->StationWidget->geometry().left() + span, 20 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));
        labelForTime->move(ui->StationWidget->geometry().left() + span,  35 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));
        labelDest->move(ui->StationWidget->geometry().left() + labelForDest->geometry().width() + span, 20 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));
        labelTime->move(ui->StationWidget->geometry().left() + labelForTime->geometry().width() + span, 35 + (span * (ui->StationWidget->widget(widgetIndex)->children().count() / 4)));

        labelDest->setText(resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["DestinationName"].toArray().at(0).toObject().value("value").toString());

        // Calcul next train
        QString str_arrivalTimeUTC = resultArray[i].toObject()["MonitoredVehicleJourney"].toObject()["MonitoredCall"].toObject()["ExpectedDepartureTime"].toString();
        QString str_nowUTC = resultArray[i].toObject()["RecordedAtTime"].toString();

        QDateTime arrivalTimeUTC = QDateTime::fromString(str_arrivalTimeUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        QDateTime nowUTC = QDateTime::fromString(str_nowUTC, "yyyy-MM-ddTHH:mm:ss.zzzZ");
        arrivalTimeUTC.setTimeSpec(Qt::UTC);
        nowUTC.setTimeSpec(Qt::UTC);
        qint64 remainingTime = nowUTC.secsTo(arrivalTimeUTC);

        labelTime->setText(QDateTime::fromTime_t(remainingTime).toUTC().toString("mm") + " min");

        ui->StationWidget->widget(widgetIndex)->show();
    }
}

