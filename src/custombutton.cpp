#include "custombutton.h"
#include "Abstract_API.h"
#include "mainwindow.h"

CustomButton::CustomButton(Abstract_API *ptr, QWidget *parent) : QPushButton(parent)
{
    ptrAPI = ptr;
    icon = ptrAPI->getPixmap();
    QIcon iconpix;
    iconpix.addPixmap(Icon::iconNormalOff(icon), QIcon::Normal, QIcon::Off);
    iconpix.addPixmap(Icon::iconNormalOn(icon), QIcon::Normal, QIcon::On);

    setIcon(iconpix);
    setCheckable(true);
    buttonID = ptr->getId();
//    setIconSize(QSize(100,100));
//    setFixedSize(100,100);

     connect(this, SIGNAL(clicked()), this, SLOT(ClickedManage()));
     connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index)), this, SLOT(FinishedReceived()));
}

void CustomButton::ClickedManage()
{
    qDebug()<<isChecked()<<isEnabled();
        if (this->isChecked()) {
            emit Clicked(ptrAPI); }
        else {
            emit RazSig(buttonID); }
}

void CustomButton::FinishedReceived()
{
    emit Finished();
}


