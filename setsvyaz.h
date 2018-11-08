#ifndef SETSVYAZ_H
#define SETSVYAZ_H

#include <QDialog>

#include <QDebug>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <QMessageBox>

namespace Ui {
class setSvyaz;
}

class setSvyaz : public QDialog
{
    Q_OBJECT

public:
    explicit setSvyaz(QWidget *parent = 0);
    ~setSvyaz();

    QString list1vib, list2vib; //peremennie hraneniya vibora usera iz listov
    QString FromComboVib;       //peremennaya stepeni svyazi

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);  //sobitie vibora userom iz lista 1
    void on_listWidget_2_itemClicked(QListWidgetItem *item);    //sobitie vibora userom iz lista 2

    void recVec(QVector <QString> aa);  //prinimaem ot glavnogo okna spisok tekstovih imen suzhnostey)

    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);

signals:
    void send2Suzh(const QString&, const QString&, const QString&, const QString&);  //signal otpravki glavnomy okny nazvaniy 2x suzhnostey

private:
    Ui::setSvyaz *ui;
};

#endif // SETSVYAZ_H
