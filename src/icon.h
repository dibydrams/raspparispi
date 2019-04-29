#ifndef ICON_H
#define ICON_H

#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

#define ICON_SIZE 128

class Icon : public QIcon
{
public:
    Icon();
    static QPixmap iconNormalOff(QPixmap img);
    static QPixmap iconNormalOn(QPixmap img);
    static QPixmap iconNormalOff2(QPixmap img);
    // Test functions under
    static QPixmap iconPushState(QPixmap img);
    static QPixmap iconNormalState2(QPixmap img);
    static QPixmap iconPushState2(QPixmap img);
private:
};

#endif // ICON_H
