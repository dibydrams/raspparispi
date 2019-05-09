#ifndef ICON_H
#define ICON_H

#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

#define ICON_SIZE 128
#define ICON_SIZE_MAP 96

class Icon : public QIcon
{
public:
    Icon();
    static QPixmap iconNormalOff(QPixmap img);
    static QPixmap iconNormalOn(QPixmap img);

    // Icon Map Off base
    static QPixmap iconMapOffStr(QPixmap img, QString str, QColor color);
    static QPixmap iconMapOff(QPixmap img, QColor color);

    // Icon Map Off variantes

    static QPixmap iconMapOffClose(QPixmap img, QColor color, int close);
    static QPixmap iconMapOffpix(QPixmap img, QPixmap pixbottom, QColor color);


    // Icon Test
    static QPixmap iconMapOffV1(QPixmap img, int i);
    static QPixmap iconMapOnV1(QPixmap img, int i);
    static QPixmap iconNormalOff2(QPixmap img);
    static QPixmap iconPushState(QPixmap img);
    static QPixmap iconNormalState2(QPixmap img);
    static QPixmap iconPushState2(QPixmap img);
private:
};

#endif // ICON_H
