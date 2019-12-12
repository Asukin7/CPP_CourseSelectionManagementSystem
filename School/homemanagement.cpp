#include "homemanagement.h"
#include "ui_homemanagement.h"

HomeManagement::HomeManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeManagement)
{
    ui->setupUi(this);
    initialize();
}

HomeManagement::~HomeManagement()
{
    delete ui;
}

void HomeManagement::initialize()
{
    QString str = QString("select * from %1 where %2 = '%3'").arg(user.getType(), user.getIdType(), user.getID());
    QSqlQuery query;
    query.exec(str);
    if(!query.next())
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
        user.setOnline(false);
        qApp->exit(666);
        return;
    }
    QSqlRecord rec = query.record();
    ui->lineEdit_mno->setText(query.value(0).toString());
    ui->checkBox_1_1->setChecked(query.value(1).toBool());
    ui->checkBox_1_2->setChecked(query.value(2).toBool());
    ui->checkBox_1_3->setChecked(query.value(3).toBool());
    ui->checkBox_1_4->setChecked(query.value(4).toBool());
    ui->checkBox_1_5->setChecked(query.value(5).toBool());
    ui->checkBox_2_1->setChecked(query.value(6).toBool());
    ui->checkBox_2_2->setChecked(query.value(7).toBool());
    ui->checkBox_2_3->setChecked(query.value(8).toBool());
    ui->checkBox_2_4->setChecked(query.value(9).toBool());
    ui->checkBox_2_5->setChecked(query.value(10).toBool());
    ui->checkBox_3_1->setChecked(query.value(11).toBool());
    ui->checkBox_3_2->setChecked(query.value(12).toBool());
    ui->checkBox_3_3->setChecked(query.value(13).toBool());
    ui->checkBox_3_4->setChecked(query.value(14).toBool());
    ui->checkBox_3_5->setChecked(query.value(15).toBool());
    ui->checkBox_4_1->setChecked(query.value(16).toBool());
    ui->checkBox_4_2->setChecked(query.value(17).toBool());
    ui->checkBox_4_3->setChecked(query.value(18).toBool());
    ui->checkBox_4_4->setChecked(query.value(19).toBool());
    ui->checkBox_4_5->setChecked(query.value(20).toBool());
    ui->checkBox_5_1->setChecked(query.value(21).toBool());
    ui->checkBox_5_2->setChecked(query.value(22).toBool());
    ui->checkBox_5_3->setChecked(query.value(23).toBool());
    ui->checkBox_5_4->setChecked(query.value(24).toBool());
    ui->checkBox_5_5->setChecked(query.value(25).toBool());
    ui->checkBox_6_1->setChecked(query.value(26).toBool());
    ui->checkBox_6_2->setChecked(query.value(27).toBool());
    ui->checkBox_6_3->setChecked(query.value(28).toBool());
    ui->checkBox_6_4->setChecked(query.value(29).toBool());
    ui->checkBox_6_5->setChecked(query.value(30).toBool());
}

void HomeManagement::on_pushButton_logout_clicked()
{
    user.setOnline(false);
    qApp->exit(666);
}

void HomeManagement::on_pushButton_changePassword_clicked()
{
    changePassword = new ChangePassword(this);
    changePassword->exec();
    if(!user.getOnline())
    {
        on_pushButton_logout_clicked();
    }
}

void HomeManagement::on_pushButton_search_clicked()
{
    initialize();
}
