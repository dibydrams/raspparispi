#include "custombutton.h"
#include "Abstract_API.h"

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
    setIconSize(QSize(100,100));
    setFixedSize(100,100);

    if (!this->isChecked()) {
        connect (this, SIGNAL(clicked()), this, SLOT(ClickedManage()));
        connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(FinishedReceived()));
    }
}

void CustomButton::ClickedManage()
{
    emit Clicked(ptrAPI);
}

void CustomButton::FinishedReceived()
{
    emit Finished();
}


