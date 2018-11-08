#include "setsvyaz.h"
#include "ui_setsvyaz.h"

setSvyaz::setSvyaz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setSvyaz)
{
    ui->setupUi(this);

    this->setWindowTitle("Установление связи между сущностями");

    ui->comboBox->addItem("1:1");
    ui->comboBox->addItem("1:N");
}

setSvyaz::~setSvyaz()
{
    delete ui;
}

//poluchenie spiska textov suzhnostey iz glavnogo okna
void setSvyaz::recVec(QVector <QString> aa)
{
    for (int i = 0; i < aa.size(); i++)
    {
        ui->listWidget->insertItem(i,aa[i]);
        ui->listWidget_2->insertItem(i,aa[i]);
    }
}
//

//peredaem v programmy vibor usera iz pervogo lista
void setSvyaz::on_listWidget_itemClicked(QListWidgetItem *item)
{
    list1vib=item->text();

    //po vsem elementam vtorogo okna probegaem
//    for (int i = 0; i < ui->listWidget_2->count(); i++)
//    {
//        if (ui->listWidget_2->item(i)->text() == list1vib)  //esli text vibranniy sootv tomy chto est vo vtorom okne
//        {
//            ui->listWidget_2->item(i)->setHidden(true); //to pryachem
//        }
//        else
//        {
//            ui->listWidget_2->item(i)->setHidden(false); //inache pokazivaem
//        }
//    }
}
//

//peredaem v programmy vibor usera iz vtorogo lista
void setSvyaz::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    list2vib=item->text();

    //po vsem elementam pervogo okna probegaem
//    for (int i = 0; i < ui->listWidget->count(); i++)
//    {
//        if (ui->listWidget->item(i)->text() == list2vib)  //esli text vibranniy sootv tomy chto est vo vtorom okne
//        {
//            ui->listWidget->item(i)->setHidden(true); //to pryachem
//        }
//        else
//        {
//            ui->listWidget->item(i)->setHidden(false); //inache pokazivaem
//        }
//    }
}
//

//knopka peredachi parametrov dly svyazi suzhnostey
void setSvyaz::on_pushButton_clicked()
{
//    if (list1vib == list2vib)       //proveryaem imena soedinyaemih suzhnostey
//    {
//        QMessageBox * mes = new QMessageBox();
//        mes->setText("Сущности имеют одинаковые имена - исправьте!");
//        mes->show();
//    }
//    else
//    {
        emit send2Suzh(list1vib,list2vib,FromComboVib,ui->lineEdit->text());  //signal otpravki parametrov v glavnoe okno
        this->close();
//    }
}
//

//vibor usera
void setSvyaz::on_comboBox_currentIndexChanged(const QString &arg1)
{
    FromComboVib=arg1;
}
