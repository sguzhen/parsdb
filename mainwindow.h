#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "suzhnost.h"
#include "textinbox.h"
#include "textinell.h"
#include "atribut.h"
#include "lines.h"
#include "svyaz.h"
#include "paramsuzh.h"
#include "paramatr.h"

#include "login.h"
#include "ui_login.h"

#include "setsvyaz.h"
#include "ui_setsvyaz.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

#include <QLineEdit>
#include <QTextEdit>
#include <QSignalMapper>
#include <QtSql>

#include <QMessageBox>

#include <QFileDialog>

#include <QTcpSocket>

#include <QWheelEvent>

#include <QDebug>

namespace Ui {
class MainWindow;
}


class myscene : public QGraphicsScene
{
    Q_OBJECT

public:
    myscene(QGraphicsScene* parent = 0);

    //pri nazhatii na obekt polychaem i peredaem ykazatel na nego
    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        QGraphicsItem* test = (QGraphicsItem*) itemAt(event->scenePos(),QTransform());
        if ((test->data(0).toString()=="Suzhnost") || (test->data(0).toString()=="Svyaz"))
        {
            emit sendPosSuzh(test);     //peredaem suzhnost
        }
        else if (test->data(0).toString()=="Atribut")
        {
            emit sendPosAtr(test);     //peredaem atribut
        }
        else if (test->data(0).toString()=="ParamSuzhAdd")
        {
            emit sendAddAtr();  //peredaem signal dlya dobavleniya atributa cherez vsplivayuzhuyu A
        }
        else if (test->data(0).toString()=="ParamSuzhDel")
        {
            emit sendDelSuzhBis();  //peredaem signal dlya udaleniya suzhnosti pri nazhatii D
        }
        else if (test->data(0).toString()=="ParamSuzhSv")
        {
                emit sendSvSuzhBis();  //peredaem signal dlya dobavleniya svyazi pri nazhatii S
        }
        else if (test->data(0).toString()=="ParamAtrDel")
        {
            emit sendDelSuzhBis();  //peredaem signal dlya udaleniya atributa pri nazhatii D
        }
        else
        {
            emit setFlagSuzhFalse();   //flag suzhnosti izmenyyaem - dlya kontextnogo menu
        }

        QGraphicsScene::mousePressEvent(event);
    }

signals:
    void sendPosSuzh(QGraphicsItem*);
    void sendPosAtr(QGraphicsItem*);
    void setFlagSuzhFalse();
    void sendAddAtr();
    void sendDelSuzhBis();
    void sendSvSuzhBis();
};
//

//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    myscene* mscene;
    QGraphicsItem* delSuzh{};

    atribut* atr{};       //obekt atributa
    textinell * textEl{}; //tekst atributa
    setSvyaz* newSvyaz{}; //okno ystanovki svyazi
    svyaz* newS{};    //

    QGraphicsItem* rec1List{};    //
    QGraphicsItem* rec2List{};    //opredelyaem suzhnosti po ih texty dly svyazi

    QString globTextDB;
    QTextEdit* FinishText{};          //itogoviy text dly koda
    QTextEdit* FinishTextForDel;    //text pri udalenii suzhnosti pri vigruzke
    QTextEdit* FinishTextForAddAtr; //text pri dobavlenii atributov v podgruzhennuyu DB

    QWidget* setBD{};

    //knopki menu vverhu
    QPushButton* SetSuzhBut;
    QPushButton* SetAtrBut;
    //

    //combo dlya vibora db
    QComboBox* changeDB;
    //

    QMessageBox* mess;  //okno dlya raznih soobzheniy

    //int globChangeCombo;
    QString globChangeCombo;

    //Hranenie nastroek
    QSettings* settings;

    textinbox* textinpaste;

    int flagNomSuzh;        //dobavlenie +1 k imeni suzh po umolchaniyu
    int flagNomSvyaz;
    int flagItemSvyaz;
    int flagKolSv;
    int globKolShagov{};      //podschet shagov
    int nomUdalSuzh{};        //hranim nomer udalennoy suzhnosi - dly dobavleniya na scenu
    QVector <int> nomerUdalSuzh;

    bool globFlagSuzh;
    bool globFlagAtr;       //proveryaem pri nazhatii pravoy klavishey - atribut li eto
    bool globFlagSvyaz;
    bool flag1N;
    bool VigsDB;            //vigruzka c DB proverka
    bool flagNetKluchSuzh;  //flag na otsutstvie klucha u suzhnosti

    QLabel* statText;       //text statusa soedineniya
    QLabel* statNetwText;   //text statusa pri setevoy rabote
    QLabel* statCvet;       //cvet status podklucheniya

    QLabel* statTextNet;       //text statusa soedineniya
    QLabel* statCvetNet;       //cvet status podklucheniya

    QPushButton* ButViborDataBase;  //knopka dlya  utverzhdeniya vibora db

    QTcpSocket* socket{};

    QByteArray Data;
    QJsonParseError parseError{};
    QJsonDocument jsonDoc;
    QJsonObject jsonMessage;

    login* logwin{};

    virtual void wheelEvent(QWheelEvent *event);

