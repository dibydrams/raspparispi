#include "widgetmap.h"
#include <QPainter>

WidgetMap::WidgetMap(QWidget *parent) : QWidget(parent)
{

}

void WidgetMap::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QString fileName = ":/Tmp_Map/maprougemont.png";
    QPixmap pixmap(fileName);
    p.drawPixmap(0,0,pixmap);
}
