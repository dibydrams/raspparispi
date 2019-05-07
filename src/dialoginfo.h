#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>

namespace Ui {
class dialoginfo;
}

class dialoginfo : public QDialog
{
    Q_OBJECT

public:
    explicit dialoginfo(QWidget *parent = nullptr);
    ~dialoginfo();

private:
    Ui::dialoginfo *ui;
};

#endif // DIALOGINFO_H
