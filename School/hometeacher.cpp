#include "hometeacher.h"
#include "ui_hometeacher.h"

HomeTeacher::HomeTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeTeacher)
{
    ui->setupUi(this);
    initialize();
}

HomeTeacher::~HomeTeacher()
{
    delete ui;
}

void HomeTeacher::initialize()
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
    ui->label_tno->setText(query.value(rec.indexOf("tno")).toString());
    ui->label_tname->setText(query.value(rec.indexOf("tname")).toString());
    ui->label_tsex->setText(query.value(rec.indexOf("tsex")).toString());
    ui->label_tage->setText(query.value(rec.indexOf("tage")).toString());
    ui->label_teb->setText(query.value(rec.indexOf("teb")).toString());
    ui->label_tpt->setText(query.value(rec.indexOf("tpt")).toString());
    ui->label_cno1->setText(query.value(rec.indexOf("cno1")).toString());
    ui->label_cno2->setText(query.value(rec.indexOf("cno2")).toString());
    ui->label_cno3->setText(query.value(rec.indexOf("cno3")).toString());
    if(ui->label_cno1->text().isEmpty())
    {
        ui->pushButton_cno1_addChange->setText("添加");
        ui->pushButton_cno1_delete->setEnabled(false);
        ui->pushButton_cno1->setEnabled(false);
    }
    else
    {
        ui->pushButton_cno1_addChange->setText("修改");
        ui->pushButton_cno1_delete->setEnabled(true);
        ui->pushButton_cno1->setEnabled(true);
    }
    if(ui->label_cno2->text().isEmpty())
    {
        ui->pushButton_cno2_addChange->setText("添加");
        ui->pushButton_cno2_delete->setEnabled(false);
        ui->pushButton_cno2->setEnabled(false);
    }
    else
    {
        ui->pushButton_cno2_addChange->setText("修改");
        ui->pushButton_cno2_delete->setEnabled(true);
        ui->pushButton_cno2->setEnabled(true);
    }
    if(ui->label_cno3->text().isEmpty())
    {
        ui->pushButton_cno3_addChange->setText("添加");
        ui->pushButton_cno3_delete->setEnabled(false);
        ui->pushButton_cno3->setEnabled(false);
    }
    else
    {
        ui->pushButton_cno3_addChange->setText("修改");
        ui->pushButton_cno3_delete->setEnabled(true);
        ui->pushButton_cno3->setEnabled(true);
    }
}

void HomeTeacher::on_pushButton_logout_clicked()
{
    user.setOnline(false);
    qApp->exit(666);
}

void HomeTeacher::on_pushButton_changePassword_clicked()
{
    changePassword = new ChangePassword(this);
    changePassword->exec();
    if(!user.getOnline())
    {
        on_pushButton_logout_clicked();
    }
}

void HomeTeacher::on_pushButton_cno1_addChange_clicked()
{
    teacherCourse = new TeacherCourse(this);
    if(ui->pushButton_cno1_addChange->text() == "添加")
    {
        teacherCourse->setWindowTitle("添加主讲课程一");
    }
    else if(ui->pushButton_cno1_addChange->text() == "修改")
    {
        QSqlQuery query;
        query.exec(QString("select * from sct where sct.cno = '%1' and sct.tno = '%2' and sct.grade is NULL").arg(ui->label_cno1->text(), user.getID()));
        if(query.next())
        {
            QMessageBox::critical(this, "失败", "存在已选该课程且未录入成绩的学生\n不可修改该课程");
            return;
        }
        teacherCourse->setWindowTitle("修改主讲课程一");
    }
    teacherCourse->initialize();
    teacherCourse->exec();
    initialize();
}

void HomeTeacher::on_pushButton_cno2_addChange_clicked()
{
    teacherCourse = new TeacherCourse(this);
    if(ui->pushButton_cno2_addChange->text() == "添加")
    {
        teacherCourse->setWindowTitle("添加主讲课程二");
    }
    else if(ui->pushButton_cno2_addChange->text() == "修改")
    {
        QSqlQuery query;
        query.exec(QString("select * from sct where sct.cno = '%1' and sct.tno = '%2' and sct.grade is NULL").arg(ui->label_cno2->text(), user.getID()));
        if(query.next())
        {
            QMessageBox::critical(this, "失败", "存在已选该课程且未录入成绩的学生\n不可修改该课程");
            return;
        }
        teacherCourse->setWindowTitle("修改主讲课程二");
    }
    teacherCourse->initialize();
    teacherCourse->exec();
    initialize();
}

