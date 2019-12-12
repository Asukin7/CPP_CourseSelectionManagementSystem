#include "teachercourse.h"
#include "ui_teachercourse.h"

TeacherCourse::TeacherCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherCourse)
{
    ui->setupUi(this);
    initialize();
}

TeacherCourse::~TeacherCourse()
{
    delete ui;
}

void TeacherCourse::initialize()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    ui->pushButton->setEnabled(false);
}

void TeacherCourse::on_pushButton_search_clicked()
{
    QString str = "";
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cno"), ui->lineEdit_search_cno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cname"), ui->lineEdit_search_cname->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cpno"), ui->lineEdit_search_cpno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("ccredit"), ui->lineEdit_search_ccredit->text());
    str = ToolClass::QString___Add(str, QString("where"));
    str = QString("select * from course") + str;

    QSqlQuery query;
    query.exec(str);
    if(!query.next())
    {
        QMessageBox::critical(this, "错误", "查询结果为空");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "课程号");
    model->setHeaderData(1, Qt::Horizontal, "课程名");
    model->setHeaderData(2, Qt::Horizontal, "先行课程名");
    model->setHeaderData(3, Qt::Horizontal, "学分");
    ui->tableView->setModel(model);
}

void TeacherCourse::on_pushButton_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    int row = ui->tableView->currentIndex().row();
    QString cno = model->data(model->index(row,0)).toString();
    QMessageBox messageBox(QMessageBox::NoIcon,"选择课程",QString("选择课程\n课程号：%1").arg(cno),QMessageBox::Yes|QMessageBox::No);
    int result=messageBox.exec();
    switch (result)
    {
    case QMessageBox::Yes:
    {
        QString cnoType;
        if(this->windowTitle().mid(6,1) == "一")
        {
            cnoType = "cno1";
        }
        else if(this->windowTitle().mid(6,1) == "二")
        {
            cnoType = "cno2";
        }
        else if(this->windowTitle().mid(6,1) == "三")
        {
            cnoType = "cno3";
        }
        QString str = QString("update teacher set %1 = '%2' where tno = '%3'").arg(cnoType, cno, user.getID());
        ToolClass::SQLQuery(str, QString("%1成功").arg(this->windowTitle().left(2)), QString("%1失败").arg(this->windowTitle().left(2)));
        break;
    }
    case QMessageBox::No:
    {
        return;
    }
    default:break;
    }
}

void TeacherCourse::on_tableView_clicked()
{
    ui->pushButton->setEnabled(true);
}
