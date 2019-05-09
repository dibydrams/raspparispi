#ifndef DIALOGTRADUCTION_H
#define DIALOGTRADUCTION_H

#include <QDialog>
#include <QTranslator>


namespace Ui {
class Dialogtraduction;
}

class Dialogtraduction : public QDialog
{
    Q_OBJECT

public:

    explicit Dialogtraduction(QWidget *parent = nullptr);
    ~Dialogtraduction();
    void flag();

private:

    Ui::Dialogtraduction *ui;
    QString m_lang;
    Dialogtraduction *l_lang;

public slots:

    void loadfr();
    void loadar();
    void loaden();


signals:

    void received(QString lang);

};

#endif // DIALOGTRADUCTION_H
