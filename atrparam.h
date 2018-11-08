#ifndef ATRPARAM_H
#define ATRPARAM_H

#include <QDialog>

namespace Ui {
class atrparam;
}

class atrparam : public QDialog
{
    Q_OBJECT

public:
    explicit atrparam(QWidget *parent = 0);
    ~atrparam();

    QString CurTip;
    Ui::atrparam *ui;
    bool status = false;

private slots:
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void recAtrText(const QString&, const QString&, const QString&, int);   //kluch-nekluch; text; tip; kolvo simvolov atributa pri dobavlenii-izmenenii

    void on_pushButton_2_clicked();

signals:
    void sendTip(const QString&, const QString&, int, const QString&, bool);
    //void netwSetAtr();
};

#endif // ATRPARAM_H
