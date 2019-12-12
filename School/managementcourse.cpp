#include "managementcourse.h"
#include "ui_managementcourse.h"

ManagementCourse::ManagementCourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementCourse)
{
    ui->setupUi(this);
    ui->pushButton_excel->setEnabled(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    on_pushButton_back_clicked();
}

ManagementCourse::~ManagementCourse()
{
    delete ui;
}

void ManagementCourse::on_pushButton_search_clicked()
{
    if(!user.getPermission("course_search")) return;
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

    ui->pushButton_excel->setEnabled(true);
}

void ManagementCourse::on_pushButton_add_clicked()
{
    if(!user.getPermission("course_add")) return;
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("添加");
    ui->groupBox_data->show();
}

void ManagementCourse::on_pushButton_delete_clicked()
{
    if(!user.getPermission("course_delete")) return;
    ui->lineEdit_cno->setEnabled(false);
    ui->lineEdit_cname->setEnabled(false);
    ui->lineEdit_cpno->setEnabled(false);
    ui->lineEdit_ccredit->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("删除");
    ui->groupBox_data->show();
}

void ManagementCourse::on_pushButton_change_clicked()
{
    if(!user.getPermission("course_change")) return;
    ui->lineEdit_cno->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("修改");
    ui->groupBox_data->show();
}

void ManagementCourse::on_pushButton_excel_clicked()
{
    if(!user.getPermission("course_excel")) return;
    ToolClass::TableToXlsx(ui->tableView->model());
}

void ManagementCourse::on_pushButton_yes_clicked()
{
    if(ui->pushButton_yes->text() == "添加")
    {
        QString str = QString("insert into course (cno, cname, cpno, ccredit) values ('%1', '%2', %3, %4)").arg(ui->lineEdit_cno->text(), ui->lineEdit_cname->text(), ToolClass::QStringChangeNULL(ui->lineEdit_cpno->text()), ui->lineEdit_ccredit->text());
        ToolClass::SQLQuery(str, "添加成功", "添加失败");
    }
    else if(ui->pushButton_yes->text() == "删除")
    {
        QString str = QString("delete from course where cno = '%1'").arg(ui->lineEdit_cno->text());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
    }
    else if(ui->pushButton_yes->text() == "修改")
    {
        QString str = QString("update course set cname = '%1', cpno = %2, ccredit = %3 where cno = '%4'").arg(ui->lineEdit_cname->text(), ToolClass::QStringChangeNULL(ui->lineEdit_cpno->text()), ui->lineEdit_ccredit->text(), ui->lineEdit_cno->text());
        ToolClass::SQLQuery(str, "修改成功", "修改失败");
    }
    else
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
    }
}

void ManagementCourse::on_pushButton_back_clicked()
{
    ui->lineEdit_cno->setEnabled(true);
    ui->lineEdit_cname->setEnabled(true);
    ui->lineEdit_cpno->setEnabled(true);
    ui->lineEdit_ccredit->setEnabled(true);
    ui->groupBox_data->hide();
    ui->pushButton_yes->setText("yes");
    ui->groupBox_management->show();
}

void ManagementCourse::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row,0);
    ui->lineEdit_cno->setText(model->data(index).toString());
    index = model->index(row,1);
    ui->lineEdit_cname->setText(model->data(index).toString());
    index = model->index(row,2);
    ui->lineEdit_cpno->setText(model->data(index).toString());
    index = model->index(row,3);
    ui->lineEdit_ccredit->setText(model->data(index).toString());
}
