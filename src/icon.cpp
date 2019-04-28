#include "icon.h"

Icon::Icon()
{
}

///
/// Button Normal in Off State
/// \brief Icon::iconNormalState
/// \param QPixmap img
/// \return Pixmap
///
QPixmap Icon::iconNormalOff(QPixmap img)
{

    ///
    /// \brief Outline
    /// Outline color Gray
    ///
    QColor outcolor(188, 188, 188);

    QSize pixSize(ICON_SIZE, ICON_SIZE);

    // QPixmap background with transparant background and Pen around

    QPixmap img2(img);

    QPixmap bigPixmap = img2.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    bigPixmap.fill(Qt::transparent);

    QPainter painter(&bigPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    QPen pen(QColor(outcolor), 8, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

    // Icon in the center resized to be smaller

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(QPointF(ICON_SIZE / 6, ICON_SIZE / 6), img2.scaled(pixSize * 0.7, Qt::KeepAspectRatio, Qt::FastTransformation));

    return bigPixmap;
}


/// Button Normal in On State
/// \brief Icon::iconActiveState2
/// \param Qpixmap img
/// \return Qpixmap
///
QPixmap Icon::iconNormalOn(QPixmap img)
{

    ///
    /// \brief bgcolor shcolor
    /// Background color White
    /// Outline color Green
    ///
    QColor bgcolor(255, 255, 255);
    QColor outcolor(126, 170, 44);

    QSize pixSize(ICON_SIZE, ICON_SIZE);

    // QPixmap background with brush and Pen around

    QPixmap img2(img);

    QPixmap bigPixmap = img2.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

    QPainter painter(&bigPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setBrush(QBrush(QColor(bgcolor), Qt::SolidPattern));
    QPen pen(QColor(outcolor), 16, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

    // Icon in the center resized to be smaller

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(QPointF(ICON_SIZE / 4, ICON_SIZE / 4), img2.scaled(pixSize * 0.5, Qt::KeepAspectRatio, Qt::FastTransformation));

    return bigPixmap;
}



///
///  Original iconNormalOff with background
/// \brief Icon::test
/// \param img
/// \return QPixmap
///
QPixmap Icon::iconNormalOff2(QPixmap img)
{

    ///
    /// \brief bgcolor shcolor
    /// Background color Gray
    /// Outline color Gray
    ///
    QColor bgcolor(195, 196, 194);
    QColor outcolor(188, 188, 188);

    QSize pixSize(ICON_SIZE, ICON_SIZE);

    // QPixmap background with brush and Pen around

    QPixmap img2(img);

    QPixmap bigPixmap = img2.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    QPainter painter(&bigPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setBrush(QBrush(QColor(bgcolor), Qt::SolidPattern));
    QPen pen(QColor(outcolor), 8, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

    // Icon in the center resized to be smaller

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(QPointF(ICON_SIZE / 6, ICON_SIZE / 6), img2.scaled(pixSize * 0.7, Qt::KeepAspectRatio, Qt::FastTransformation));

    return bigPixmap;
}



QPixmap Icon::iconNormalState2(QPixmap img)
{
    QColor color(195, 196, 194);
    QColor color2(56, 84, 5);

    QSize pixSize(ICON_SIZE, ICON_SIZE);

    QPixmap img2(img);

    QPixmap bigPixmap = img2.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

    QPainter painter(&bigPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setBrush(QBrush(QColor(color), Qt::SolidPattern));
    QPen pen(QColor(126, 170, 44), 8, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setBrush(QBrush(color2));
    painter.setPen(color2);
    painter.drawPixmap(QPointF(ICON_SIZE / 6, ICON_SIZE / 6), img2.scaled(pixSize * 0.7, Qt::KeepAspectRatio, Qt::FastTransformation));

    return bigPixmap;
}



QPixmap Icon::iconPushState(QPixmap img)
{
    QColor color(89, 132, 9);
    QColor color2(56, 84, 5);

    QSize pixSize(ICON_SIZE, ICON_SIZE);

    QPixmap img2(img);

    QPixmap bigPixmap = img2.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

    QPainter painter(&bigPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setBrush(QBrush(QColor(color), Qt::SolidPattern));
    QPen pen(QColor(126, 170, 44), 8, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setBrush(QBrush(color2));
    painter.setPen(color2);
    painter.drawPixmap(QPointF(ICON_SIZE / 6, ICON_SIZE / 6), img2.scaled(pixSize * 0.7, Qt::KeepAspectRatio, Qt::FastTransformation));

    return bigPixmap;
}


QPixmap Icon::iconPushState2(QPixmap img)
{
    QColor color(89, 132, 9);
    QColor color2(56, 84, 5);
    // QSize 64
    QSize pixSize(ICON_SIZE, ICON_SIZE);

    // QSize 32
//    QSize pixSize2(ICON_SIZE_2, ICON_SIZE_2);

    QPixmap img2(img);

    QPixmap bigPixmap = img2.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

    QPainter painter(&bigPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setBrush(QBrush(QColor(126, 170, 44), Qt::SolidPattern));
//    QPen pen(QColor(89, 132, 9), 11, Qt::SolidLine);
    QPen pen(QColor(89,132,9), 15, Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 10, 10);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setBrush(QBrush(color2));
    painter.setPen(color2);
    painter.drawPixmap(QPointF(ICON_SIZE / 4, ICON_SIZE / 4), img2.scaled(pixSize * 0.5, Qt::KeepAspectRatio, Qt::FastTransformation));

    return bigPixmap;
}



//QPixmap Icon::showIcon6(const QString img, int nb)
//{
//    QColor color(255, 0, 0);
//    QSize pixSize(ICON_SIZE, ICON_SIZE);

//    QPixmap bigPixmap(img);
//    QPixmap pixmap = bigPixmap.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

//    QPainter painter(&pixmap);
//    painter.setRenderHint(QPainter::Antialiasing);

//    painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);

//    painter.setBrush(QColor(216, 216, 216));
//    painter.setPen(Qt::NoPen);
//    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

//    painter.setCompositionMode(QPainter::CompositionMode_Source);

//    QFont font("Ubuntu", 18, 1);
//    painter.setFont(font);
//    painter.setPen(color);
//    painter.drawText(20, 20, QString::number(nb));

//    return pixmap;
//}


//QPixmap Icon::showIcon7(const QString img, int nb)
//{
//    QColor color(255, 0, 0);
//    QSize pixSize(ICON_SIZE, ICON_SIZE);

//    QPixmap bigPixmap(img);
//    QPixmap pixmap = bigPixmap.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

//    QPainter painter(&pixmap);
//    painter.setRenderHint(QPainter::Antialiasing);

//    painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);

//    painter.setBrush(QColor(216, 216, 216));
//    painter.setPen(Qt::NoPen);
//    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

//    painter.setCompositionMode(QPainter::CompositionMode_Source);

//    QFont font("Ubuntu", 18, 1);
//    painter.setFont(font);
//    painter.setPen(color);
//    painter.drawText(20, 20, QString::number(nb));

//    return pixmap;
//}


///
/// \brief MainWindow::showIcon2
/// \param img
/// \return QPixmap
///
//QPixmap Icon::showIcon2(const QString img, int nb)
//{
//    QColor color;
//    QPixmap pixmap = QPixmap(img);

//    QPainter painter(&pixmap);
//    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

//    painter.setBrush(color);
//    painter.setPen(color);

//    painter.drawRect(pixmap.rect());

//    return icon;
//}


//QIcon Icon::showIcon3(const QString img, int nb)
//{
//    QColor color(255, 0, 0);

//    QPixmap pixmap = QPixmap(img);

//    QPainter painter(&pixmap);
//    painter.drawRect(QRect(10,10,100,100));
//    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

//    painter.setBrush(color);
//    painter.setPen(color);
//    QString a = QString::number(nb);
//    painter.drawText(0, 20, a);

//    painter.setPen(color);

//    painter.drawRect(pixmap.rect());

//    QIcon icon = QIcon(pixmap);

//    return icon;
//}


//QPixmap Icon::showIcon4(const QString img, int nb)
//{
//    QColor color(255, 0, 0);
//    QSize pixSize(ICON_SIZE, ICON_SIZE);
//    QSize pixSize2(ICON_SIZE_2, ICON_SIZE_2);

//    QPixmap bigPixmap(img);
//    QPixmap pixmap = bigPixmap.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

//    QPainter painter(&pixmap);
//    painter.setRenderHint(QPainter::Antialiasing);

//    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

////    painter.setBrush(Qt::gray);
////    painter.setPen(Qt::NoPen);
////    painter.opacity();
////    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

//    painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);

//    painter.setBrush(Qt::black);
//    painter.setPen(Qt::NoPen);
//    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

//    painter.setCompositionMode(QPainter::CompositionMode_Source);

////    QFont font("Ubuntu", 18, 1);
////    painter.setFont(font);
////    painter.setPen(color);
////    painter.drawText(20, 20, QString::number(nb));

//    painter.setBrush(QColor(89, 132, 9));
//    painter.setPen(Qt::NoPen);
//    painter.drawRoundedRect(QRectF((ICON_SIZE / 2), ICON_SIZE - 30,20, 20), 5, 5);

//    return pixmap;
//}


//QPixmap Icon::showIcon5(const QString img, int nb)
//{
//    QColor color(255, 0, 0);
//    QSize pixSize(ICON_SIZE, ICON_SIZE);

//    QPixmap bigPixmap(img);
//    QPixmap pixmap = bigPixmap.scaled(pixSize, Qt::KeepAspectRatio, Qt::FastTransformation);

//    QPainter painter(&pixmap);
//    painter.setRenderHint(QPainter::Antialiasing);

//    painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);

//    painter.setBrush(Qt::black);
//    painter.setPen(Qt::NoPen);
//    painter.drawRoundedRect(QRectF(0,0,ICON_SIZE, ICON_SIZE), 5, 5);

//    painter.setCompositionMode(QPainter::CompositionMode_Source);

//    QFont font("Ubuntu", 18, 1);
//    painter.setFont(font);
//    painter.setPen(color);
//    painter.drawText(20, 20, QString::number(nb));

//    return pixmap;
//}

