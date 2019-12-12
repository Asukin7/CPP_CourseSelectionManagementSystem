#include "managementteacher.h"
#include "ui_managementteacher.h"

ManagementTeacher::ManagementTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementTeacher)
{
    ui->setupUi(this);
    ui->pushButton_excel->setEnabled(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    on_pushButton_back_clicked();
}

ManagementTeacher::~ManagementTeacher()
{
    delete ui;
}

void ManagementTeacher::on_pushButton_search_clicked()
{
    if(!user.getPermission("teacher_search")) return;
    QString str = "";
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("tno"), ui->lineEdit_search_tno->text());
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("tname"), ui->lineEdit_search_tname->text());
    if(ui->comboBox_search_tsex->currentText() == "男")
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("tsex = '男'");
    }
    else if(ui->comboBox_search_tsex->currentText() == "女")
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("tsex = '女'");
    }
    if(!ui->lineEdit_search_tage_a->text().isEmpty())
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("tage >= %1").arg(ui->lineEdit_search_tage_a->text());
    }
    if(!ui->lineEdit_search_tage_b->text().isEmpty())
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("tage <= %1").arg(ui->lineEdit_search_tage_b->text());
    }
    if(!ui->lineEdit_search_cno->text().isEmpty())
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        str += QString("(cno1 like '%%1%' or cno2 like '%%2%' or cno3 like '%%3%')").arg(ui->lineEdit_search_cno->text(), ui->lineEdit_search_cno->text(), ui->lineEdit_search_cno->text());
    }
    if(!(ui->checkBox_search_teb->isChecked() && ui->checkBox_search_teb_2->isChecked() && ui->checkBox_search_teb_3->isChecked()))
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        QString temp = "";
        if(ui->checkBox_search_teb->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("teb = '学士'");
        }
        if(ui->checkBox_search_teb_2->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("teb = '硕士'");
        }
        if(ui->checkBox_search_teb_3->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("teb = '博士'");
        }
        str += QString("(%1)").arg(temp);
    }
    if(!(ui->checkBox_search_tpt->isChecked() && ui->checkBox_search_tpt_2->isChecked() && ui->checkBox_search_tpt_3->isChecked() && ui->checkBox_search_tpt_4->isChecked()))
    {
        str = ToolClass::QStringAdd___(str, QString("and"));
        QString temp = "";
        if(ui->checkBox_search_tpt->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("tpt = '助教'");
        }
        if(ui->checkBox_search_tpt_2->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("tpt = '讲师'");
        }
        if(ui->checkBox_search_tpt_3->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("tpt = '副教授'");
        }
        if(ui->checkBox_search_tpt_4->isChecked())
        {
            temp = ToolClass::QStringAdd___(temp, QString("or"));
            temp += QString("tpt = '教授'");
        }
        str += QString("(%1)").arg(temp);
    }
    str = ToolClass::QString___Add(str, QString("where"));
    str = QString("select tno, tname, tsex, tage, teb, tpt, cno1, cno2, cno3 from teacher") + str;

    QSqlQuery query;
    query.exec(str);
    if(!query.next())
    {
        QMessageBox::critical(this, "错误", "查询结果为空");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "教工号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "性别");
    model->setHeaderData(3, Qt::Horizontal, "年龄");
    model->setHeaderData(4, Qt::Horizontal, "学历");
    model->setHeaderData(5, Qt::Horizontal, "职称");
    model->setHeaderData(6, Qt::Horizontal, "主讲课程一");
    model->setHeaderData(7, Qt::Horizontal, "主讲课程二");
    model->setHeaderData(8, Qt::Horizontal, "主讲课程三");
    ui->tableView->setModel(model);

    ui->pushButton_excel->setEnabled(true);
}

void ManagementTeacher::on_pushButton_add_clicked()
{
    if(!user.getPermission("teacher_add")) return;
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("添加");
    ui->groupBox_data->show();
}

void ManagementTeacher::on_pushButton_delete_clicked()
{
    if(!user.getPermission("teacher_delete")) return;
    ui->lineEdit_tno->setEnabled(false);
    ui->lineEdit_tname->setEnabled(false);
    ui->comboBox_tsex->setEnabled(false);
    ui->comboBox_tage->setEnabled(false);
    ui->comboBox_teb->setEnabled(false);
    ui->comboBox_tpt->setEnabled(false);
    ui->lineEdit_cno1->setEnabled(false);
    ui->lineEdit_cno2->setEnabled(false);
    ui->lineEdit_cno3->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("删除");
    ui->groupBox_data->show();
}

