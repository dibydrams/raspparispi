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
    setIconSize(QSize(128,128));
    setFixedSize(128,128);

    // Ajout dynamique des boutons à la liste de boutons
    ptr->ButtonList << this;
}
