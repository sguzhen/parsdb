#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mscene = new myscene(nullptr);
    ui->graphicsView->setScene(mscene);

    flagNomSuzh=0;
    flagNomSvyaz=0;
    flagItemSvyaz=0;
    flagKolSv = 0;
    flagNetKluchSuzh = false;   //flag na kluch suzhnosti obnulim

    globFlagSuzh = false;
    globFlagAtr = false;
    globFlagSvyaz = false;
    flag1N = false;
    VigsDB = false;             //flag na to zagrushena li model iz db ili net
    globChangeCombo = "tempdb"; //peremennaya imeni db k kotoroy sleduet podkluchitsya

    settings = new QSettings("settings.ini",QSettings::IniFormat);

    //tekuzhaya versiya
    settings->setValue("settings/curVer","0.00000000017");  //tekuzhaya versiya
    settings->sync();

    connect(mscene,SIGNAL(sendPosSuzh(QGraphicsItem*)),this,SLOT(recivePosSuzh(QGraphicsItem*)));
    connect(mscene,SIGNAL(sendPosAtr(QGraphicsItem*)),this,SLOT(recivePosAtr(QGraphicsItem*)));
    connect(mscene,SIGNAL(setFlagSuzhFalse()),this,SLOT(reciveFlagSuzhFalse()));
    connect(mscene,SIGNAL(sendAddAtr()),this,SLOT(addAtr()));
    connect(mscene,SIGNAL(sendDelSuzhBis()),this,SLOT(delS()));
    connect(mscene,SIGNAL(sendSvSuzhBis()),this,SLOT(addSvyaz()));

    //po seti
    connect(this,SIGNAL(netwSetSuzh(QString)), this, SLOT(netwRecSuzh(QString)));

    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuRequested(QPoint)));

    statText = new QLabel("Подключение к базе данных не установлено",this);
    statCvet = new QLabel("        ",this);
    statCvet->setStyleSheet("background-color:#ff0000");

    statTextNet = new QLabel("Подключение к сервису",this);
    statCvetNet = new QLabel("        ",this);
    statCvetNet->setStyleSheet("background-color:#ff0000");

    statNetwText = new QLabel("",this);

    changeDB = new QComboBox(nullptr);        //pod db
    //soedinyaem slot obrabotchika vibora db
    connect(changeDB,SIGNAL(currentTextChanged(QString)),this,SLOT(changeDB_currentTextChanged(QString)));
    //

    ButViborDataBase = new QPushButton("Выбрать базу данных");
        connect(ButViborDataBase,SIGNAL(clicked()),this,SLOT(ButViborDataBase_on_clicked()));
    ButViborDataBase->setEnabled(false);
    //

    //menu sverhu
    SetSuzhBut = new QPushButton(QIcon("suzh.ico"),"",ui->mainToolBar);      //knopka dob suzhnosti
    SetSuzhBut->setToolTip("Добавить сущность");
    SetSuzhBut->setEnabled(true);
    connect(SetSuzhBut,SIGNAL(clicked()),this,SLOT(SetSuzhBut_clicked()));

    SetAtrBut = new QPushButton(QIcon("atr.ico"),"",ui->mainToolBar);      //knopka dob atributa
    SetAtrBut->setToolTip("Добавить атрибут");
    SetAtrBut->setEnabled(false);
    connect(SetAtrBut,SIGNAL(clicked()),this,SLOT(SetAtrBut_clicked()));

    ui->mainToolBar->addWidget(statText);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(statCvet);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(changeDB);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ButViborDataBase);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(SetSuzhBut);
    ui->mainToolBar->addWidget(SetAtrBut);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(statTextNet);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(statCvetNet);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(statNetwText);
    //

    FinishTextForDel = new QTextEdit(nullptr);     //sozdaem fizicheski pod text
    FinishTextForAddAtr = new QTextEdit(nullptr);

    textinpaste = new textinbox();

    mess = new QMessageBox(nullptr);

    ui->graphicsView->setFrameStyle(0);
    ui->graphicsView->fitInView(0,0, ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio);

    ui->plainTextEdit->hide();
    ui->lineEdit->hide();
    ui->pushButton->hide();

    this->setWindowTitle("ПАР-С-БД");
}
//

//knopka menu dob suzhnosti
void MainWindow::SetSuzhBut_clicked()
{
    on_action_triggered();
}
//

//knopka menu dob atributa - snachala vizivaem menu atributa chtobi ustanovit nachalnie zhacheniya
void MainWindow::SetAtrBut_clicked()
{
    addAtr();
}
//

//pri navedenii na atribut mishi
void atribut::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    emit sendTekuzhAtr(this);  //sohranim ukazatel na atribute na kotoroy mish
    for (int i = 0; i<this->childItems().count();i++)
    {
        if (this->childItems().value(i)->data(0).toString() == "ParamAtrDel")
        {
            this->childItems().value(i)->setVisible(true);
        }
    }
    return QGraphicsItem::hoverEnterEvent(event);
}
//

//pri uhode mishi s atributa
void atribut::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    for (int i = 0; i<this->childItems().count();i++)
    {
        if (this->childItems().value(i)->data(0).toString() == "ParamAtrDel")
        {
            this->childItems().value(i)->setVisible(false);
        }
    }
    return QGraphicsItem::hoverLeaveEvent(event);
}


//pereschet koordinat suzhnosti
QVariant suzhnost::itemChange(GraphicsItemChange change, const QVariant &value)
{
    QStringList lineFirst;
    int xx,yy;
    if (change == ItemPositionChange && scene())
    {
        //pererisovivaem liniyu ot svyzi
        lineFirst=this->data(5).toString().split(";");
        for (int i=0;i<lineFirst.count()-1;i++)
        {
            for (int All=this->scene()->items().count();All!=-1;All--)   //perebiraem vse elementi na scene
            {
                if (this->scene()->items().value(All)->data(0).toString()=="LineSuzh") //esli obekt - liniya suzhnost
                {
                    if (this->scene()->items().value(All)->data(1).toString()==lineFirst[i])
                    {
                        lineS* temp = dynamic_cast<lineS*>( this->scene()->items().value(All));
                        xx=this->sceneBoundingRect().x()+55-temp->parentItem()->sceneBoundingRect().x();
                        yy=this->sceneBoundingRect().y()-temp->parentItem()->sceneBoundingRect().y();
                        temp->setLine(60,0,xx,yy);
                    }
                }
            }
        }
        //
    }

    return QGraphicsItem::itemChange(change, value);
}
//

//pererisovka
QVariant svyaz::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        emit sendPosSuzhSvyaz(this->data(3).toInt());   //nomer suzhnosti
        xx=this->data(1).toInt()-this->sceneBoundingRect().x()+55;
        yy=this->data(2).toInt()-this->sceneBoundingRect().y();   //X i Y
        lineS* tempL = dynamic_cast<lineS*>( this->childItems().value(0));
        tempL->setLine(60,0,xx,yy);    //pererisovivaem


        emit sendPosSuzhSvyaz(this->data(4).toInt());   //nomer suzhnosti
        xx=this->data(1).toInt()-this->sceneBoundingRect().x()+55;   //formiruem novie koordinaty
        yy=this->data(2).toInt()-this->sceneBoundingRect().y();   //X i Y
        lineS* tempL2 = dynamic_cast<lineS*>( this->childItems().value(1));
        tempL2->setLine(60,0,xx,yy);    //pererisovivaem
    }
    return QGraphicsItem::itemChange(change, value);
}
//

