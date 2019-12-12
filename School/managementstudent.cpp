#include "managementstudent.h"
#include "ui_managementstudent.h"

ManagementStudent::ManagementStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementStudent)
{
    ui->setupUi(this);
    ui->pushButton_excel->setEnabled(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    on_pushButton_back_clicked();
}

ManagementStudent::~ManagementStudent()
{
    delete ui;
}

void ManagementStudent::on_pushButton_search_clicked()
{
    if(!user.getPermission("student_search")) return;
    QString str = "";
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("sno"), ui->lineEdit_search_sno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("sname"), ui->lineEdit_search_sname->text());
    if(ui->comboBox_search_ssex->currentText() == "男")
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("ssex = '男'");
    }
    else if(ui->comboBox_search_ssex->currentText() == "女")
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("ssex = '女'");
    }
    if(!ui->lineEdit_search_sage_a->text().isEmpty())
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("sage >= %1").arg(ui->lineEdit_search_sage_a->text());
    }
    if(!ui->lineEdit_search_sage_b->text().isEmpty())
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("sage <= %1").arg(ui->lineEdit_search_sage_b->text());
    }
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("sdept"), ui->lineEdit_search_sdept->text());
    str = ToolClass::QString___Add(str, QString("where"));
    str = QString("select sno, sname, ssex, sage, sdept from student") + str;

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
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "性别");
    model->setHeaderData(3, Qt::Horizontal, "年龄");
    model->setHeaderData(4, Qt::Horizontal, "系别");
    ui->tableView->setModel(model);

    ui->pushButton_excel->setEnabled(true);
}

void ManagementStudent::on_pushButton_add_clicked()
{
    if(!user.getPermission("student_add")) return;
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("添加");
    ui->groupBox_data->show();
}

void ManagementStudent::on_pushButton_delete_clicked()
{
    if(!user.getPermission("student_delete")) return;
    ui->lineEdit_sno->setEnabled(false);
    ui->lineEdit_sname->setEnabled(false);
    ui->comboBox_ssex->setEnabled(false);
    ui->comboBox_sage->setEnabled(false);
    ui->lineEdit_sdept->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("删除");
    ui->groupBox_data->show();
}

void ManagementStudent::on_pushButton_change_clicked()
{
    if(!user.getPermission("student_change")) return;
    ui->lineEdit_sno->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("修改");
    ui->groupBox_data->show();
}

void ManagementStudent::on_pushButton_excel_clicked()
{
    if(!user.getPermission("student_excel")) return;
    ToolClass::TableToXlsx(ui->tableView->model());
}

void ManagementStudent::on_pushButton_yes_clicked()
{
    if(ui->pushButton_yes->text() == "添加")
    {
        QString str = QString("insert into student (sno, sname, ssex, sage, sdept) values ('%1', '%2', '%3', %4, '%5')").arg(ui->lineEdit_sno->text(), ui->lineEdit_sname->text(), ui->comboBox_ssex->currentText(), ui->comboBox_sage->currentText(), ui->lineEdit_sdept->text());
        ToolClass::SQLQuery(str, "添加成功", "添加失败");
    }
    else if(ui->pushButton_yes->text() == "删除")
    {
        QString str = QString("delete from student where sno = '%1'").arg(ui->lineEdit_sno->text());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
    }
    else if(ui->pushButton_yes->text() == "修改")
    {
        QString str = QString("update student set sname = '%1', ssex = '%2', sage = '%3', sdept = '%4' where sno = '%5'").arg(ui->lineEdit_sname->text(), ui->comboBox_ssex->currentText(), ui->comboBox_sage->currentText(), ui->lineEdit_sdept->text(), ui->lineEdit_sno->text());
        ToolClass::SQLQuery(str, "修改成功", "修改失败");
    }
    else
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
    }
}

void ManagementStudent::on_pushButton_back_clicked()
{
    ui->lineEdit_sno->setEnabled(true);
    ui->lineEdit_sname->setEnabled(true);
    ui->comboBox_ssex->setEnabled(true);
    ui->comboBox_sage->setEnabled(true);
    ui->lineEdit_sdept->setEnabled(true);
    ui->groupBox_data->hide();
    ui->pushButton_yes->setText("yes");
    ui->groupBox_management->show();
}

void ManagementStudent::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row,0);
    ui->lineEdit_sno->setText(model->data(index).toString());
    index = model->index(row,1);
    ui->lineEdit_sname->setText(model->data(index).toString());
    index = model->index(row,2);
    ui->comboBox_ssex->setCurrentText(model->data(index).toString());
    index = model->index(row,3);
    ui->comboBox_sage->setCurrentText(model->data(index).toString());
    index = model->index(row,4);
    ui->lineEdit_sdept->setText(model->data(index).toString());
}
