#include "suzhparam.h"
#include "ui_suzhparam.h"

suzhparam::suzhparam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::suzhparam)
{
    ui->setupUi(this);

    mess = new QMessageBox();
}

suzhparam::~suzhparam()
{
    delete mess;
    delete ui;
}

void suzhparam::on_pushButton_clicked()
{
    emit sendNameSuzh(ui->lineEdit->text());
    this->close();
}

void suzhparam::recSuzhText(const QString& tekTekst)
{
    ui->lineEdit->setText(tekTekst);
    ui->lineEdit->selectAll();
}

void suzhparam::on_lineEdit_textChanged(const QString &arg1)
{
    if ((arg1.contains("_")) || (arg1.contains("/")) || (arg1.contains("\\")) || (arg1.contains("-")))
    {
        mess->setText("В имени сущности не должно быть спецсимволов (_,/,\\,- и пр.)");
        mess->show();
        ui->pushButton->setEnabled(false);
    }
    else
    {
        ui->pushButton->setEnabled(true);
    }
}
