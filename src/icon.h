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
//    static QIcon showIcon(const QString img, int nb);
//    static QPixmap showIcon2(const QString img, int nb);
//    static QIcon showIcon3(const QString img, int nb);
//    static QPixmap showIcon4(const QString img, int nb);
//    static QPixmap showIcon5(const QString img, int nb);
    static QPixmap iconNormalState(const QString img);
    static QPixmap iconPushState(const QString img);
    static QPixmap iconActiveState(const QString img);
    static QPixmap iconActiveState2(const QString img);
    static QPixmap iconPushState2(const QString img);
private:
};

#endif // ICON_H
