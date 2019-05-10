#ifndef CUSTOMGRAPH_H
#define CUSTOMGRAPH_H

#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>


class GrapicScene : public QGraphicsScene
{
    Q_OBJECT
    void wMessage();
    QPixmap getPin();
public:
    CustomGraph();
    QPixmap getMap();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CUSTOMGRAPH_H
