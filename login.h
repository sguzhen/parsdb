#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

    QSqlDatabase db;
    QMessageBox* mes;

    void conn(const QString&);
    void closeconn(QSqlDatabase);
    bool checkconn(const QSqlDatabase&);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void sendConnect();         //esli podkluchenie uspeshno, to visilaem signal na smeny cveta

private:
    Ui::login *ui;
};

#endif // LOGIN_H
