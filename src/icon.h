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
    static QPixmap iconNormalState(QPixmap img);
    static QPixmap iconPushState(QString img);
    static QPixmap iconActiveState(QString img);
    static QPixmap iconActiveState2(QString img);
    static QPixmap iconPushState2(QString img);
private:
};

#endif // ICON_H
