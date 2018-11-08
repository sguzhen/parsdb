#ifndef SUZHPARAM_H
#define SUZHPARAM_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class suzhparam;
}

class suzhparam : public QDialog
{
    Q_OBJECT

public:
    explicit suzhparam(QWidget *parent = 0);
    ~suzhparam();

    QMessageBox* mess;

signals:
    void sendNameSuzh(const QString&);

private slots:
    void on_pushButton_clicked();
    void recSuzhText(const QString&);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::suzhparam *ui;
};

#endif // SUZHPARAM_H
