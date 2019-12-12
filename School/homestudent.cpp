#include "homestudent.h"
#include "ui_homestudent.h"

HomeStudent::HomeStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeStudent)
{
    ui->setupUi(this);
    initialize();
}

HomeStudent::~HomeStudent()
{
    delete ui;
}

void HomeStudent::initialize()
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
    ui->label_sno->setText(query.value(rec.indexOf("sno")).toString());
    ui->label_sname->setText(query.value(rec.indexOf("sname")).toString());
    ui->label_ssex->setText(query.value(rec.indexOf("ssex")).toString());
    ui->label_sage->setText(query.value(rec.indexOf("sage")).toString());
    ui->label_sdept->setText(query.value(rec.indexOf("sdept")).toString());
}

void HomeStudent::on_pushButton_logout_clicked()
{
    user.setOnline(false);
    qApp->exit(666);
}

void HomeStudent::on_pushButton_changePassword_clicked()
{
    changePassword = new ChangePassword(this);
    changePassword->exec();
    if(!user.getOnline())
    {
        on_pushButton_logout_clicked();
    }
}

void HomeStudent::on_pushButton_addSCT_clicked()
{
    studentSCT = new StudentSCT(this);
    studentSCT->setWindowTitle("选择课程");
    studentSCT->initialize();
    studentSCT->exec();
}

void HomeStudent::on_pushButton_searchSCT_clicked()
{
    studentSCT = new StudentSCT(this);
    studentSCT->setWindowTitle("已选课程");
    studentSCT->initialize();
    studentSCT->exec();
}
