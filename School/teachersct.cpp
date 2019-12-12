#include "teachersct.h"
#include "ui_teachersct.h"

TeacherSCT::TeacherSCT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherSCT)
{
    ui->setupUi(this);
    initialize();
}

TeacherSCT::~TeacherSCT()
{
    delete ui;
}

void TeacherSCT::initialize()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    ui->pushButton_excel->setEnabled(false);
    ui->pushButton_yes->setEnabled(false);
}

void TeacherSCT::on_pushButton_search_clicked()
{
    QString str = QString("select student.sno, student.sname, course.cno, course.cname, teacher.tno, teacher.tname, sct.grade from student, course, teacher, sct where student.sno = sct.sno and course.cno = sct.cno and teacher.tno = sct.tno and sct.cno = '%1' and sct.tno = '%2'").arg(this->windowTitle(), user.getID());

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
    model->setHeaderData(1, Qt::Horizontal, "学生名");
    model->setHeaderData(2, Qt::Horizontal, "课程号");
    model->setHeaderData(3, Qt::Horizontal, "课程名");
    model->setHeaderData(4, Qt::Horizontal, "教工号");
    model->setHeaderData(5, Qt::Horizontal, "教师名");
    model->setHeaderData(6, Qt::Horizontal, "成绩");
    ui->tableView->setModel(model);

    ui->pushButton_excel->setEnabled(true);
}

void TeacherSCT::on_pushButton_excel_clicked()
{
    ToolClass::TableToXlsx(ui->tableView->model());
}

void TeacherSCT::on_pushButton_yes_clicked()
{
    QString str = QString("update sct set grade = %1 where sno = '%2' and cno = '%3' and tno = '%4'").arg(ToolClass::QStringChangeNULL(ui->lineEdit_grade->text()), ui->lineEdit_sno->text(), ui->lineEdit_cno->text(), ui->lineEdit_tno->text());
    ToolClass::SQLQuery(str, "导入成功", "导入失败");
    on_pushButton_search_clicked();
}

void TeacherSCT::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row,0);
    ui->lineEdit_sno->setText(model->data(index).toString());
    index = model->index(row,1);
    ui->lineEdit_sname->setText(model->data(index).toString());
    index = model->index(row,2);
    ui->lineEdit_cno->setText(model->data(index).toString());
    index = model->index(row,3);
    ui->lineEdit_cname->setText(model->data(index).toString());
    index = model->index(row,4);
    ui->lineEdit_tno->setText(model->data(index).toString());
    index = model->index(row,5);
    ui->lineEdit_tname->setText(model->data(index).toString());
    index = model->index(row,6);
    ui->lineEdit_grade->setText(model->data(index).toString());

    ui->pushButton_yes->setEnabled(true);
}
