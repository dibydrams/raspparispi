#ifndef WIDGETMAP_H
#define WIDGETMAP_H

#include <QWidget>

class WidgetMap : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMap(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent *event) override;
signals:

public slots:
};

#endif // WIDGETMAP_H
