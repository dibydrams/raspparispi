#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QScrollArea>

namespace Ui {
class dialoginfo;
}

class dialoginfo : public QDialog
{
    Q_OBJECT

public:
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetDistance;
   // QTableWidget QList<QTableWidget>;
    explicit dialoginfo(QWidget *parent = nullptr);
    ~dialoginfo();

private:
    Ui::dialoginfo *ui;
};

#endif // DIALOGINFO_H