void HomeTeacher::on_pushButton_cno3_addChange_clicked()
{
    teacherCourse = new TeacherCourse(this);
    if(ui->pushButton_cno3_addChange->text() == "添加")
    {
        teacherCourse->setWindowTitle("添加主讲课程三");
    }
    else if(ui->pushButton_cno3_addChange->text() == "修改")
    {
        QSqlQuery query;
        query.exec(QString("select * from sct where sct.cno = '%1' and sct.tno = '%2' and sct.grade is NULL").arg(ui->label_cno3->text(), user.getID()));
        if(query.next())
        {
            QMessageBox::critical(this, "失败", "存在已选该课程且未录入成绩的学生\n不可修改该课程");
            return;
        }
        teacherCourse->setWindowTitle("修改主讲课程三");
    }
    teacherCourse->initialize();
    teacherCourse->exec();
    initialize();
}

void HomeTeacher::on_pushButton_cno1_delete_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from sct where sct.cno = '%1' and sct.tno = '%2' and sct.grade is NULL").arg(ui->label_cno1->text(), user.getID()));
    if(query.next())
    {
        QMessageBox::critical(this, "失败", "存在已选该课程且未录入成绩的学生\n不可删除该课程");
        return;
    }
    QMessageBox messageBox(QMessageBox::NoIcon,"删除课程",QString("确定删除课程"),QMessageBox::Yes|QMessageBox::No);
    int result=messageBox.exec();
    switch (result)
    {
    case QMessageBox::Yes:
    {
        QString str = QString("update teacher set cno1 = null where tno = '%1'").arg(user.getID());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
        break;
    }
    case QMessageBox::No:
    {
        return;
    }
    default:break;
    }
    initialize();
}

void HomeTeacher::on_pushButton_cno2_delete_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from sct where sct.cno = '%1' and sct.tno = '%2' and sct.grade is NULL").arg(ui->label_cno2->text(), user.getID()));
    if(query.next())
    {
        QMessageBox::critical(this, "失败", "存在已选该课程且未录入成绩的学生\n不可删除该课程");
        return;
    }
    QMessageBox messageBox(QMessageBox::NoIcon,"删除课程",QString("确定删除课程"),QMessageBox::Yes|QMessageBox::No);
    int result=messageBox.exec();
    switch (result)
    {
    case QMessageBox::Yes:
    {
        QString str = QString("update teacher set cno2 = null where tno = '%1'").arg(user.getID());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
        break;
    }
    case QMessageBox::No:
    {
        return;
    }
    default:break;
    }
    initialize();
}

void HomeTeacher::on_pushButton_cno3_delete_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from sct where sct.cno = '%1' and sct.tno = '%2' and sct.grade is NULL").arg(ui->label_cno3->text(), user.getID()));
    if(query.next())
    {
        QMessageBox::critical(this, "失败", "存在已选该课程且未录入成绩的学生\n不可删除该课程");
        return;
    }
    QMessageBox messageBox(QMessageBox::NoIcon,"删除课程",QString("确定删除课程"),QMessageBox::Yes|QMessageBox::No);
    int result=messageBox.exec();
    switch (result)
    {
    case QMessageBox::Yes:
    {
        QString str = QString("update teacher set cno3 = null where tno = '%1'").arg(user.getID());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
        break;
    }
    case QMessageBox::No:
    {
        return;
    }
    default:break;
    }
    initialize();
}

void HomeTeacher::on_pushButton_cno1_clicked()
{
    teacherSCT = new TeacherSCT(this);
    teacherSCT->setWindowTitle(ui->label_cno1->text());
    teacherSCT->initialize();
    teacherSCT->exec();
    initialize();
}

void HomeTeacher::on_pushButton_cno2_clicked()
{
    teacherSCT = new TeacherSCT(this);
    teacherSCT->setWindowTitle(ui->label_cno2->text());
    teacherSCT->initialize();
    teacherSCT->exec();
    initialize();
}

void HomeTeacher::on_pushButton_cno3_clicked()
{
    teacherSCT = new TeacherSCT(this);
    teacherSCT->setWindowTitle(ui->label_cno3->text());
    teacherSCT->initialize();
    teacherSCT->exec();
    initialize();
}
