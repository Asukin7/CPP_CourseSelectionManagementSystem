#include "managementsct.h"
#include "ui_managementsct.h"

ManagementSCT::ManagementSCT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementSCT)
{
    ui->setupUi(this);
    ui->pushButton_excel->setEnabled(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    on_pushButton_back_clicked();
}

ManagementSCT::~ManagementSCT()
{
    delete ui;
}

void ManagementSCT::on_pushButton_search_clicked()
{
    if(!user.getPermission("sct_search")) return;
    QString str = "";
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("sno"), ui->lineEdit_search_sno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("cno"), ui->lineEdit_search_cno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("tno"), ui->lineEdit_search_tno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("grade"), ui->lineEdit_search_grade->text());
    str = ToolClass::QString___Add(str, QString("where"));
    str = QString("select * from sct") + str;

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
    model->setHeaderData(2, Qt::Horizontal, "教工号");
    model->setHeaderData(3, Qt::Horizontal, "成绩");
    ui->tableView->setModel(model);

    ui->pushButton_excel->setEnabled(true);
}

void ManagementSCT::on_pushButton_add_clicked()
{
    if(!user.getPermission("sct_add")) return;
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("添加");
    ui->groupBox_data->show();
}

void ManagementSCT::on_pushButton_delete_clicked()
{
    if(!user.getPermission("sct_delete")) return;
    ui->lineEdit_sno->setEnabled(false);
    ui->lineEdit_cno->setEnabled(false);
    ui->lineEdit_tno->setEnabled(false);
    ui->lineEdit_grade->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("删除");
    ui->groupBox_data->show();
}

void ManagementSCT::on_pushButton_change_clicked()
{
    if(!user.getPermission("sct_change")) return;
    ui->lineEdit_sno->setEnabled(false);
    ui->lineEdit_cno->setEnabled(false);
    ui->lineEdit_tno->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("修改");
    ui->groupBox_data->show();
}

void ManagementSCT::on_pushButton_excel_clicked()
{
    if(!user.getPermission("sct_excel")) return;
    ToolClass::TableToXlsx(ui->tableView->model());
}

void ManagementSCT::on_pushButton_yes_clicked()
{
    if(ui->pushButton_yes->text() == "添加")
    {
        QString str = QString("insert into sct (sno, cno, tno, grade) values ('%1', '%2', '%3', %4)").arg(ui->lineEdit_sno->text(), ui->lineEdit_cno->text(), ui->lineEdit_tno->text(), ToolClass::QStringChangeNULL(ui->lineEdit_grade->text()));
        ToolClass::SQLQuery(str, "添加成功", "添加失败");
    }
    else if(ui->pushButton_yes->text() == "删除")
    {
        QString str = QString("delete from sct where sno = '%1' and cno = '%2' and tno = '%3'").arg(ui->lineEdit_sno->text(), ui->lineEdit_cno->text(), ui->lineEdit_tno->text());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
    }
    else if(ui->pushButton_yes->text() == "修改")
    {
        QString str = QString("update sct set grade = %1 where sno = '%2' and cno = '%3' and tno = '%4'").arg(ToolClass::QStringChangeNULL(ui->lineEdit_grade->text()), ui->lineEdit_sno->text(), ui->lineEdit_cno->text(), ui->lineEdit_tno->text());
        ToolClass::SQLQuery(str, "修改成功", "修改失败");
    }
    else
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
    }
}

void ManagementSCT::on_pushButton_back_clicked()
{
    ui->lineEdit_sno->setEnabled(true);
    ui->lineEdit_cno->setEnabled(true);
    ui->lineEdit_tno->setEnabled(true);
    ui->lineEdit_grade->setEnabled(true);
    ui->groupBox_data->hide();
    ui->pushButton_yes->setText("yes");
    ui->groupBox_management->show();
}

void ManagementSCT::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row,0);
    ui->lineEdit_sno->setText(model->data(index).toString());
    index = model->index(row,1);
    ui->lineEdit_cno->setText(model->data(index).toString());
    index = model->index(row,2);
    ui->lineEdit_tno->setText(model->data(index).toString());
    index = model->index(row,3);
    ui->lineEdit_grade->setText(model->data(index).toString());
}
