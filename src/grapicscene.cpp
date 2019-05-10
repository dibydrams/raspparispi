#include "grapicscene.h"

GrapicScene::GrapicScene()
{
    addPixmap(getMap());
    wMessage();
}

///
/// \brief CustomGraph::mousePressEvent
/// \param mouseEvent
///
void GrapicScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton)
    {
        QPoint punkt = views().first()->mapFromScene(mouseEvent->scenePos().toPoint());

        QMessageBox msgBox;
        msgBox.setWindowTitle("Sélectionner le point");
        msgBox.setText("Est ce que vous voulez valider la position ?");
//        QPushButton *validButton = msgBox.addButton(tr("Valider"), QMessageBox::ActionRole);
//        QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        qDebug() << punkt;

    }
}

///
/// \brief CustomGraph::getMap
/// \return QPixmap
///
QPixmap GrapicScene::getMap()
{
    return QPixmap("/home/guillaume/Bureau/staticimagebig.jpg");
}

///
/// \brief CustomGraph::getPin
/// \return QPixmap
///
QPixmap GrapicScene::getPin()
{
   return QPixmap("/home/guillaume/Téléchargements/pin.png");
}


///
/// \brief CustomGraph::wMessage
///
void GrapicScene::wMessage()
{
    qDebug() << width();
    qDebug() << height();
}