void ManagementTeacher::on_pushButton_change_clicked()
{
    if(!user.getPermission("teacher_change")) return;
    ui->lineEdit_tno->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("修改");
    ui->groupBox_data->show();
}

void ManagementTeacher::on_pushButton_excel_clicked()
{
    if(!user.getPermission("teacher_excel")) return;
    ToolClass::TableToXlsx(ui->tableView->model());
}

void ManagementTeacher::on_pushButton_yes_clicked()
{
    if(ui->pushButton_yes->text() == "添加")
    {
        QString str = QString("insert into teacher (tno, tname, tsex, tage, teb, tpt, cno1, cno2, cno3) values ('%1', '%2', '%3', %4, '%5', '%6', %7, %8, %9)").arg(ui->lineEdit_tno->text(), ui->lineEdit_tname->text(), ui->comboBox_tsex->currentText(), ui->comboBox_tage->currentText(), ui->comboBox_teb->currentText(), ui->comboBox_tpt->currentText(), ToolClass::QStringChangeNULL(ui->lineEdit_cno1->text()), ToolClass::QStringChangeNULL(ui->lineEdit_cno2->text()), ToolClass::QStringChangeNULL(ui->lineEdit_cno3->text()));
        ToolClass::SQLQuery(str, "添加成功", "添加失败");
    }
    else if(ui->pushButton_yes->text() == "删除")
    {
        QString str = QString("delete from teacher where tno = '%1'").arg(ui->lineEdit_tno->text());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
    }
    else if(ui->pushButton_yes->text() == "修改")
    {
        QString str = QString("update teacher set tname = '%1', tsex = '%2', tage = '%3', teb = '%4', tpt = '%5', cno1 = %6, cno2 = %7, cno3 = %8 where tno = '%9'").arg(ui->lineEdit_tname->text(), ui->comboBox_tsex->currentText(), ui->comboBox_tage->currentText(), ui->comboBox_teb->currentText(), ui->comboBox_tpt->currentText(), ToolClass::QStringChangeNULL(ui->lineEdit_cno1->text()), ToolClass::QStringChangeNULL(ui->lineEdit_cno2->text()), ToolClass::QStringChangeNULL(ui->lineEdit_cno3->text()), ui->lineEdit_tno->text());
        ToolClass::SQLQuery(str, "修改成功", "修改失败");
    }
    else
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
    }
}

void ManagementTeacher::on_pushButton_back_clicked()
{
    ui->lineEdit_tno->setEnabled(true);
    ui->lineEdit_tname->setEnabled(true);
    ui->comboBox_tsex->setEnabled(true);
    ui->comboBox_tage->setEnabled(true);
    ui->comboBox_teb->setEnabled(true);
    ui->comboBox_tpt->setEnabled(true);
    ui->lineEdit_cno1->setEnabled(true);
    ui->lineEdit_cno2->setEnabled(true);
    ui->lineEdit_cno3->setEnabled(true);
    ui->groupBox_data->hide();
    ui->pushButton_yes->setText("yes");
    ui->groupBox_management->show();
}

void ManagementTeacher::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row,0);
    ui->lineEdit_tno->setText(model->data(index).toString());
    index = model->index(row,1);
    ui->lineEdit_tname->setText(model->data(index).toString());
    index = model->index(row,2);
    ui->comboBox_tsex->setCurrentText(model->data(index).toString());
    index = model->index(row,3);
    ui->comboBox_tage->setCurrentText(model->data(index).toString());
    index = model->index(row,4);
    ui->comboBox_teb->setCurrentText(model->data(index).toString());
    index = model->index(row,5);
    ui->comboBox_tpt->setCurrentText(model->data(index).toString());
    index = model->index(row,6);
    ui->lineEdit_cno1->setText(model->data(index).toString());
    index = model->index(row,7);
    ui->lineEdit_cno2->setText(model->data(index).toString());
    index = model->index(row,8);
    ui->lineEdit_cno3->setText(model->data(index).toString());
}
