#include "custombutton.h"
#include "Abstract_API.h"

CustomButton::CustomButton(Abstract_API *ptr, QWidget *parent) : QPushButton(parent)
{
    ptrAPI = ptr;
    icon = ptrAPI->getPixmap();
    setIcon(QIcon(Icon::iconNormalState(icon)));
    buttonID = ptr->getId();
    setFlat(true);
    setIconSize(QSize(128,128));
    setFixedSize(128,128);


    // Ajout dynamique des boutons à la liste de boutons
    ptr->ButtonList << this;
}
