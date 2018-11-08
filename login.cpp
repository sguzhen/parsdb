#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QODBC");

    mes = new QMessageBox();
    mes->setWindowTitle("Статус подключения");

    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

    this->setWindowTitle("Подключение к БД");
}

login::~login()
{
    delete mes;
    delete ui;
}

void login::on_pushButton_clicked()
{
    conn("tempdb");
}

//knopka otmena
void login::on_pushButton_2_clicked()
{
    this->close();
}

void login::conn(const QString& textDB)
{
    if (checkconn(db))
    {
        db.close();
        //db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        db = QSqlDatabase::addDatabase("QODBC");
    }

    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()+";DATABASE="+textDB+";");
    db.setUserName(ui->lineEdit_2->text());
    db.setPassword(ui->lineEdit_3->text());

    if (db.open())
    {
        mes->setText("Подключение успешно ");
            sendConnect();
        this->close();
    }
    else
    {
        mes->setText("Подключение не удалось: "+db.lastError().text());
    }
    mes->show();
}

//zakritie db
void login::closeconn(QSqlDatabase namedb)
{
    namedb.close();
    //namedb = QSqlDatabase();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

//proverka otkrito soedinenie ili net
bool login::checkconn(const QSqlDatabase& namedb)
{
    return namedb.isOpen();
}
