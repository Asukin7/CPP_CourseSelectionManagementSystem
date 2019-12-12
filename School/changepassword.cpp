#include "changepassword.h"
#include "ui_changepassword.h"

ChangePassword::ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_pushButton_changePassword_clicked()
{
    if(ui->lineEdit_changePassword->text().length() < 6)
    {
        QMessageBox::critical(this, "错误", "密码位数需要大于或等于6位");
        return;
    }
    if(ui->lineEdit_changePassword->text() != ui->lineEdit_changePassword_2->text())
    {
        QMessageBox::critical(this, "错误", "密码输入不一致");
        return;
    }
    QString str = QString("update %1 set password = '%2' where %3 = '%4' and password = '%5'").arg(user.getType(), ui->lineEdit_changePassword->text(), user.getIdType(), user.getID(), ui->lineEdit_password->text());
    QSqlQuery query;
    if(query.exec(str))
    {
        user.setOnline(false);
        QMessageBox::information(this, "成功", "修改密码成功");
        this->close();
    }
    else
    {
        QMessageBox::critical(this, "错误", "修改密码失败");
    }
}
