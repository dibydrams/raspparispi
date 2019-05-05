#ifndef DIALOGTRADUCTION_H
#define DIALOGTRADUCTION_H

#include <QDialog>
#include <QTranslator>
#include "mainwindow.h"

namespace Ui {
class Dialogtraduction;
}

class Dialogtraduction : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogtraduction(QWidget *parent = nullptr);
    ~Dialogtraduction();


private:
    Ui::Dialogtraduction *ui;

private slots:
    void language();


public slots:
    void loadlang();



};

#endif // DIALOGTRADUCTION_H