//pererisovka linii atribut-suzhnost
QVariant atribut::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        if (this->parentItem()->data(0).toString()=="Suzhnost")
        {
            xx=0-this->x()+30;   //formiruem novie koordinaty
            yy=0-this->y();   //X i Y
            lineS* tempL = dynamic_cast<lineS*>( this->childItems().value(0));
            tempL->setLine(30,15,xx,yy);    //pererisovivaem
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
//

//sozdanie sceni
myscene::myscene(QGraphicsScene * parent):QGraphicsScene(parent)
{
    //create
}
//

void MainWindow::wheelEvent(QWheelEvent *event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;

    if (event->delta()>0)
    {
        ui->graphicsView->scale(scaleFactor, scaleFactor);
    }
    else
    {
        ui->graphicsView->scale(1/scaleFactor, 1/scaleFactor);
    }
}

//
MainWindow::~MainWindow()
{
    //obnulyaem put
    settings->setValue("settings/pathsave","/");
    settings->sync();

    delete statText;
    delete statCvet;
    delete SetSuzhBut;
    delete SetAtrBut;
    delete FinishTextForDel;
    delete FinishTextForAddAtr;
    delete settings;
    delete mscene;
    delete ui;
}
//

//procedura dobavleniya suzhnosti
void MainWindow::setSuzh(suzhnost* Suzh, const QString& nameSuzh)
{
    //0 - imya suzhnosti
    //1 -
    //2 - IMYA KLUCHEVOGO ATRIBUTA s tipom
    //3 - nomer suzhnosti
    //4 - nomer atributa (i dlya kolichestva)
    //5 - hranenie vseh liniy ot svyzi
    //6 - nomer itema svyazi
    //7 - hranenie texta vseh atributov BEZ kluchevogo
    //8 - imy kluchevogo BEZ tipa
    //9 - imy klucha_FK tip
    //10 - tekst suzhnosti itogovoy
    //11 - CHECK vpisali kluch ili ezhe net
    //12 - CHECK est li y suzhnosti kluchevie polya: 0 - net, 1 - est
    //13 - ustanovlena li setevoy rezhim
    //14 - hranenie nazvaniya dly constr PK_ppp_ppp
    //15 - hranim tip klucha(ey) v suzhnosti

    connect(Suzh, SIGNAL(sendTekuzhSuzh(QGraphicsItem*)), this, SLOT(reciveTekuzhSuzh(QGraphicsItem*)));    //dlya opredeleniya suzhnosti pri nazhatii na bistrie dobavlenie atributa i udalenie
    connect(Suzh,SIGNAL(sendPosSuzhNetwork(QGraphicsItem*,double,double)),this,SLOT(recievePosSuzhNetwork(QGraphicsItem*,double,double)));

    auto * text = new textinbox();
    text->setData(0,"TextSuzh");
    text->setPos(-30,0);
    text->setTextWidth(120);
    QFont intext("Times", 10);
    text->setFont(intext);
    text->setHtml("<center>"+nameSuzh+"</center>");
    text->setParentItem(Suzh);

    //dobavlyaem element parametra k suzhnosti dlya bistrogo dobavleniya
    auto* ryad = new paramsuzh();
    ryad->setPos(-25,-30);
    ryad->setData(0,"ParamSuzhAdd");
    ryad->setHtml("A");
    ryad->setVisible(false);
    ryad->setParentItem(Suzh);
    //

    //dobavlyaem element parametra k suzhnosti dlya bistrogo udaleniya
    auto* bisUd = new paramsuzh();
    bisUd->setPos(75,-30);
    bisUd->setData(0,"ParamSuzhDel");
    bisUd->setHtml("D");
    bisUd->setVisible(false);
    bisUd->setParentItem(Suzh);
    //

    //dobavlyaem element parametra k suzhnosti dlya bistrogo udaleniya
    auto* bisSv = new paramsuzh();
    bisSv->setPos(25,-30);
    bisSv->setData(0,"ParamSuzhSv");
    bisSv->setHtml("S");
    bisSv->setVisible(false);
    bisSv->setParentItem(Suzh);
    //

    delSuzh = Suzh; //sohranyaem ukazatel na suzhnost sozdannuyu
    mscene->addItem(Suzh);

    //peredacha po seti
    if (ui->netWork->isChecked())
    {
        Suzh->setData(13,true);
        emit netwSetSuzh(nameSuzh);
    }
}
//

//menu - dobavit suzhnost
void MainWindow::on_action_triggered()
{
    auto* suzh = new suzhnost();
    flagNomSuzh = flagNomSuzh + 1;

    if (nomerUdalSuzh.count()==0)
    {
        suzh->setData(3,flagNomSuzh);
        suzh->setPos(150*(flagNomSuzh-1),100);
        setSuzh(suzh, "Сущность"+QString::number(flagNomSuzh));
    }
    else
    {
        suzh->setData(3,nomerUdalSuzh[0]);
        suzh->setPos(150*(nomerUdalSuzh[0]-1),100);
        setSuzh(suzh, "Сущность"+QString::number(nomerUdalSuzh[0]));
        nomerUdalSuzh.remove(0,1);
    }
}

//obrabotka i vistavlenie tekuzhey suzhnosti pri navedenii mishi - eto dlya bistrih dobavlenie atributa i udaleniya suzh
void MainWindow::reciveTekuzhSuzh(QGraphicsItem* tekuzhSuzh)
{
    delSuzh = tekuzhSuzh;
}
//

//knopka udaleniya elementov
void MainWindow::delS()
{
    bool flagSuzh = false;        //flag yavlyaetsya suzhnost glavnoy ili net
    QMessageBox::StandardButton DelOrNot = QMessageBox::question(this, "Удаление", "Вы действительно хотите удалить?", QMessageBox::Yes|QMessageBox::No);
    if (VigsDB)     //esli mi podgruzhali iz DB
    {
        if (delSuzh->data(0).toString() == "Suzhnost")
        {
            if (DelOrNot == QMessageBox::Yes)
            {
                textinpaste = dynamic_cast<textinbox*>( delSuzh->childItems().value(delSuzh->data(4).toInt()));
                FinishTextForDel->insertPlainText("DROP TABLE "+textinpaste->toPlainText()+";");                                //dopisivaem instrukciyu udaleniya suzhnosti iz db
                FinishTextForDel->insertHtml("<br>");

                QString forD;
                QStringList forDelS = delSuzh->data(6).toString().split(";");
                if (forDelS.length()>0)
                {
                    for (int i = 0; i < forDelS.length(); i++)
                    {
                        forD = forDelS[i];
                        if (forD.contains("f"))
                        {
                            mess->setText("Вы хотите удалить главную сущность");
                            mess->show();
                            flagSuzh = true;  //suzhnost glavnaya
                        }
                        else    //esli s ne s f - to suzhnost mozhno udalyat
                        {
                            for (int All=mscene->items().count();All!=-1;All--)
                            {
                                if ((mscene->items().value(All)->data(0).toString()=="Svyaz") && (mscene->items().value(All)->data(5).toString() == forD))
                                {
                                    delSvyaz(mscene->items().value(All));   //udalyaem svyaz
                                }
                            }
                        }
                    }
                }
                if (!flagSuzh)
                {
                    nomerUdalSuzh.append(delSuzh->data(3).toInt());

                    delete delSuzh;
                    flagNomSuzh = flagNomSuzh - 1;  //izmenyaem kolichestvo suzhnostey
                }
            }
        }
        else if (delSuzh->data(0).toString() == "Atribut")          //udalyaem atributi OTDELNO ot suzhnosti
        {
            if (DelOrNot == QMessageBox::Yes)
            {
                textinbox* tmp = dynamic_cast<textinbox*>( delSuzh->parentItem()->childItems().value(delSuzh->parentItem()->data(4).toInt()));
                textinbox* tmp2 = dynamic_cast<textinbox*>( delSuzh->childItems().value(1));
                FinishTextForDel->insertPlainText("ALTER TABLE "+tmp->toPlainText()+" DROP COLUMN "+tmp2->toPlainText()+";");                                //dopisivaem instrukciyu udaleniya suzhnosti iz db
                FinishTextForDel->insertHtml("<br>");

                if ((delSuzh->data(2).toString() == "key") || (delSuzh->data(2).toString() == "keyInt"))
                {
                    delSuzh->parentItem()->setData(12, delSuzh->parentItem()->data(12).toInt()-1);  //ukazivaem suzhnosti chto udalili kluchevoe pole i ego bolshe net
                }
                delSuzh->parentItem()->setData(4,delSuzh->parentItem()->data(4).toInt()-1);         //izmenyaem kol-vo atributov y suzhnosti

                delete delSuzh;
            }
        }
        else if (delSuzh->data(0).toString() == "Svyaz")    //udalenie svyazi ------------- dodelat podchitku dannih o liniyah v data(5)
        {
            if (DelOrNot == QMessageBox::Yes)
            {
                delSvyaz(delSuzh);      //procedura udaleniya svyazi
            }
        }
    }       //konec sluchaya vigruzki iz basi dannih
    else        // inache
    {
        if (delSuzh->data(0).toString() == "Suzhnost")
        {
            if (DelOrNot == QMessageBox::Yes)
            {
                QString forD;
                QStringList forDelS = delSuzh->data(6).toString().split(";");
                if (forDelS.length()>0)
                {
                    for (int i = 0; i < forDelS.length(); i++)
                    {
                        forD = forDelS[i];
                        if (forD.contains("f"))
                        {
                            mess->setText("Вы хотите удалить главную сущность");
                            mess->show();
                            flagSuzh = true;  //suzhnost glavnaya
                        }
                        else
                        {
                            for (int All=mscene->items().count();All!=-1;All--)
                            {
                                if ((mscene->items().value(All)->data(0).toString()=="Svyaz") && (mscene->items().value(All)->data(5).toString() == forD))
                                {
                                    delSvyaz(mscene->items().value(All));   //udalyaem svyaz
                                }
                            }
                        }
                    }
                }

                if (!flagSuzh)
                {
                    nomerUdalSuzh.append(delSuzh->data(3).toInt());

                    delete delSuzh;
                    SetAtrBut->setEnabled(false);
                    flagNomSuzh = flagNomSuzh - 1;  //izmenyaem kolichestvo suzhnostey
                }
            }
        }
        else if (delSuzh->data(0).toString() == "Atribut")
        {
            if (DelOrNot == QMessageBox::Yes)
            {
                delSuzh->parentItem()->setData(4,delSuzh->parentItem()->data(4).toInt()-1);         //izmenyaem kol-vo atributov y suzhnosti

                if ((delSuzh->data(2).toString()=="keyInt") || (delSuzh->data(2).toString()=="key"))    //izmenyaem kolichestvo kluchey pri udalenii
                {
                    delSuzh->parentItem()->setData(12,delSuzh->parentItem()->data(12).toInt()-1);
                }

                delete delSuzh;
            }
        }
        else if (delSuzh->data(0).toString() == "Svyaz")    //udalenie svyazi ------------- dodelat podchitku dannih o liniyah v data(5)
        {
            if (DelOrNot == QMessageBox::Yes)
            {
                delSvyaz(delSuzh);      //procedura udaleniya svyazi
            }
        }
    }
}
//

//udalenie svyazi
void MainWindow::delSvyaz(QGraphicsItem* tekSv)
{
    //qDebug()<<tekSv->data(20).toString();
    if (VigsDB)
    {
        if (tekSv->data(20).toString()!="")
        {
            FinishTextForDel->insertPlainText("ALTER TABLE "+tekSv->data(15).toString()+" DROP CONSTRAINT "+tekSv->data(20).toString());
        }
        //FinishTextForDel->insertHtml("<br>");
    }

    QString str;
    for (int All=mscene->items().count();All!=-1;All--)
    {
        if ((mscene->items().value(All)->data(0).toString()=="Suzhnost") && ((mscene->items().value(All)->data(3).toInt() == tekSv->data(3).toInt()) || (mscene->items().value(All)->data(3).toInt() == tekSv->data(4).toInt())))
        {
            str = mscene->items().value(All)->data(6).toString();

            if (mscene->items().value(All)->data(6).toString() == (tekSv->data(5).toString()+";"))
            {
                str.remove(tekSv->data(5).toString()+";");
            }
            else
            {
                str.remove(tekSv->data(5).toString()+"f;");
            }

            mscene->items().value(All)->setData(6, str);
        }
    }

    tekSv->setData(5, tekSv->data(5).toInt()-1);   //umenshaem kolvo svyazey
    delete tekSv;
}

//obrabotka peredachi pos suzhnosti po seti
void MainWindow::recievePosSuzhNetwork(QGraphicsItem* suzh, double posX, double posY)
{
    if (ui->netWork->isChecked())
    {
        if (!socket->isOpen())
        {
            socket = new QTcpSocket(this);
                connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
            socket->connectToHost("194.87.103.91",7777);
        }
        else
        {
            if (socket->waitForConnected(1000))
            {
                socket->write(QByteArray(QString(R"({"action":"changePosSuzh","nameSuzh":")"+(dynamic_cast<textinbox*>( suzh->childItems().value(suzh->data(4).toInt())))->toPlainText()+R"(","posX":)"+QString::number(posX)+",\"posY\":"+QString::number(posY)+"}").toUtf8().data()));
                socket->waitForBytesWritten(1000);
                socket->flush();
            }
        }
    }
    else
    {
        qDebug()<<"Ne ustanovlen setevoy rezhim";
    }
}
//

//obrabotka nazhatiya na suzhnost - poluchenie obekta s kotorim rabotaem
void MainWindow::recivePosSuzh(QGraphicsItem* suzhpos)
{
    delSuzh = suzhpos;
    SetAtrBut->setEnabled(true);        //vistavlyaem aktivnoy knopku iz menu sverhu dob atributa
    globFlagSuzh = true;
    globFlagAtr = false;
}
//

//obrabotka nazhatiya na atribut - poluchenie obekta s kotorim rabotaem
void MainWindow::recivePosAtr(QGraphicsItem* atrpos)
{
    delSuzh = atrpos;
    SetAtrBut->setEnabled(false);        //vistavlyaem NEaktivnoy knopku iz menu sverhu dob atributa
    globFlagAtr = true;
}
//

//flag suzhnosti - dlya kontextnogo
void MainWindow::reciveFlagSuzhFalse()
{
    globFlagSuzh = false;
    SetAtrBut->setEnabled(false);        //vistavlyaem NEaktivnoy knopku iz menu sverhu dob atributa
}

//menu - sformirovat kod - vizova okna s sformirovannim textom po figuram
void MainWindow::on_action_2_triggered()
{
    setBD = new QWidget(nullptr);
    setBD->setGeometry(100,100,800,300);

    FinishText = new QTextEdit(setBD);

    auto* VerticalRov = new QVBoxLayout;

    QPushButton* SendTextToDB = new QPushButton("Сформировать таблицы в БД");
    connect(SendTextToDB,SIGNAL(clicked()),this,SLOT(ReciveTextForDB()));

    VerticalRov->addWidget(FinishText);
    VerticalRov->addWidget(SendTextToDB);

    //opisivaem kluchevie i NEklyuchevie polya
    for (int All=mscene->items().count();All!=-1;All--)
    {
        if (mscene->items().value(All)->data(0).toString()=="Suzhnost")
        {
            mscene->items().value(All)->setData(2, "");
            mscene->items().value(All)->setData(7, "");
            mscene->items().value(All)->setData(8, "");
            mscene->items().value(All)->setData(10, "");
            mscene->items().value(All)->setData(11, "0");
            mscene->items().value(All)->setData(12, 0);

            QList<QGraphicsItem *> itm = mscene->items().value(All)->childItems();
            for (int i=0;i<itm.size();i++)
            {
                if (itm.value(i)->data(0).toString()=="Atribut")        //esli rebenok atribut - to
                {
                    if (itm.value(i)->data(2).toString()=="nokey")
                    {
                        mscene->items().value(All)->setData(7,mscene->items().value(All)->data(7).toString()+itm.value(i)->data(3).toString()+",");
                    }
                    else
                    {
                        mscene->items().value(All)->setData(12,mscene->items().value(All)->data(12).toInt()+1); //nashli kluch - yvelichili schetchik kluchey

                        if (mscene->items().value(All)->data(12).toInt()==1) //esli kluch odin to
                        {
                            mscene->items().value(All)->setData(2,itm.value(i)->data(3).toString());
                            mscene->items().value(All)->setData(8,itm.value(i)->data(4).toString());    //kluch
                            mscene->items().value(All)->setData(9,itm.value(i)->data(5).toString());
                            mscene->items().value(All)->setData(14,itm.value(i)->data(4).toString());   //dlya PK_
                        }
                        else //esli kluzhey mnogo - sostavnoy, to
                        {
                            //esli mi chto to zapisali v imya kluch atr+tip to
                            if (mscene->items().value(All)->data(2).toString()!="")
                            {
                                mscene->items().value(All)->setData(2,mscene->items().value(All)->data(2).toString()+","+itm.value(i)->data(3).toString());    //imy kluch atr + tip
                            }
                            else    //esli tam ezhe nichego ne zapisivali to
                            {
                                mscene->items().value(All)->setData(2,itm.value(i)->data(3).toString()+" NOT NULL CONSTRAINT");    //imy kluch atr + tip
                            }
                            mscene->items().value(All)->setData(8,mscene->items().value(All)->data(8).toString()+","+itm.value(i)->data(4).toString());    //kluch
                            mscene->items().value(All)->setData(9,itm.value(i)->data(5).toString());
                            mscene->items().value(All)->setData(14,mscene->items().value(All)->data(14).toString()+"_"+itm.value(i)->data(4).toString());
                        }
                    }
                }
            }
        }
    }

    //
    QVector <QString> forBezKluch;
    //opisivaem kluchevie polya pri svyazi All - svyaz, All2 - suzh
    for (int All=mscene->items().count();All!=-1;All--)
    {
        if (mscene->items().value(All)->data(0).toString()=="Svyaz")
        {
            for (int All2=mscene->items().count();All2!=-1;All2--)
            {
                if ((mscene->items().value(All2)->data(0).toString()=="Suzhnost") && (mscene->items().value(All2)->data(3).toString()==mscene->items().value(All)->data(3).toString()))
                {
                    mscene->items().value(All)->setData(10, mscene->items().value(All2)->data(7).toString());   //atributi pervoy s
                    mscene->items().value(All)->setData(18, mscene->items().value(All2)->data(9).toString());   //key pervoy _FK - dlya 1:N

                    //esli kluchevoe pole voobzhe est
                    if (mscene->items().value(All)->data(18).toString()!="")
                    {
                        if (mscene->items().value(All2)->data(12).toInt()==1)    //esli etot kluch odin to
                        {
                            mscene->items().value(All)->setData(12, mscene->items().value(All2)->data(2).toString()+" NOT NULL CONSTRAINT PK_"+mscene->items().value(All2)->data(14).toString()+" PRIMARY KEY("+mscene->items().value(All2)->data(8).toString()+")");   //key pervoy
                        }
                        else        //esli kluchey mnogo - sostavnoy, to
                        {
                            mscene->items().value(All)->setData(12, mscene->items().value(All2)->data(2).toString()+" NOT NULL CONSTRAINT PK_"+mscene->items().value(All2)->data(14).toString()+" PRIMARY KEY("+mscene->items().value(All2)->data(8).toString()+")");   //key pervoy
                        }
                    }
                    else    //klucha u suzhnosti net voobzhe
                    {
                        mess->setText("У вас отсутствует первичный ключ у сущности!");  //UKAZAT U KAKOY!!!!!!!!
                        mess->show();
                        flagNetKluchSuzh = true; //flag chto net klucha
                    }

                    textinpaste = dynamic_cast<textinbox*>( mscene->items().value(All2)->childItems().value(mscene->items().value(All2)->data(4).toInt()));
                    mscene->items().value(All)->setData(14, textinpaste->toPlainText());  //imya pervoy sizhnosti

                    mscene->items().value(All)->setData(16, mscene->items().value(All2)->data(8).toString());   //imya klucha BEZ tipa
                    mscene->items().value(All)->setData(17, mscene->items().value(All2)->data(8).toString());   //imya klucha vtorostepennoy suzhnosti BEZ tipa

                    mscene->items().value(All2)->setData(10,"CREATE TABLE "+mscene->items().value(All)->data(14).toString()+"("+mscene->items().value(All)->data(12).toString()+","+mscene->items().value(All2)->data(7).toString());

                    forBezKluch << mscene->items().value(All)->data(14).toString(); //sohranim imya suzhnosti dlya otobrazheniya v soobzhenii
                }
                else if ((mscene->items().value(All2)->data(0).toString()=="Suzhnost") && (mscene->items().value(All2)->data(3).toString()==mscene->items().value(All)->data(4).toString()))
                {
                    mscene->items().value(All)->setData(11, mscene->items().value(All2)->data(7).toString());   //atributa vtoroy s

                    //esli kluch voobzhe est
                    if (mscene->items().value(All2)->data(8).toString()!="")
                    {
                        mscene->items().value(All)->setData(13, mscene->items().value(All2)->data(2).toString()+" NOT NULL CONSTRAINT"+" PK_"+mscene->items().value(All2)->data(14).toString()+" PRIMARY KEY("+mscene->items().value(All2)->data(8).toString()+")");   //key vtoroy
                    }
                    else    //klucha u suzh net voobzhe
                    {
                        mess->setText("У вас отсутствует первичный ключ у сущности!");  //UKAZAT U KAKOY!!!!!!!!
                        mess->show();
                        flagNetKluchSuzh = true; //flag chto net klucha
                    }

                    textinpaste = dynamic_cast<textinbox*>( mscene->items().value(All2)->childItems().value(mscene->items().value(All2)->data(4).toInt()));
                    mscene->items().value(All)->setData(15, textinpaste->toPlainText());  //imya vtoroy suzhnosti

                    mscene->items().value(All)->setData(17, mscene->items().value(All2)->data(8).toString());   //imya klucha BEZ tipa

                    mscene->items().value(All2)->setData(10,"CREATE TABLE "+mscene->items().value(All)->data(15).toString()+"("+mscene->items().value(All)->data(13).toString()+","+mscene->items().value(All2)->data(7).toString());

                    forBezKluch << mscene->items().value(All)->data(15).toString(); //sohranim imya suzhnosti dlya otobrazheniya v soobzhenii
                }
            }
        }
    }


    //formiruem i sohranyaem text vivoda
    QStringList temp;
    QString t;
    QString peremDlyaStolb;    //peremennaya dly hraneniya stroki s atributami kluchevimi BEZ tipa
    for (int All=mscene->items().count();All!=-1;All--)
    {
        if (mscene->items().value(All)->data(0).toString()=="Suzhnost")
        {
            temp = mscene->items().value(All)->data(6).toString().split(";");

            if (temp.length()!=1)   //esli svyaz y suzhnosti est, to
            {
                for (int i=0; i<temp.length()-1; i++)
                {
                    t=temp[i];
                    if (t.contains("f"))        //esli glavnaya
                    {
                        t.remove(1,t.length());
                    }
                    else if (!t.contains("f"))        //esli BEZ f - suzhnost NE glavnaya
                    {
                        for (int All2=mscene->items().count();All2!=-1;All2--)
                        {
                            if ((mscene->items().value(All2)->data(0).toString()=="Svyaz") && (mscene->items().value(All2)->data(5).toString()==t))
                            {
                                if (mscene->items().value(All2)->data(7).toString()=="1:1")
                                {
                                    for (int All3=mscene->items().count();All3!=-1;All3--)
                                    {
                                        if ((mscene->items().value(All3)->data(0).toString()=="Suzhnost") && (mscene->items().value(All3)->data(3).toString()==mscene->items().value(All2)->data(4).toString()))    //esli suzhnost NE glavnaya
                                        {
                                            //qDebug()<<"111"<<mscene->items().value(All2)->data(17).toString();
                                            mscene->items().value(All3)->setData(10, mscene->items().value(All3)->data(10).toString()+" CONSTRAINT "+"FK_"+mscene->items().value(All2)->data(15).toString()+"_"+mscene->items().value(All2)->data(14).toString()+" FOREIGN KEY ("+mscene->items().value(All2)->data(17).toString()+") "+"REFERENCES "+mscene->items().value(All2)->data(14).toString()+"("+mscene->items().value(All2)->data(16).toString()+"),");
                                            mscene->items().value(All2)->setData(20,"FK_"+mscene->items().value(All2)->data(15).toString()+"_"+mscene->items().value(All2)->data(14).toString());
                                        }
                                    }
                                }
                                else if (mscene->items().value(All2)->data(7).toString()=="1:N")
                                {
                                    for (int All3=mscene->items().count();All3!=-1;All3--)
                                    {
                                        if ((mscene->items().value(All3)->data(0).toString()=="Suzhnost") && (mscene->items().value(All3)->data(3).toString()==mscene->items().value(All2)->data(4).toString()))    //esli suzhnost NE glavnaya i kluch ezhe ne opisan
                                        {
                                            if (!flag1N)  //esli atribut kluchevoy
                                            {
                                                mscene->items().value(All3)->setData(10,mscene->items().value(All3)->data(10).toString()+mscene->items().value(All2)->data(18).toString()+" CONSTRAINT "+"FK_"+mscene->items().value(All2)->data(15).toString()+"_"+mscene->items().value(All2)->data(14).toString()+" FOREIGN KEY ("+mscene->items().value(All2)->data(16).toString()+"_FK"+") "+"REFERENCES "+mscene->items().value(All2)->data(14).toString()+"("+mscene->items().value(All2)->data(16).toString()+"),");
                                                mscene->items().value(All2)->setData(20,"FK_"+mscene->items().value(All2)->data(15).toString()+"_"+mscene->items().value(All2)->data(14).toString());
                                            }
                                            else
                                            {
                                                mscene->items().value(All3)->setData(10,mscene->items().value(All3)->data(10).toString()+" CONSTRAINT "+"FK_"+mscene->items().value(All2)->data(15).toString()+"_"+mscene->items().value(All2)->data(14).toString()+" FOREIGN KEY ("+mscene->items().value(All2)->data(9).toString()+") "+"REFERENCES "+mscene->items().value(All2)->data(14).toString()+"("+mscene->items().value(All2)->data(16).toString()+"),");
                                                mscene->items().value(All2)->setData(20,"FK_"+mscene->items().value(All2)->data(15).toString()+"_"+mscene->items().value(All2)->data(14).toString());
                                                flag1N = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else    //esli svyazi y suzhnosti net
            {
                textinpaste = dynamic_cast<textinbox*>( mscene->items().value(All)->childItems().value(mscene->items().value(All)->data(4).toInt()));
                mscene->items().value(All)->setData(10, "CREATE TABLE "+textinpaste->toPlainText()+"(");


                peremDlyaStolb = "";
                QList<QGraphicsItem *> itm = mscene->items().value(All)->childItems();
                for (int i=0;i<itm.size();i++)
                {
                    if (itm.value(i)->data(0).toString()=="Atribut")        //esli rebenok atribut - to
                    {
                        if (itm.value(i)->data(2).toString()=="nokey")
                        {
                            mscene->items().value(All)->setData(10,mscene->items().value(All)->data(10).toString()+itm.value(i)->data(3).toString()+",");
                        }
                        else
                        {
                            mscene->items().value(All)->setData(10,mscene->items().value(All)->data(10).toString()+itm.value(i)->data(3).toString()+",");
                            peremDlyaStolb = peremDlyaStolb + itm.value(i)->data(4).toString()+",";     //spisok atributov sostavnogo klucha
                        }
                    }
                }

                if (mscene->items().value(All)->data(12).toInt()==0)    //esli u suzh bez svyazi net klucha, to flag otmechaem
                {
                    forBezKluch << textinpaste->toPlainText();  //hranim imya suzhnosti BEZ klucha
                    flagNetKluchSuzh = true;
                }

                peremDlyaStolb.remove(peremDlyaStolb.length()-1,1); //ubiraem poslebnuyu , iz stroki
                mscene->items().value(All)->setData(10, mscene->items().value(All)->data(10).toString()+" PRIMARY KEY(" + peremDlyaStolb + ")");    //vistavlyaem sostavnoy kluch
            }
        }
    }

    //zapolnyaem okni vivoda tekstom
    QString total;  //peremen dlya itogovoy stroki
    if (!flagNetKluchSuzh)
    {
        for (int All=mscene->items().count();All!=-1;All--)
        {
            if (mscene->items().value(All)->data(0).toString()=="Suzhnost")
            {
                total = mscene->items().value(All)->data(10).toString();

                //ubiraem poslednuyu zapyatuyu
                while (total[total.length()-1]==',')
                {
                    total.remove(total.length()-1, 1);
                }
                //

                //dopisivaem skobky v konec
                total.append(");");
                //

                FinishText->insertPlainText(total);
                FinishText->insertHtml("<br>");
            }
        }
    }
    else    //esli flag true - kluchey y suzh net
    {
        SendTextToDB->setEnabled(false);    //blokiruem knopku
        FinishText->clear();    //ochizhaem okno vivoda
        FinishText->insertHtml("У данных сущностей отсутствует первичный ключ: <br>");

        //vivedem polzovatelyu dannie po tomy kakie suzhnosti BEZ pervichnogo klucha
        for (const auto & i : forBezKluch)
        {
            FinishText->insertHtml(i + "<br>");
        }

        flagNetKluchSuzh = false;   //vozvrazhaem kluch k nazhalnomy
    }

    //vivodim
    globTextDB = FinishText->toPlainText();
    if (FinishTextForDel->toPlainText() != "")
    {
        FinishText->insertHtml(FinishTextForDel->toPlainText());
        globTextDB.append(FinishTextForDel->toPlainText());

        if ((globTextDB[0]==")") && (globTextDB[1]==";"))
        {
            globTextDB.remove(0,3);
        }
        //qDebug()<<"glob"<<globTextDB;
    }
    setBD->setLayout(VerticalRov);
    setBD->show();
}

//dobavlenie atribut suzhnosti
void MainWindow::addAtr()
{
    //0 - sistemnoe imya atributa - Atribut
    //1 - tip atributa
    //2 - key or nokey
    //3 - imy atributa s tipom dannih
    //4 - imy atributa BEZ podcherkivaniya
    //5 - imy atr_FK tip - dlya 1:N
    //6 - imya suzhnosti dannogo atributa
    //7 - esli eto tip dannih s vozmozhnostiyu kolichestva - to hranim kolvo simvolov ili razmer
    atr = new atribut();
        connect(atr, SIGNAL(sendTekuzhAtr(QGraphicsItem*)), this, SLOT(reciveTekuzhSuzh(QGraphicsItem*)));    //dlya opredeleniya atributa pri nazhatii na bistrie dobavlenie atributa i udalenie
    if (ui->netWork->isChecked())
    {
        connect(atr,SIGNAL(netwSetAtr(QGraphicsItem*,QString,QString,QString,QString)), this, SLOT(netwRecAtr(QGraphicsItem*,QString,QString,QString,QString)));
    }
    atr->aparam = new atrparam();
        //sozdaem signal-slot dlya obrabotki dvoinogo nazhatiya na atribut
        connect(atr->aparam,SIGNAL(sendTip(QString,QString,int,QString,bool)),atr,SLOT(recTip(QString,QString,int,QString,bool)));
    atr->aparam->setWindowTitle("Добавление атрибута");
    atr->aparam->setModal(true);
    atr->aparam->show();
    //

    //tekst vnutri atributa
    textEl = new textinell();
    textEl->setData(0,"TextAtr");
    textEl->setPos(-30,0);
    textEl->setTextWidth(120);
    QFont intext("Times", 10);
    textEl->setFont(intext);
    textEl->setHtml("<center>Atribut</center>");
    textEl->setParentItem(atr);
    //

    //perenesem vbok
    atr->moveBy(-200*sin(1.5/2 * delSuzh->data(4).toInt()),-200*cos(1.5/2 * delSuzh->data(4).toInt()));
    //

    //
    auto* LT = new lineS();
    //0 - imy dlya obekta
    //1 - xx koordinata
    //2 - yy koordinata
    LT->setData(0,"LineAtr");
    LT->setData(1, 0 - atr->x() + 30);
    LT->setData(2, 0 - atr->y());
    LT->setLine(30,15,LT->data(1).toInt(),LT->data(2).toInt());
    LT->setParentItem(atr);
    //

    //dobavlyaem element parametra k atributu dlya bistrogo udaleniya
    auto* ryad = new paramatr();
    ryad->setPos(20,-30);
    ryad->setData(0,"ParamAtrDel");
    ryad->setHtml("D");
    ryad->setVisible(false);
    ryad->setParentItem(atr);
    //

    //zavisimost ot suzhnosti
    atr->setParentItem(delSuzh);
    //

    //sohranim imya suzhnosti v atribute
    textinpaste = dynamic_cast<textinbox*>( atr->parentItem()->childItems().value(atr->parentItem()->data(4).toInt()+1));
    atr->setData(6,textinpaste->toPlainText());
    //

    //uvelichivaem schetchik kolva atributov u dannoy suzhnosti
    delSuzh->setData(4,delSuzh->data(4).toInt()+1);
    //
}

//nazhatie dvoinoe na atribute
void atribut::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    aparam = new atrparam();
    aparam->setWindowTitle("Добавление атрибута");

        connect(aparam,SIGNAL(sendTip(QString,QString,int,QString,bool)),this,SLOT(recTip(QString,QString,int,QString,bool)));

    //peredaem kluch-nekluch; imy; tip, kolvo simvolov atributa v okno dlya redaktirovaniya
        connect(this,SIGNAL(sendAtrText(QString,QString,QString,int)),aparam,SLOT(recAtrText(QString,QString,QString,int)));
        emit sendAtrText(this->data(2).toString(),this->data(4).toString(), this->data(1).toString(), this->data(7).toInt()); //peredaem kluch/nekluch; imya; tip; kolvo simvolov atributa
    //

    aparam->setModal(true); //vistavlyaem chto okno prioritetnoe
    aparam->show();

    QGraphicsItem::mouseDoubleClickEvent(event);
}
//

//odinochnoe nazhatie - otpuskanie
void suzhnost::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    //qDebug()<<event->pos().x();
    if (this->data(13).toBool())
    {
        emit sendPosSuzhNetwork((QGraphicsItem*)this, event->scenePos().x(), event->scenePos().y());
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

//dvoinoe na suzhnosti
void suzhnost::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    sparam = new suzhparam();
    sparam->setWindowTitle("Редактор сущности");
        connect(sparam,SIGNAL(sendNameSuzh(QString)),this,SLOT(recNameSuzh(QString)));

    //imya suzhnosti peredaem v okno redaktirovaniya imeni suzhnosti
        connect(this,SIGNAL(sendSuzhText(QString)),sparam,SLOT(recSuzhText(QString)));
        emit sendSuzhText((dynamic_cast<textinbox*>( this->childItems().value(this->data(4).toInt())))->toPlainText());
        disconnect(this,SIGNAL(sendSuzhText(const QString&)),sparam,SLOT(recSuzhText(const QString&)));
    //

    sparam->setModal(true); //vistavlyaem chto okno prioritetnoe
    sparam->show();
    QGraphicsItem::mouseDoubleClickEvent(event);
}
//

//poluchenie imeni suzhnosti
void suzhnost::recNameSuzh(const QString& nameSuzh)
{
    (dynamic_cast<textinbox*>( this->childItems().value(this->data(4).toInt())))->setHtml("<p align = center>"+nameSuzh+"</p>");
}

//tip dannix atributa
void atribut::recTip(const QString& aa, const QString& bb, int KolSimv, const QString& nameAtr, bool st)
{
    if (nameAtr != "")      //esli nazvanie NE pustoe
    {
        (dynamic_cast<textinell*>( this->childItems().value(1)))->setHtml("<center>"+nameAtr+"<center>");

        if (bb=="key")      //esli vistavlen chto atribut - kluch
        {
            this->setData(2,"key");
            if ((aa=="varchar") || (aa=="char"))
            {
                this->setData(3,nameAtr+" "+aa+"("+QString::number(KolSimv)+")");
                this->setData(5,nameAtr+"_FK "+aa+"("+QString::number(KolSimv)+")");
                this->setData(7,KolSimv);   //hranim kolvo simvolov
                this->parentItem()->setData(15, aa+"("+QString::number(KolSimv)+")");   //sohranyaem v suzhnosti kluch
            }
            else
            {
                this->setData(3,nameAtr+" "+aa);
                this->parentItem()->setData(15, aa);   //sohranyaem v suzhnosti kluch
            }
            this->setData(4,nameAtr);
            if (!st)    //esli status bil ne kluchevim do etogo - to uvelich
            {
                this->parentItem()->setData(12, this->parentItem()->data(12).toInt()+1); //ustanavlivaem flag chto kluch est u suzhnosti
            }
            (dynamic_cast<textinell*>( this->childItems().value(1)))->setHtml("<center><u>"+(dynamic_cast<textinell*>( this->childItems().value(1)))->toPlainText()+"</u></center>");
        }
        else if (bb=="keyInt")
        {
            this->setData(2,"keyInt");
            this->setData(3,nameAtr+" "+aa);
            this->setData(4,nameAtr);
            this->setData(5,nameAtr+"_FK "+aa);
            if (!st)    //esli status bil ne kluchevim do etogo - to uvelich
            {
                this->parentItem()->setData(12, this->parentItem()->data(12).toInt()+1); //ustanavlivaem flag chto kluch est u suzhnosti
            }
            this->parentItem()->setData(15, aa);   //sohranyaem v suzhnosti kluch
            (dynamic_cast<textinell*>( this->childItems().value(1)))->setHtml("<center><u>"+(dynamic_cast<textinell*>( this->childItems().value(1)))->toPlainText()+"</u></center>");
        }
        else    //esli atribut ne kluch
        {
            this->setData(2,"nokey");

            if ((aa=="varchar") || (aa=="char"))
            {
                this->setData(3,nameAtr+" "+aa+"("+QString::number(KolSimv)+")");
                this->setData(7,KolSimv);   //hranim kolvo simvolov
            }
            else
            {
                this->setData(3,nameAtr+" "+aa);
            }

            this->setData(4,nameAtr);
            if (st)
            {
                this->parentItem()->setData(12, this->parentItem()->data(12).toInt()-1); //ustanavlivaem flag chto klucha u suzhnosti net
            }
        }
        this->setData(1,aa);    //sohranyaem vvedenniy tip atributa
    }
    else    //esli nazvanie pustoe
    {
        this->parentItem()->setData(4, this->parentItem()->data(4).toInt()-1);   //umenshaem kolvo atributov
        delete this;        //udalyaem pustoy atribut
    }

    emit netwSetAtr(this->parentItem(), this->data(4).toString(), this->data(2).toString(), this->data(1).toString(), this->data(7).toString());
}
//

//knopka okna ustanovki svyazi
void MainWindow::addSvyaz()
{
    bool testKluchSuzh = false;
    for (int All=mscene->items().count();All!=-1;All--)   //perebiraem vse elementi na scene
    {
        if (mscene->items().value(All)->data(0).toString()=="Suzhnost")
        {
            if ((mscene->items().value(All)->data(12).toInt()==0) || (mscene->items().value(All)->data(12).toInt()==-1))
            {
                testKluchSuzh = true;
            }
        }
    }

    if ((flagNomSuzh>=1) && (!testKluchSuzh))
    {
        QVector <QString>   stringVec;
        newSvyaz = new setSvyaz();
        connect(this,SIGNAL(sendVec(QVector<QString>)),newSvyaz,SLOT(recVec(QVector<QString>)));
        connect(newSvyaz,SIGNAL(send2Suzh(QString,QString,QString,QString)),this,SLOT(rec2Suzh(QString,QString,QString,QString)));

        for (int All=mscene->items().count();All!=-1;All--)   //perebiraem vse elementi na scene
        {
            if (mscene->items().value(All)->data(0).toString()=="TextSuzh")
            {
                textinpaste = dynamic_cast<textinbox*>( mscene->items().value(All));
                stringVec.append(textinpaste->toPlainText());
            }
        }

        emit sendVec(stringVec);
        newSvyaz->show();

        disconnect(this,SIGNAL(sendVec(QVector <QString>)),newSvyaz,SLOT(recVec(QVector <QString>)));
    }
    else
    {
        if (testKluchSuzh)
        {
            mess->setText("Связь невозможно установить так как у одной из сущностей нет первичного ключа");
        }
        mess->show();
    }
}
//

//obrabotka poluchennih ot okna imen 2x suzhnostey dlya svyzi
void MainWindow::rec2Suzh(const QString& aa,const QString& bb, const QString& TextSvyazi, const QString& TextFromUSvyaz)
{
    for (int All=mscene->items().count();All!=-1;All--)   //perebiraem vse elementi na scene
    {
        if (mscene->items().value(All)->data(0).toString()=="TextSuzh")
        {
            textinpaste = dynamic_cast<textinbox*>( mscene->items().value(All));

            if (aa==bb)
            {
                rec1List = textinpaste->parentItem();
                rec2List = rec1List;
            }
            else
            {
                if (textinpaste->toPlainText() == aa)
                {
                    rec1List = textinpaste->parentItem();
                }
                else if (textinpaste->toPlainText() == bb)
                {
                    rec2List = textinpaste->parentItem();
                }
            }
        }
    }

    //esli kluch est u suzhnostey i u pervoi i u vtoroy - to delaem svyaz
    if ((rec1List->data(12).toInt() >= 1) && (rec2List->data(12).toInt() >=1) )
    {
        if (TextSvyazi == "1:1")    //esli svyaz 1:1
        {
            if (rec1List->data(12).toInt() == rec2List->data(12).toInt())   //proveryaem chtobi kolichestvo kluchevih poley odnoy suzhnosti ravno kolvo drugoy
            {
                if (rec1List->data(15).toString() == rec2List->data(15).toString())
                {
                    addNewSvyaz(TextSvyazi, TextFromUSvyaz);    //dobavlyaem svyaz
                }
                else
                {
                    mess->setText("Вы пытаетесь объединить ключевые атрибуты с разными типами данных");
                    mess->show();
                }
            }
            else
            {
                mess->setText("У соединяемых сущностей разное количество ключевых полей");
                mess->show();
            }
        }
        else    //to prosto obedinyaem bez proverok
        {
            addNewSvyaz("1:N",TextFromUSvyaz);  //dobavlyaem svyaz
        }
    }
    else    //esli klucha hotya bi u odnoy suzhnosti net - to net i obedineniya
    {
        mess->setText("У одной (или) обеих сущностей нет ключа");
        mess->show();
    }
}
//

//procedura neposredstvennogo dobavleniya svyazi v shemu
void MainWindow::addNewSvyaz(const QString& textS, const QString& textUs)
{
    //0 - imya
    //1 - koordinata X novaya suzhnosti
    //2 - koordinata Y novaya suzhnosti
    //3 - nomer suzhnosti pervoy v soedinenii na scene
    //4 - nomer suzhnosti vtoroy v soedinenii na scene
    //5 - nomer svyazi
    //6 - nomer: suzhnost-svyaz   dlya proverki
    //7 - nazvanie svyazi - 1:1 ili 1:N
    //8 - kolichestvo elementov
    //9 - atribut iz vigruzki DB, NE yavlyaetsya kluchem
    //10 - text pervoy suzhnosti soedineniya
    //11 - text vtoroy suzhnosti soedineniya
    //12 - key pervoy s tipom
    //13 - key vtoroy s tipom
    //14 - imya pervoy suzhnosti
    //15 - imya vtoroy suzhnosti
    //16 - key pervoy BEZ tipa
    //17 - key vtoroy BEZ tipa
    //18 - key pervoy s _FK s tipom BEZ PRIMARY KEY
    //19 - podpis pod svyazyu
    //20 - polniy tekst FK_suzh1_suzh2


    newS = new svyaz();
    newS->setData(0,"Svyaz");
    newS->setData(3,rec1List->data(3).toInt());
    newS->setData(4,rec2List->data(3).toInt());
    newS->setData(5,++flagItemSvyaz);
    newS->setData(7,textS);
    mscene->addItem(newS);
    //

    //
    auto * tt = new textinbox();
    tt->setData(0,"TextSvyaz");
    tt->setPos(0,-10);
    tt->setTextWidth(120);
    tt->setHtml("<center><font size=4><b>"+QString(textS)+"</b></font></center>");
    newS->setData(8,++flagKolSv);
    //

    //text pod svyazyu
    auto * textUsvyaz = new textinbox();
    textUsvyaz->setData(0,"TextUSvyaz");
    textUsvyaz->setTextWidth(120);
    textUsvyaz->setHtml("<center>"+QString(textUs)+"</center>");
    textUsvyaz->moveBy(0,50);
    newS->setData(8,++flagKolSv);
    newS->setData(19,textUs);      //hranim podpis pod svyazyu
    //

    connect(newS,SIGNAL(sendPosSuzhSvyaz(int)),this,SLOT(recPosSuzhSvyaz(int)));
    connect(this,SIGNAL(sendPosXSuzhSvyaz(int,int)),newS,SLOT(recPosXSuzhSvyaz(int,int)));

    //
    auto* LT = new lineS();
    //0 - imy dlya obekta
    //1 - nom svyaz
    LT->setData(0,"LineSuzh");
    LT->setData(1,++flagNomSvyaz);
    LT->setLine(60,0,rec1List->sceneBoundingRect().x()+55,rec1List->sceneBoundingRect().y()+45);
    rec1List->setData(5,rec1List->data(5).toString()+LT->data(1).toString()+";");
    rec1List->setData(6,rec1List->data(6).toString()+newS->data(5).toString()+"f"+";");
    newS->setData(8,++flagKolSv);
    //

    //
    auto* LT2 = new lineS();
    //0 - imy dlya obekta
    //1 - nom svyaz
    LT2->setData(0,"LineSuzh");
    LT2->setData(1,++flagNomSvyaz);
    LT2->setLine(60,0,rec2List->sceneBoundingRect().x()+55,rec2List->sceneBoundingRect().y()+45);
    rec2List->setData(5,rec2List->data(5).toString()+LT2->data(1).toString()+";");
    rec2List->setData(6,rec2List->data(6).toString()+newS->data(5).toString()+";");
    newS->setData(8,++flagKolSv);
    //

    //
    newS->setData(6,newS->data(3).toString()+newS->data(5).toString());
    //

    //
    textinbox* nazvSuzh = dynamic_cast<textinbox*>( rec1List->childItems().value(rec1List->data(4).toInt()));
    newS->setData(14,nazvSuzh->toPlainText());
    nazvSuzh = dynamic_cast<textinbox*>( rec2List->childItems().value(rec2List->data(4).toInt()));
    newS->setData(15,nazvSuzh->toPlainText());
    //

    LT->setParentItem(newS);
    LT2->setParentItem(newS);
    tt->setParentItem(newS);
    textUsvyaz->setParentItem(newS);
}
//

//
void MainWindow::recPosSuzhSvyaz(int nom)
{
    for (int All=mscene->items().count();All!=-1;All--)   //perebiraem vse elementi na scene
    {
        if (mscene->items().value(All)->data(3).toInt()==nom) //esli obekt - suzhnost
        {
            emit sendPosXSuzhSvyaz(mscene->items().value(All)->sceneBoundingRect().x(), mscene->items().value(All)->sceneBoundingRect().y());
        }
    }

    globFlagSvyaz = true;
}
//

//poluchaem novie X-Y dlya elementa svyzi pri peremezhenii
void svyaz::recPosXSuzhSvyaz(int XX, int YY)
{
    this->setData(1,XX);
    this->setData(2,YY);
}
//

//otklik pravoy knopki
void MainWindow::customMenuRequested(QPoint pos)
{
    auto *menu=new QMenu(this);
    if ((globFlagSuzh) && (delSuzh->data(0).toString()=="Suzhnost"))
    {
        QAction* addAtr = new QAction("Добавить атрибут", this);
            connect(addAtr,SIGNAL(triggered()),this,SLOT(addAtr()));
        menu->addAction(addAtr);

        if (flagNomSuzh >= 2)    //esli suzhnostey bolshe 2, to mozhno svyazivat
        {
            QAction* addSvyaz = new QAction("Установить связь", this);
                connect(addSvyaz,SIGNAL(triggered()),this,SLOT(addSvyaz()));
            menu->addAction(addSvyaz);
        }

        QAction* DelS = new QAction("Удалить", this);
            connect(DelS,SIGNAL(triggered()),this,SLOT(delS()));
        menu->addAction(DelS);
    }
    else if ((globFlagAtr) && (delSuzh->data(0).toString()=="Atribut")) //esli vibrali atribut
    {
        QAction* delAtr = new QAction("Удалить атрибут", this);
            connect(delAtr,SIGNAL(triggered()),this,SLOT(delS()));
        menu->addAction(delAtr);
    }
    else if ((globFlagSvyaz) && (delSuzh->data(0).toString()=="Svyaz")) //esli vibrali atribut
    {
        QAction* delSvyaz = new QAction("Удалить связь", this);
            connect(delSvyaz,SIGNAL(triggered()),this,SLOT(delS()));
        menu->addAction(delSvyaz);
    }
    else    //esli pustoe mesto to menu s dobavleniem suzhnosti
    {
        globFlagAtr = false;
        globFlagSvyaz = false;
        QAction* addSuzh = new QAction("Добавить сущность", this);
            connect(addSuzh,SIGNAL(triggered()),this,SLOT(addSuzh()));
        menu->addAction(addSuzh);
    }
    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}
//

//pri nazhatii knopki formirovaniya tablic v DB
void MainWindow::ReciveTextForDB()
{
    qDebug()<<"asdasdasd";
    QString aggr;

    QStringList temp = globTextDB.split(";");

    qDebug()<<temp;

    QSqlQuery* query = new QSqlQuery();
    for (int i=0; i<=temp.length()-1;i++)
    {
        QString tt = temp[i];
        qDebug()<<tt<<globTextDB;
        //if (!tt.contains("CONSTRAINT FK"))
        //{
            qDebug()<<"in";
            if (query->exec(tt))
            {
                aggr.append("Таблица успешно добавлена. ");
            }
            else
            {
                aggr.append("Произошла ошибка, таблица не была добавлена. ");
            }
        //}
    }

    QString tempSave;
    bool fl=false;
    bool infl = false;
    for (int i=0; i<temp.length()-1;i++)
    {
        QString tt = temp[i];
        if (tt.contains("CONSTRAINT"))
        {
            if (!query->exec(tt))
            {
                tempSave = tt;
                infl=true;
            }

            if (fl)
            {
                if (query->exec(tempSave))
                {
                    infl=false;
                }
            }

            if (infl)
            {
                fl=true;
            }
            else
            {
                fl=false;
            }
        }
    }

    delete query;
    mess->setText(aggr);
    mess->show();
}
//

//pri nazhatii knopki ispravleniya tablic v DB
void MainWindow::EditTextForDB()
{
    QSqlQuery* query = new QSqlQuery();
        query->exec(FinishText->toPlainText());                 //vipolnyaem redaktirovanie tablic db
    delete query;
}

//podkluchenie k DB - MS SQL
void MainWindow::on_action_MS_SQL_Server_2_triggered()
{
    logwin = new login();
        connect(logwin,SIGNAL(sendConnect()),this,SLOT(recConnect()));
    logwin->show();
}
//

//vihod
void MainWindow::on_closeApp_triggered()
{
    this->close();
}
//

//smena cveta v statuse
void MainWindow::recConnect()
{
    if (logwin->checkconn(logwin->db))
    {
        statText->setText("Подключение к базе данных "+globChangeCombo+" установлено");
        statCvet->setStyleSheet("background-color:#00ff00");
        ButViborDataBase->setEnabled(true);

        QSqlQuery* query = new QSqlQuery();
        query->exec("SELECT name FROM sys.databases"); //vibiraem vse imena DB s servera
        while (query->next())
        {
            changeDB->addItem(query->value(0).toString());  //zapolnyaem combo imenami
        }
        delete query;

        ui->vigrDB->setEnabled(true);
        ui->action_MS_SQL_Server->setEnabled(true);
    }
}
//

//otkluchenie ot DB
void MainWindow::on_action_MS_SQL_Server_triggered()
{
    if (logwin->checkconn(logwin->db))
    {
        logwin->closeconn(logwin->db);
        ButViborDataBase->setEnabled(false);

        statText->setText("Подключение к базе данных не установлено");
        statCvet->setStyleSheet("background-color:#ff0000");
        changeDB->clear();
        ui->vigrDB->setEnabled(false);
        ui->action_MS_SQL_Server->setEnabled(false);

        delete logwin;
    }
}
//

//dobavlenie suzhnosti
void MainWindow::addSuzh()
{
    on_action_triggered();
}
//

//zagruzka dannih iz DB
void MainWindow::on_vigrDB_triggered()
{
    suzhnost* suzh;
    QSqlQuery* query = new QSqlQuery();
        query->exec("select o.name, c.name, t.name, c.max_length from sys.objects o inner join sys.columns c on c.object_id = o.object_id inner join sys.types t on c.system_type_id = t.system_type_id where t.user_type_id = t.system_type_id and o.type = 'U' AND o.name NOT LIKE '%sysdiagrams%' order by 1, 2");
    QString temp = "";
    while (query->next())
    {
        //query->value(0).toString() - imya tablici
        if (temp!=query->value(0).toString())
        {
            temp = query->value(0).toString();
            flagNomSuzh = flagNomSuzh + 1;
            suzh = new suzhnost();
            suzh->setData(3,flagNomSuzh);
            setSuzh(suzh, query->value(0).toString());  //dobavit suzhnost
            suzh->setPos(150*(suzh->data(3).toInt()-1),100);
        }

        auto* atr = new atribut();
        connect(atr, SIGNAL(sendTekuzhAtr(QGraphicsItem*)), this, SLOT(reciveTekuzhSuzh(QGraphicsItem*)));    //dlya opredeleniya atributa pri nazhatii na bistrie dobavlenie atributa i udalenie
        //organizuem atribut
        setAtr(suzh, atr, query->value(1).toString(), "nokey", query->value(2).toString(), query->value(3).toString());  //dobavit atribut
    }
    //

    //FORMIRUEM KLUCHEVOE POLE SUZHNOSTEY
    QSqlQuery* query2 = new QSqlQuery();
    query->exec("select name from sys.objects WHERE type_desc='USER_TABLE'");
    while (query->next())
    {
        if (query->value(0).toString()!="sysdiagrams")
        {
            //nahodim kluchevoe pole dlya konkretnoy tablici
            query2->prepare("select COLUMN_NAME from INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE where TABLE_NAME = :id2 AND CONSTRAINT_NAME LIKE 'PK%'");
            query2->bindValue(":id2",query->value(0).toString());
            query2->exec();
            while (query2->next())
            {
                for (int All=mscene->items().count();All!=-1;All--)
                {
                    if ((mscene->items().value(All)->data(0).toString()=="Suzhnost"))
                    {
                        //text suzhnosti
                        textinpaste =dynamic_cast<textinbox*>( mscene->items().value(All)->childItems().value(mscene->items().value(All)->data(4).toInt()));
                        if (textinpaste->toPlainText()==query->value(0).toString())
                        {
                            //vpisat v suzhnost kluch
                            mscene->items().value(All)->setData(2,query2->value(0).toString());

                            QList<QGraphicsItem *> itm = mscene->items().value(All)->childItems();
                            for (int i=0;i<itm.size();i++)
                            {
                                if (itm.value(i)->data(0).toString()=="Atribut")
                                {
                                    //vistavlyaem, chto atribut - kluch
                                    textinpaste =dynamic_cast<textinbox*>( itm.value(i)->childItems().value(1));
                                    if (textinpaste->toPlainText()==query2->value(0).toString())
                                    {
                                        itm.value(i)->setData(2,"key");
                                        itm.value(i)->setData(4,query2->value(0).toString());
                                        textinpaste->setHtml("<center><u>"+textinpaste->toPlainText()+"</u></center>");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    query2->clear();
    //

    //FORMIRUEM SVYAZY
    query->exec("select (select name from sys.objects where object_id=fk.parent_object_id), (select name from sys.objects where object_id=fk.referenced_object_id) from sys.foreign_keys fk");
    while (query->next())
    {
        //FK_Сущность1_Сущность2     - na pervom meste suzhnost vtorostepennaya, na vtorom - glavnaya
        auto* glavSuzh = new suzhnost();
        auto* vtorSuzh = new suzhnost();

        newS = new svyaz();
        newS->setData(0,"Svyaz");

        for (int All=mscene->items().count();All!=-1;All--)
        {
            if ((mscene->items().value(All)->data(0).toString()=="Suzhnost"))
            {
                //text suzhnosti
                textinpaste = dynamic_cast<textinbox*>( mscene->items().value(All)->childItems().value(mscene->items().value(All)->data(4).toInt()));
                //esli text suzhnosti raven vtorostepennoy suzhnosti
                if (query->value(0).toString()==query->value(1).toString())
                {
                    vtorSuzh = dynamic_cast<suzhnost*>( mscene->items().value(All));
                    glavSuzh = vtorSuzh;
                    newS->setData(4,mscene->items().value(All)->data(3).toInt());
                    newS->setData(11,textinpaste->toPlainText());        //nazvanie polya
                    newS->setData(3,mscene->items().value(All)->data(3).toInt());
                    newS->setData(10,textinpaste->toPlainText());        //nazvanie polya

                    newS->setData(15,query->value(0).toString());        //nazvanie klucha 1 i 2 suzhnosti
                    newS->setData(17, mscene->items().value(All)->data(2).toString());  //kluch
                    newS->setData(20,"FK_"+newS->data(10).toString()+"_"+newS->data(11).toString());
                }
                else
                {
                    if (textinpaste->toPlainText() == query->value(0).toString())
                    {
                        vtorSuzh = dynamic_cast<suzhnost*>( mscene->items().value(All));
                        newS->setData(4,mscene->items().value(All)->data(3).toInt());
                        newS->setData(11,textinpaste->toPlainText());
                        newS->setData(15,query->value(0).toString());
                    }
                    else if (textinpaste->toPlainText()== query->value(1).toString())
                    {
                        glavSuzh = dynamic_cast<suzhnost*>( mscene->items().value(All));
                        newS->setData(3,mscene->items().value(All)->data(3).toInt());
                        newS->setData(10,textinpaste->toPlainText());
                    }

                    newS->setData(20,"FK_"+newS->data(11).toString()+"_"+newS->data(10).toString());
                }
            }
        }


        newS->setData(5,++flagItemSvyaz);
        newS->setData(7,"1:1");
        mscene->addItem(newS);

        //text pod svyazyu
        auto * textUsvyaz = new textinbox();
        textUsvyaz->setData(0,"TextUSvyaz");
        textUsvyaz->setTextWidth(120);
        textUsvyaz->setHtml("<center>"+QString("")+"</center>");
        textUsvyaz->moveBy(0,50);
        newS->setData(8,++flagKolSv);
        //

        connect(newS,SIGNAL(sendPosSuzhSvyaz(int)),this,SLOT(recPosSuzhSvyaz(int)));
        connect(this,SIGNAL(sendPosXSuzhSvyaz(int,int)),newS,SLOT(recPosXSuzhSvyaz(int,int)));

        //
        auto* LT = new lineS();
        //0 - imy dlya obekta
        //1 - nom svyaz
        LT->setData(0,"LineSuzh");
        LT->setData(1,++flagNomSvyaz);
        LT->setLine(60,0,glavSuzh->sceneBoundingRect().x()+55,glavSuzh->sceneBoundingRect().y()+45);
        glavSuzh->setData(5,glavSuzh->data(5).toString()+LT->data(1).toString()+";");
        glavSuzh->setData(6,glavSuzh->data(6).toString()+newS->data(5).toString()+"f"+";");
        newS->setData(8,++flagKolSv);
        //

        //
        auto* LT2 = new lineS();
        //0 - imy dlya obekta
        //1 - nom svyaz
        LT2->setData(0,"LineSuzh");
        LT2->setData(1,++flagNomSvyaz);
        LT2->setLine(60,0,vtorSuzh->sceneBoundingRect().x()+55,vtorSuzh->sceneBoundingRect().y()+45);
        vtorSuzh->setData(5,vtorSuzh->data(5).toString()+LT2->data(1).toString()+";");
        vtorSuzh->setData(6,vtorSuzh->data(6).toString()+newS->data(5).toString()+";");
        newS->setData(8,++flagKolSv);
        //

        //
        newS->setData(6,newS->data(3).toString()+newS->data(5).toString());
        //

        LT->setParentItem(newS);
        LT2->setParentItem(newS);
        textUsvyaz->setParentItem(newS);
    }

    //naidem atribut, chto yavlyaetsya FK
    QString TempKey;
    QSqlQuery* query3 = new QSqlQuery();
    QSqlQuery* query5 = new QSqlQuery();
    query->exec("select c.name, f.referenced_object_id, f.parent_object_id from sys.columns c inner join sys.foreign_key_columns f on c.column_id=f.parent_column_id and c.object_id = f.parent_object_id");
    while (query->next())
    {
        //naidem imy suzhnosti, s kotorim svyaz - t.e. GLAVNUYU SUZHNOST
        query2->prepare("select name from sys.objects WHERE object_id=:id");
        query2->bindValue(":id",query->value(1).toString());
        query2->exec();
        query2->next();
        //query2->value(0).toString();  - GLAVNAYA po svyazi dly atributa tekuzhego
        //query->value(0).toString(); - imya FK

        //proveryam - tekuzhiy atribut yavlyaetsya li kluchem
        query3->prepare("select COLUMN_NAME from INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE where TABLE_NAME = (select name from sys.objects o where o.object_id = :id2 AND CONSTRAINT_NAME LIKE 'PK%')");
        query3->bindValue(":id2",query->value(2).toString());
        query3->exec();
        while (query3->next())
        {
            //hranim imya vtorostepennoy suzhnosti
            query5->prepare("select name from sys.objects WHERE type_desc='USER_TABLE' and object_id=:id3");
            query5->bindValue(":id3", query->value(2).toString());
            query5->exec();
            query5->next();
            //

            TempKey = query3->value(0).toString();

            for (int All=mscene->items().count();All!=-1;All--)
            {
                if ((mscene->items().value(All)->data(0).toString()=="Svyaz") && (mscene->items().value(All)->data(10).toString()==query2->value(0).toString()) && (mscene->items().value(All)->data(11).toString()==query5->value(0).toString()) && (query->value(0).toString()==TempKey))
                {
                    //qDebug()<<"1";
                    auto * tt = new textinbox();
                    tt->setData(0,"TextSvyaz");
                    tt->setPos(0,-10);
                    tt->setTextWidth(120);
                    tt->setHtml("<center><font size=4><b>"+QString("1:1")+"</b></font></center>");
                    mscene->items().value(All)->setData(8,++flagKolSv);
                    mscene->items().value(All)->setData(7,"1:1");
                    tt->setParentItem(mscene->items().value(All));
                }
                else if ((mscene->items().value(All)->data(0).toString()=="Svyaz") && (mscene->items().value(All)->data(10).toString()==query2->value(0).toString()) && (mscene->items().value(All)->data(11).toString()==query5->value(0).toString()) && (query->value(0).toString()!=TempKey))
                {
                    //qDebug()<<"2";
                    auto * tt = new textinbox();
                    tt->setData(0,"TextSvyaz");
                    tt->setPos(0,-10);
                    tt->setTextWidth(120);
                    tt->setHtml("<center><font size=4><b>"+QString("1:N")+"</b></font></center>");
                    mscene->items().value(All)->setData(8,++flagKolSv);
                    mscene->items().value(All)->setData(7,"1:N");

                    mscene->items().value(All)->setData(9,query->value(0).toString());
                    flag1N = true;

                    tt->setParentItem(mscene->items().value(All));
                }
            }
        }
    }


    delete query;
    delete query2;
    delete query3;
    delete query5;

    VigsDB = true;
}
//

//procedura dobavleniya atributa
void MainWindow::setAtr(QGraphicsItem* suzhN, atribut* Atr, const QString& nameAtr, const QString& KnK, const QString& tipAtr, const QString& kolSim)
{
    Atr->setData(1, tipAtr);
    Atr->setData(2,KnK);
    Atr->setData(4, nameAtr);     //pomezhaem dlya hraneniya imya atributa

    if ((tipAtr=="varchar") || (tipAtr=="char"))
    {
        if (kolSim!="-1")
        {
            Atr->setData(3, nameAtr+" "+tipAtr+"("+kolSim+")");
            Atr->setData(5, nameAtr+"_FK "+tipAtr+"("+kolSim+")");
            Atr->setData(7, kolSim);
        }
        else
        {
            Atr->setData(3, nameAtr+" "+tipAtr+"(max)");
            Atr->setData(5, nameAtr+"_FK "+tipAtr+"(max)");
        }
    }
    else
    {
        Atr->setData(3, nameAtr+" "+tipAtr);
        Atr->setData(5, nameAtr+"_FK "+tipAtr);
    }

    //perenesem vbok
    Atr->moveBy(-200*sin(1.5/2 * suzhN->data(4).toInt()),-200*cos(1.5/2 * suzhN->data(4).toInt()));
    //

    textEl = new textinell();
    textEl->setData(0,"TextAtr");
    textEl->setPos(-30,0);
    textEl->setTextWidth(120);
    QFont intexta("Times", 10);
    textEl->setFont(intexta);
    textEl->setHtml("<center>"+nameAtr+"</center>");
    textEl->setParentItem(Atr);

    //
    auto* LT = new lineS();
    LT->setData(0,"LineAtr");
    LT->setData(1, 0 - Atr->x() + 30);
    LT->setData(2, 0 - Atr->y());
    LT->setLine(30,15,LT->data(1).toInt(),LT->data(2).toInt());
    LT->setParentItem(Atr);
    //

    //dobavlyaem element parametra k atributu dlya bistrogo udaleniya
    auto* ryad = new paramatr();
    ryad->setPos(20,-30);
    ryad->setData(0,"ParamAtrDel");
    ryad->setHtml("D");
    ryad->setVisible(false);
    ryad->setParentItem(Atr);
    //

    Atr->setParentItem(suzhN);

    //sohranim imya suzhnosti v atribute
    textinpaste = dynamic_cast<textinbox*>( Atr->parentItem()->childItems().value(Atr->parentItem()->data(4).toInt()+1));
    Atr->setData(6,textinpaste->toPlainText());
    //

    //uvelichivaem schetchik kolva atributov u dannoy suzhnosti
    suzhN->setData(4,suzhN->data(4).toInt()+1);
    //
}
//

//ochizhaem scenu
void MainWindow::on_action_6_triggered()
{
    mscene->clear();

    ui->graphicsView->fitInView(0,0, ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio);

    FinishTextForAddAtr->clear();
    FinishTextForDel->clear();
    flagNomSuzh = 0;
    flagNomSvyaz = 0;
    flagItemSvyaz=0;
    flagKolSv = 0;

    VigsDB = false; //esli zagruzhali iz DB - otmenyaem

    ui->SimpleSave->setEnabled(false);
}

//spravka
void MainWindow::on_action_3_triggered()
{
    QDialog* diag = new QDialog(nullptr);
    diag->setWindowTitle("О программе...");
    diag->setModal(true);

    auto* VerticalR = new QVBoxLayout(diag);
    auto* myEdit = new QTextEdit(diag);
    myEdit->setHtml("Версия 0.00000000017 (04-08-2016) <br>");
    VerticalR->addWidget(myEdit);
    myEdit->setEnabled(true);

    diag->setLayout(VerticalR);
    diag->show();
}

//vibor db dlya raboti
void MainWindow::changeDB_currentTextChanged(const QString &arg1)
{
    globChangeCombo = arg1;
}

//knopka vibora db dlya raboti
void MainWindow::ButViborDataBase_on_clicked()
{
    logwin->conn(globChangeCombo);
}


//sohranenie shemi
void MainWindow::on_action_SaveScheme_triggered()
{
    saveAs_or_simpleSave("saveAs");
}

//zagruzka schemi
void MainWindow::on_action_LoadScheme_triggered()
{
    QFile file(QFileDialog::getOpenFileName(nullptr,"","/","*.ermdb"));
    if(file.open(QIODevice::ReadOnly))
    {
        QString s0,s1,s2,s3;
        QStringList sep,sep_2;

        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            str = stream.readLine();
            suzhnost* suzh;

            if (str.contains("<suzhnost>"))
            {
                flagNomSuzh = flagNomSuzh + 1;
                suzh = new suzhnost();
                suzh->setData(3,flagNomSuzh);
                str.remove(0,10);
                str.remove(str.length()-11,11);
                setSuzh(suzh, str);  //dobavit suzhnost
                suzh->setPos(150*(suzh->data(3).toInt()-1),100);
            }

            if (str.contains("<atribut>"))
            {
                auto* atr = new atribut();
                connect(atr, SIGNAL(sendTekuzhAtr(QGraphicsItem*)), this, SLOT(reciveTekuzhSuzh(QGraphicsItem*)));    //dlya opredeleniya atributa pri nazhatii na bistrie dobavlenie atributa i udalenie
                //organizuem atribut
                sep = str.split("//");
                s0 = sep[0];    //nazvanie
                s1 = sep[1];    //key or nokey
                s2 = sep[2];    //tip
                s3 = sep[3];    //kolsim
                s0.remove(0,9); //ubiraem <atribut>
                s3.remove(s3.length()-10,10);   //ubiraem </atribut>
                setAtr(suzh, atr, s0, s1, s2, s3);  //dobavit atribut
                if ((s1 == "key") || (s1 == "keyInt"))
                {
                    atr->parentItem()->setData(12,atr->parentItem()->data(12).toInt()+1);   //ustanavlivaem chto u suzhnosti est pole kluch
                    textinell* tempText =dynamic_cast<textinell*>( atr->childItems().value(1));
                    tempText->setHtml("<center><u>"+tempText->toPlainText()+"</u></center>");   //podcherkivaem
                }
            }

            if (str.contains("<svyaz>"))
            {
                str.remove(0,7);    //ubiraem <svyaz>
                str.remove(str.count()-8,8);    //ubiraem </svyaz>
                sep = str.split(";");
                for (int i = 0; i < sep.count()-1;i++)
                {
                    s0 = sep[i];
                    sep_2 = s0.split("-");
                    rec2Suzh(sep_2[0],sep_2[1], sep_2[2], sep_2[3]);
                }
            }
        }
        if(stream.status()!= QTextStream::Ok)
        {
            mess->setText("Файл невозможно прочитать");
            mess->show();
        }
        file.close();
    }
}

//sohranenie na prediduzhiy put
void MainWindow::on_SimpleSave_triggered()
{
    saveAs_or_simpleSave("simpleSave");
}

//sohranenie AS or Simple
void MainWindow::saveAs_or_simpleSave(const QString& how)
{
    QFile file;
    if (how == "saveAs")
    {
        file.setFileName(QFileDialog::getSaveFileName(nullptr,"",settings->value("settings/pathsave","/").toString(),"*.ermdb"));
        ui->SimpleSave->setEnabled(true);
    }
    else
    {
        file.setFileName(settings->value("settings/pathsave","/").toString());
    }

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);

        for (int All=mscene->items().count();All!=-1;All--)
        {
            if ((mscene->items().value(All)->data(0).toString()=="Suzhnost"))
            {
                textinbox* test = dynamic_cast<textinbox*>( mscene->items().value(All)->childItems().value(mscene->items().value(All)->data(4).toInt()));
                stream << "<suzhnost>" << test->toPlainText() << "</suzhnost>\n";

                QList<QGraphicsItem *> itm = mscene->items().value(All)->childItems();
                for (int i=0;i<itm.size();i++)
                {
                    if (itm.value(i)->data(0).toString()=="Atribut")
                    {
                        //nazvanie - KeyNeKey - tip - kolsim
                        stream << "<atribut>" << itm.value(i)->data(4).toString()+"//"+itm.value(i)->data(2).toString()+"//"+itm.value(i)->data(1).toString()+"//"+itm.value(i)->data(7).toString() << "</atribut>\n";
                    }
                }
            }
        }

        stream << "<svyaz>";
        for (int All=mscene->items().count();All!=-1;All--)
        {
            if ((mscene->items().value(All)->data(0).toString()=="Svyaz"))
            {
                //glavnaya suzh - vtor suzh - 1:1 ili 1:N - podpis pod svyazyu
                stream << mscene->items().value(All)->data(14).toString() << "-" << mscene->items().value(All)->data(15).toString() << "-" << mscene->items().value(All)->data(7).toString() << "-" << mscene->items().value(All)->data(19).toString() << ";";
            }
        }
        stream << "</svyaz>";

        if (how == "saveAs")
        {
            //sohranyaem put
            settings->setValue("settings/pathsave",file.fileName());  //
            settings->sync(); //
        }

        file.close();
        if (stream.status() != QTextStream::Ok)
        {
            mess->setText("Ошибка записи файла");
            mess->show();
        }
    }
}

//proverit obnovlenie
void MainWindow::on_checkUpdate_triggered()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("194.87.103.91",7777);

    if (socket->waitForConnected(1000))
    {
        socket->write(settings->value("settings/curVer","/").toByteArray());

        socket->waitForReadyRead(1000);
        QByteArray Data = socket->readAll();
        if (Data == "OK")
        {
            mess->setText("У вас последняя версия программы");
        }
        else
        {
            mess->setText("Существует обновленная версия программы");
        }
        mess->show();
    }
    else
    {
        mess->setText(QString(socket->error()));
        mess->show();
    }

    socket->close();
    socket->deleteLater();
}

//po seti dobavlenie suzhnosti
void MainWindow::netwRecSuzh(const QString& nameS)
{
    if (ui->netWork->isChecked())
    {
        if (!socket->isOpen())
        {
            socket = new QTcpSocket(this);
                connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
            socket->connectToHost("194.87.103.91",7777);
        }
        else
        {
            if (socket->waitForConnected(1000))
            {
                socket->write(QByteArray(QString(R"({"action":"addSuzh","name":")"+nameS+"\"}").toUtf8().data()));
                socket->waitForBytesWritten(1000);
                socket->flush();
            }
        }
    }
    else
    {
        qDebug()<<"Ne ustanovlen setevoy rezhim";
    }
}

//po seti dobavlenie atributa
void MainWindow::netwRecAtr(QGraphicsItem* suzh, const QString& nameAtr, const QString& KnK, const QString& tipAtr, const QString& KolS)
{
    if (ui->netWork->isChecked())
    {
        if (!socket->isOpen())
        {
            socket = new QTcpSocket(this);
                connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
            socket->connectToHost("194.87.103.91",7777);
        }
        else
        {
            if (socket->waitForConnected(1000))
            {
                textinbox* test = dynamic_cast<textinbox*>( suzh->childItems().value(suzh->data(4).toInt()));
                socket->write(QByteArray(QString(R"({"action":"addAtr","nameSuzh":")"+test->toPlainText()+R"(","nameAtr":")"+nameAtr+R"(","KnK":")"+KnK+R"(","tipAtr":")"+tipAtr+R"(","KolS":")"+KolS+"\"}").toUtf8().data()));
                socket->waitForBytesWritten(1000);
                socket->flush();
            }
        }
    }
    else
    {
        qDebug()<<"Ne ustanovlen setevoy rezhim";
    }
}

//podkluchenie po seti
void MainWindow::on_netWork_triggered()
{
    if (ui->netWork->isChecked())
    {
        socket = new QTcpSocket(this);
            connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
            connect(socket,SIGNAL(readyRead()),this,SLOT(readyReadSock()));
        socket->connectToHost("194.87.103.91",7777);

        ui->addRemChat->setEnabled(true);
        ui->plainTextEdit->show();
        ui->lineEdit->show();
        ui->pushButton->show();
        ui->addRemChat->setChecked(true);
    }
    else
    {
        statNetwText->setText("");
        socket->close();
        socket->deleteLater();

        ui->addRemChat->setEnabled(false);
        ui->plainTextEdit->hide();
        ui->lineEdit->hide();
        ui->pushButton->hide();
    }
}

void MainWindow::readyReadSock()
{
    Data = (dynamic_cast<QTcpSocket*>(sender()))->readAll();

    jsonDoc = QJsonDocument::fromJson(Data, &parseError);
    jsonMessage = jsonDoc.object();

    //esli soedinenie uspeshno
    if (jsonMessage["type"].toString()=="welcome")
    {
        statCvetNet->setStyleSheet("background-color:#00ff00");
        if (jsonMessage["status"].toString()=="server")
            statNetwText->setText("Статус: сервер");
        else
        {
            statNetwText->setText("Статус: клиент");
            ui->graphicsView->setEnabled(false);
        }
    }
    else if (jsonMessage["type"].toString()=="chat")    //pishem v chat
    {
        ui->plainTextEdit->insertPlainText(jsonMessage["text"].toString());
    }
    else if ((jsonMessage["type"].toString()=="client") && (jsonMessage["action"].toString()=="addsuzh"))
    {
        auto* suzh = new suzhnost();
        flagNomSuzh = flagNomSuzh + 1;
        suzh->setData(3,flagNomSuzh);
        suzh->setPos(150*(suzh->data(3).toInt()-1),100);
        setSuzh(suzh, jsonMessage["name"].toString());
    }
    else if ((jsonMessage["type"].toString()=="client") && (jsonMessage["action"].toString()=="addatr"))
    {
        for (int All=mscene->items().count();All!=-1;All--)
        {
            if (mscene->items().value(All)->data(0).toString()=="Suzhnost")
            {
                textinbox* test = dynamic_cast<textinbox*>( mscene->items().value(All)->childItems().value(mscene->items().value(All)->data(4).toInt()));
                if (test->toPlainText()==jsonMessage["nameSuzh"].toString())
                {
                    atr = new atribut();
                    setAtr(mscene->items().value(All), atr, jsonMessage["nameAtr"].toString(), jsonMessage["KnK"].toString(), jsonMessage["tipAtr"].toString(), jsonMessage["KolS"].toString());
                }
            }
        }
    }
    else if ((jsonMessage["type"].toString()=="client") && (jsonMessage["action"].toString()=="changepossuzh"))
    {
        for (int All=mscene->items().count();All!=-1;All--)
        {
            if (mscene->items().value(All)->data(0).toString()=="Suzhnost")
            {
                textinbox* test = dynamic_cast<textinbox*>( mscene->items().value(All)->childItems().value(mscene->items().value(All)->data(4).toInt()));
                if (test->toPlainText()==jsonMessage["nameSuzh"].toString())
                {
                    mscene->items().value(All)->setPos(jsonMessage["posX"].toDouble(),jsonMessage["posY"].toDouble());
                }
            }
        }
    }
}

//disconnect socket
void MainWindow::sockDisc()
{
    statCvetNet->setStyleSheet("background-color:#ff0000");
    ui->graphicsView->setEnabled(true);
    socket->close();
    socket->deleteLater();
}

//napisat v chat
void MainWindow::on_pushButton_clicked()
{
    if (ui->netWork->isChecked())
    {
        if (!socket->isOpen())
        {
            socket = new QTcpSocket(this);
                connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
            socket->connectToHost("194.87.103.91",7777);
        }
        else
        {
            if (socket->waitForConnected(1000))
            {
                socket->write(QByteArray(QString(R"({"action":"sendChat","text":")"+ui->lineEdit->text()+"\"}").toUtf8().data()));
                socket->waitForBytesWritten(1000);
                socket->flush();
            }
        }
    }
    else
    {
        qDebug()<<"Ne ustanovlen setevoy rezhim";
    }

    ui->lineEdit->clear();
}

//pokazat skrit chat
void MainWindow::on_addRemChat_triggered()
{
    if (ui->addRemChat->isChecked())
    {
        ui->plainTextEdit->show();
        ui->lineEdit->show();
        ui->pushButton->show();
    }
    else
    {
        ui->plainTextEdit->hide();
        ui->lineEdit->hide();
        ui->pushButton->hide();
    }
}
