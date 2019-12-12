#include "studentsct.h"
#include "ui_studentsct.h"

StudentSCT::StudentSCT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentSCT)
{
    ui->setupUi(this);
    initialize();
}

StudentSCT::~StudentSCT()
{
    delete ui;
}

void StudentSCT::initialize()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    ui->pushButton->setEnabled(false);
    if(this->windowTitle() == "选择课程")
    {
        ui->pushButton->setText("选择");
    }
    if(this->windowTitle() == "已选课程")
    {
        ui->pushButton->setText("打印");
    }
}

void StudentSCT::on_pushButton_search_clicked()
{
    if(this->windowTitle() == "选择课程")
    {
        QString str = QString(" where (course.cno = teacher.cno1 or course.cno = teacher.cno2 or course.cno = teacher.cno3) ");
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cno"), ui->lineEdit_search_cno->text());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cname"), ui->lineEdit_search_cname->text());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cpno"), ui->lineEdit_search_cpno->text());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("ccredit"), ui->lineEdit_search_ccredit->text());
        str = QString("select course.cno, course.cname, teacher.tno, teacher.tname, course.cpno, course.ccredit from course, teacher") + str;

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
        model->setHeaderData(2, Qt::Horizontal, "教工号");
        model->setHeaderData(3, Qt::Horizontal, "教师名");
        model->setHeaderData(4, Qt::Horizontal, "先行课程号");
        model->setHeaderData(5, Qt::Horizontal, "学分");
        ui->tableView->setModel(model);
    }
    if(this->windowTitle() == "已选课程")
    {
        QString str = QString(" where sct.sno = '%1' and sct.cno = course.cno and sct.tno = teacher.tno ").arg(user.getID());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cno"), ui->lineEdit_search_cno->text());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cname"), ui->lineEdit_search_cname->text());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cpno"), ui->lineEdit_search_cpno->text());
        str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("ccredit"), ui->lineEdit_search_ccredit->text());
        str = QString("select sct.sno, course.cno, course.cname, teacher.tno, teacher.tname, course.cpno, course.ccredit, sct.grade from course, teacher, sct") + str;

        QSqlQuery query;
        query.exec(str);
        if(!query.next())
        {
            QMessageBox::critical(this, "错误", "查询结果为空");
            return;
        }

        QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, "学号");
        model->setHeaderData(1, Qt::Horizontal, "课程号");
        model->setHeaderData(2, Qt::Horizontal, "课程名");
        model->setHeaderData(3, Qt::Horizontal, "教工号");
        model->setHeaderData(4, Qt::Horizontal, "教师名");
        model->setHeaderData(5, Qt::Horizontal, "先行课程号");
        model->setHeaderData(6, Qt::Horizontal, "学分");
        model->setHeaderData(7, Qt::Horizontal, "分数");
        ui->tableView->setModel(model);

        ui->pushButton->setEnabled(true);
    }
}

void StudentSCT::on_pushButton_clicked()
{
    if(this->windowTitle() == "选择课程")
    {
        QAbstractItemModel *model = ui->tableView->model();
        int row = ui->tableView->currentIndex().row();
        QString cno = model->data(model->index(row,0)).toString();
        QString tno = model->data(model->index(row,2)).toString();
        QMessageBox messageBox(QMessageBox::NoIcon,"选择课程",QString("选择课程\n课程号：%1\n教工号：%2").arg(cno, tno),QMessageBox::Yes|QMessageBox::No);
        int result=messageBox.exec();
        switch (result)
        {
        case QMessageBox::Yes:
        {
            QString str = QString("insert into sct (sno, cno, tno) values ('%1', '%2', '%3')").arg(user.getID(), cno, tno);
            ToolClass::SQLQuery(str, "选择成功", "选择失败");
            break;
        }
        case QMessageBox::No:
        {
            return;
        }
        default:break;
        }
    }
    if(this->windowTitle() == "已选课程")
    {
        ToolClass::TableToXlsx(ui->tableView->model());
    }
}

void StudentSCT::on_tableView_clicked()
{
    if(this->windowTitle() == "选择课程")
    {
        ui->pushButton->setEnabled(true);
    }
}