private slots:
    void recivePosSuzh(QGraphicsItem* suzhpos);
    void recivePosAtr(QGraphicsItem* atrpos);
    void rec2Suzh(const QString& aa,const QString& bb,const QString& TextSvyazi, const QString& TextFromUSvyaz);       //slot obrabotki ystanovleniya svyazi
    void recPosSuzhSvyaz(int nom);
    void customMenuRequested(QPoint);
    void ReciveTextForDB();     //perehod k oknu nastroek podklucheniya k DB
    void EditTextForDB();       //
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_MS_SQL_Server_2_triggered();
    void reciveFlagSuzhFalse();
    void addAtr();      //DOBAVLENIE ATRIBUTA K SUZHNOSTI
    void addSvyaz();    //USTANOVKA SVYAZI
    void addSuzh();     //DOBALENIE SUZHNOSTI
    void delS();        //UDALENIE SUZHNOSTI/SVYAZI/ATRIBUTA
    void recConnect();  //SMENA CVETA - SOEDINENIE YSPESHNO
    void on_closeApp_triggered();
    void on_action_MS_SQL_Server_triggered();
    void on_vigrDB_triggered();

    void setSuzh(suzhnost*, const QString&);
    void setAtr(QGraphicsItem*, atribut*, const QString&, const QString&, const QString&, const QString&);

    //knopki menu sverhu
    void SetSuzhBut_clicked();  //knopka menu dobavleniya suzhnosti
    void SetAtrBut_clicked();
    //

    void on_action_6_triggered();

    void on_action_3_triggered();

    //void delSvyaz(QGraphicsItem* tekSv);      //udalenie svyazi
    void delSvyaz(QGraphicsItem*);      //udalenie const svyazi
    void addNewSvyaz(const QString &,const QString &);     //procedura neposredstvennogo dobavleniya svyazi v shemu

    void changeDB_currentTextChanged(const QString &arg1);

    void ButViborDataBase_on_clicked();
    void reciveTekuzhSuzh(QGraphicsItem*);
    void on_action_SaveScheme_triggered();

    void on_action_LoadScheme_triggered();

    void on_SimpleSave_triggered();
    void on_checkUpdate_triggered();

    void saveAs_or_simpleSave(const QString&); //kak sohranit

    //po seti suzhnost dobavlenie
    void netwRecSuzh(const QString&);
    //po seti atribut dobavlenie
    void netwRecAtr(QGraphicsItem*, const QString&, const QString&, const QString&, const QString&);
    //poluchenie pos suzhnosti pri seti
    void recievePosSuzhNetwork(QGraphicsItem*, double, double);

    void on_netWork_triggered();

    //disconnect socket
    void sockDisc();

    void readyReadSock();

    void on_pushButton_clicked();

    void on_addRemChat_triggered();

signals:
    void sendItem(QGraphicsItem*);   //peresilaem vibranniy item v atribut
    void sendVec(QVector <QString>); //
    void sendPosXSuzhSvyaz(int, int);
    void customContextMenuRequested(QPoint);
    void reconn(QString);   //signal na perepodkluchenie

    //po seti
    void netwSetSuzh(QString);

private:
    Ui::MainWindow *ui;
};
//

#endif // MAINWINDOW_H
