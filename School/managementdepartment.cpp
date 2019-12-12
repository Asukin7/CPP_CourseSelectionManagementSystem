#include "managementdepartment.h"
#include "ui_managementdepartment.h"

ManagementDepartment::ManagementDepartment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementDepartment)
{
    ui->setupUi(this);
    ui->pushButton_excel->setEnabled(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    on_pushButton_back_clicked();
}

ManagementDepartment::~ManagementDepartment()
{
    delete ui;
}

void ManagementDepartment::on_pushButton_search_clicked()
{
    if(!user.getPermission("department_search")) return;
    QString str = "";
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("dno"), ui->lineEdit_search_dno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("dname"), ui->lineEdit_search_dname->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("dmanager"), ui->lineEdit_search_dmanager->text());
    str = ToolClass::QString___Add(str, QString("where"));
    str = QString("select * from department") + str;

    QSqlQuery query;
    query.exec(str);
    if(!query.next())
    {
        QMessageBox::critical(this, "错误", "查询结果为空");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "系编号");
    model->setHeaderData(1, Qt::Horizontal, "系名");
    model->setHeaderData(2, Qt::Horizontal, "系主任");
    ui->tableView->setModel(model);

    ui->pushButton_excel->setEnabled(true);
}

void ManagementDepartment::on_pushButton_add_clicked()
{
    if(!user.getPermission("department_add")) return;
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("添加");
    ui->groupBox_data->show();
}

void ManagementDepartment::on_pushButton_delete_clicked()
{
    if(!user.getPermission("department_delete")) return;
    ui->lineEdit_dno->setEnabled(false);
    ui->lineEdit_dname->setEnabled(false);
    ui->lineEdit_dmanager->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("删除");
    ui->groupBox_data->show();
}

void ManagementDepartment::on_pushButton_change_clicked()
{
    if(!user.getPermission("department_change")) return;
    ui->lineEdit_dno->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("修改");
    ui->groupBox_data->show();
}

void ManagementDepartment::on_pushButton_excel_clicked()
{
    if(!user.getPermission("department_excel")) return;
    ToolClass::TableToXlsx(ui->tableView->model());
}

void ManagementDepartment::on_pushButton_yes_clicked()
{
    if(ui->pushButton_yes->text() == "添加")
    {
        QString str = QString("insert into department (dno, dname, dmanager) values ('%1', '%2', %3)").arg(ui->lineEdit_dno->text(), ui->lineEdit_dname->text(), ToolClass::QStringChangeNULL(ui->lineEdit_dmanager->text()));
        ToolClass::SQLQuery(str, "添加成功", "添加失败");
    }
    else if(ui->pushButton_yes->text() == "删除")
    {
        QString str = QString("delete from department where dno = '%1'").arg(ui->lineEdit_dno->text());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
    }
    else if(ui->pushButton_yes->text() == "修改")
    {
        QString str = QString("update department set dname = '%1', dmanager = %2 where dno = '%3'").arg(ui->lineEdit_dname->text(), ToolClass::QStringChangeNULL(ui->lineEdit_dmanager->text()), ui->lineEdit_dno->text());
        ToolClass::SQLQuery(str, "修改成功", "修改失败");
    }
    else
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
    }
}

void ManagementDepartment::on_pushButton_back_clicked()
{
    ui->lineEdit_dno->setEnabled(true);
    ui->lineEdit_dname->setEnabled(true);
    ui->lineEdit_dmanager->setEnabled(true);
    ui->groupBox_data->hide();
    ui->pushButton_yes->setText("yes");
    ui->groupBox_management->show();
}

void ManagementDepartment::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row,0);
    ui->lineEdit_dno->setText(model->data(index).toString());
    index = model->index(row,1);
    ui->lineEdit_dname->setText(model->data(index).toString());
    index = model->index(row,2);
    ui->lineEdit_dmanager->setText(model->data(index).toString());
}
