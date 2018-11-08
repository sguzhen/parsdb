#include "atrparam.h"
#include "ui_atrparam.h"

#include <QDebug>

atrparam::atrparam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::atrparam)
{
    ui->setupUi(this);

    ui->comboBox->addItem("char");
    ui->comboBox->addItem("int");
    ui->comboBox->addItem("float");
    ui->comboBox->addItem("money");
    ui->comboBox->addItem("varchar");
    ui->comboBox->addItem("varchar(max)");
    ui->comboBox->addItem("date");
}

atrparam::~atrparam()
{
    delete ui;
}

void atrparam::on_pushButton_clicked()
{
    if ((ui->checkBox->isChecked()) && (CurTip=="int"))
    {
        emit sendTip(CurTip, "keyInt", 0, ui->lineEdit->text(), status);
    }
    else if ((ui->checkBox->isChecked()) && (CurTip!="int"))
    {
        if ((CurTip=="varchar") || (CurTip=="char"))
        {
            emit sendTip(CurTip, "key", ui->spinBox->value(), ui->lineEdit->text(), status);
        }
        else
        {
            emit sendTip(CurTip, "key", 0, ui->lineEdit->text(), status);
        }
    }
    else
    {
        if ((CurTip=="varchar") || (CurTip=="char"))
        {
            emit sendTip(CurTip, "nokey", ui->spinBox->value(), ui->lineEdit->text(), status);
        }
        else
        {
            emit sendTip(CurTip, "nokey", 0, ui->lineEdit->text(), status);
        }
    }

    //emit netwSetAtr();
    this->close();
}

void atrparam::on_comboBox_currentIndexChanged(const QString &arg1)
{
    CurTip=arg1;

    if ((arg1=="varchar") || (arg1=="char"))
    {
        ui->spinBox->setEnabled(true);
    }
    else
    {
        ui->spinBox->setEnabled(false);
    }
}

//poluchaem pri dvoinom nazhatii kluch ili net; nazvanie atributa i ego tip
void atrparam::recAtrText(const QString& keyNokey, const QString& textAtr, const QString& tipA, int KolSim)
{
    //vistavlyaem imya atributa
    ui->lineEdit->setText(textAtr);

    //esli kluch - to stavim galky
    if ((keyNokey=="key") || (keyNokey=="keyInt"))
    {
        ui->checkBox->setChecked(true);
        status = true;
    }
    //

    //vistavlyaem tip dannih atributa kotoriy bil pri sozdanii
    for (int i=0; i<ui->comboBox->count();i++)
    {
        if (tipA==ui->comboBox->itemText(i))
        {
            ui->comboBox->setCurrentIndex(i);
        }
    }
    //

    if ((tipA=="varchar") || (tipA=="char"))
    {
        ui->spinBox->setValue(KolSim);
    }
}

//esli zhmem otmena
void atrparam::on_pushButton_2_clicked()
{
    this->close();
}
