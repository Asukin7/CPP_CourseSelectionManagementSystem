#include "managementaccount.h"
#include "ui_managementaccount.h"

ManagementAccount::ManagementAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementAccount)
{
    ui->setupUi(this);
    ui->pushButton_excel->setEnabled(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选择行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单选
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度拉长
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置列宽度根据内容自适应
    on_pushButton_back_clicked();
}

ManagementAccount::~ManagementAccount()
{
    delete ui;
}

void ManagementAccount::on_pushButton_search_clicked()
{
    if(!user.getPermission("management_search")) return;
    QString str = "";
    str = ToolClass::SQLSearchWhereWhatLikeValue(str, QString("and"), QString("mno"), ui->lineEdit_search_mno->text());
    str = ToolClass::QString___Add(str, QString("where"));
    str = QString("select mno, student_search, student_add, student_delete, student_change, student_excel, teacher_search, teacher_add, teacher_delete, teacher_change, teacher_excel, course_search, course_add, course_delete, course_change, course_excel, department_search, department_add, department_delete, department_change, department_excel, sct_search, sct_add, sct_delete,sct_change, sct_excel, management_search, management_add, management_delete, management_change, management_excel from management") + str;

    QSqlQuery query;
    query.exec(str);
    if(!query.next())
    {
        QMessageBox::critical(this, "错误", "查询结果为空");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(query);
    ui->tableView->setModel(model);

    ui->pushButton_excel->setEnabled(true);
}

void ManagementAccount::on_pushButton_add_clicked()
{
    if(!user.getPermission("management_add")) return;
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("添加");
    ui->groupBox_data->show();
}

void ManagementAccount::on_pushButton_delete_clicked()
{
    if(!user.getPermission("management_delete")) return;
    ui->lineEdit_mno->setEnabled(false);
    ui->checkBox_1_1->setEnabled(false); ui->checkBox_1_2->setEnabled(false); ui->checkBox_1_3->setEnabled(false); ui->checkBox_1_4->setEnabled(false); ui->checkBox_1_5->setEnabled(false);
    ui->checkBox_2_1->setEnabled(false); ui->checkBox_2_2->setEnabled(false); ui->checkBox_2_3->setEnabled(false); ui->checkBox_2_4->setEnabled(false); ui->checkBox_2_5->setEnabled(false);
    ui->checkBox_3_1->setEnabled(false); ui->checkBox_3_2->setEnabled(false); ui->checkBox_3_3->setEnabled(false); ui->checkBox_3_4->setEnabled(false); ui->checkBox_3_5->setEnabled(false);
    ui->checkBox_4_1->setEnabled(false); ui->checkBox_4_2->setEnabled(false); ui->checkBox_4_3->setEnabled(false); ui->checkBox_4_4->setEnabled(false); ui->checkBox_4_5->setEnabled(false);
    ui->checkBox_5_1->setEnabled(false); ui->checkBox_5_2->setEnabled(false); ui->checkBox_5_3->setEnabled(false); ui->checkBox_5_4->setEnabled(false); ui->checkBox_5_5->setEnabled(false);
    ui->checkBox_6_1->setEnabled(false); ui->checkBox_6_2->setEnabled(false); ui->checkBox_6_3->setEnabled(false); ui->checkBox_6_4->setEnabled(false); ui->checkBox_6_5->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("删除");
    ui->groupBox_data->show();
}

void ManagementAccount::on_pushButton_change_clicked()
{
    if(!user.getPermission("management_change")) return;
    ui->lineEdit_mno->setEnabled(false);
    ui->groupBox_management->hide();
    ui->pushButton_yes->setText("修改");
    ui->groupBox_data->show();
}

void ManagementAccount::on_pushButton_excel_clicked()
{
    if(!user.getPermission("management_excel")) return;
    ToolClass::TableToXlsx(ui->tableView->model());
}

void ManagementAccount::on_pushButton_yes_clicked()
{
    if(ui->pushButton_yes->text() == "添加")
    {
        QString str = QString("insert into management (mno, student_search, student_add, student_delete, student_change, student_excel, teacher_search, teacher_add, teacher_delete, teacher_change, teacher_excel, course_search, course_add, course_delete, course_change, course_excel, department_search, department_add, department_delete, department_change, department_excel, sct_search, sct_add, sct_delete,sct_change, sct_excel, management_search, management_add, management_delete, management_change, management_excel) values ('%1', ").arg(ui->lineEdit_mno->text())
                + QString("'%1', '%2', '%3', '%4', '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_1_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_5->isChecked()))
                + QString("'%1', '%2', '%3', '%4', '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_2_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_5->isChecked()))
                + QString("'%1', '%2', '%3', '%4', '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_3_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_5->isChecked()))
                + QString("'%1', '%2', '%3', '%4', '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_4_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_5->isChecked()))
                + QString("'%1', '%2', '%3', '%4', '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_5_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_5->isChecked()))
                + QString("'%1', '%2', '%3', '%4', '%5')").arg(ToolClass::BoolToQString(ui->checkBox_6_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_5->isChecked()));
        ToolClass::SQLQuery(str, "添加成功", "添加失败");
    }
    else if(ui->pushButton_yes->text() == "删除")
    {
        QString str = QString("delete from management where mno = '%1'").arg(ui->lineEdit_mno->text());
        ToolClass::SQLQuery(str, "删除成功", "删除失败");
    }
    else if(ui->pushButton_yes->text() == "修改")
    {
        QString str = QString("update management set ")
                + QString("student_search = '%1', student_add = '%2', student_delete = '%3', student_change = '%4', student_excel = '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_1_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_1_5->isChecked()))
                + QString("teacher_search = '%1', teacher_add = '%2', teacher_delete = '%3', teacher_change = '%4', teacher_excel = '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_2_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_2_5->isChecked()))
                + QString("course_search = '%1', course_add = '%2', course_delete = '%3', course_change = '%4', course_excel = '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_3_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_3_5->isChecked()))
                + QString("department_search = '%1', department_add = '%2', department_delete = '%3', department_change = '%4', department_excel = '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_4_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_4_5->isChecked()))
                + QString("sct_search = '%1', sct_add = '%2', sct_delete = '%3', sct_change = '%4', sct_excel = '%5', ").arg(ToolClass::BoolToQString(ui->checkBox_5_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_5_5->isChecked()))
                + QString("management_search = '%1', management_add = '%2', management_delete = '%3', management_change = '%4', management_excel = '%5' ").arg(ToolClass::BoolToQString(ui->checkBox_6_1->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_2->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_3->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_4->isChecked()), ToolClass::BoolToQString(ui->checkBox_6_5->isChecked()))
                + QString("where mno = '%1'").arg(ui->lineEdit_mno->text());
        ToolClass::SQLQuery(str, "修改成功", "修改失败");
    }
    else
    {
        QMessageBox::critical(this, "错误", "发生未知错误");
    }
}

void ManagementAccount::on_pushButton_back_clicked()
{
    ui->lineEdit_mno->setEnabled(true);
    ui->checkBox_1_1->setEnabled(true); ui->checkBox_1_2->setEnabled(true); ui->checkBox_1_3->setEnabled(true); ui->checkBox_1_4->setEnabled(true); ui->checkBox_1_5->setEnabled(true);
    ui->checkBox_2_1->setEnabled(true); ui->checkBox_2_2->setEnabled(true); ui->checkBox_2_3->setEnabled(true); ui->checkBox_2_4->setEnabled(true); ui->checkBox_2_5->setEnabled(true);
    ui->checkBox_3_1->setEnabled(true); ui->checkBox_3_2->setEnabled(true); ui->checkBox_3_3->setEnabled(true); ui->checkBox_3_4->setEnabled(true); ui->checkBox_3_5->setEnabled(true);
    ui->checkBox_4_1->setEnabled(true); ui->checkBox_4_2->setEnabled(true); ui->checkBox_4_3->setEnabled(true); ui->checkBox_4_4->setEnabled(true); ui->checkBox_4_5->setEnabled(true);
    ui->checkBox_5_1->setEnabled(true); ui->checkBox_5_2->setEnabled(true); ui->checkBox_5_3->setEnabled(true); ui->checkBox_5_4->setEnabled(true); ui->checkBox_5_5->setEnabled(true);
    ui->checkBox_6_1->setEnabled(true); ui->checkBox_6_2->setEnabled(true); ui->checkBox_6_3->setEnabled(true); ui->checkBox_6_4->setEnabled(true); ui->checkBox_6_5->setEnabled(true);
    ui->groupBox_data->hide();
    ui->pushButton_yes->setText("yes");
    ui->groupBox_management->show();
}

void ManagementAccount::on_tableView_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex index;
    int row = ui->tableView->currentIndex().row();
    index = model->index(row, 0); ui->lineEdit_mno->setText(model->data(index).toString());
    index = model->index(row, 1); ui->checkBox_1_1->setChecked(model->data(index).toBool());
    index = model->index(row, 2); ui->checkBox_1_2->setChecked(model->data(index).toBool());
    index = model->index(row, 3); ui->checkBox_1_3->setChecked(model->data(index).toBool());
    index = model->index(row, 4); ui->checkBox_1_4->setChecked(model->data(index).toBool());
    index = model->index(row, 5); ui->checkBox_1_5->setChecked(model->data(index).toBool());
    index = model->index(row, 6); ui->checkBox_2_1->setChecked(model->data(index).toBool());
    index = model->index(row, 7); ui->checkBox_2_2->setChecked(model->data(index).toBool());
    index = model->index(row, 8); ui->checkBox_2_3->setChecked(model->data(index).toBool());
    index = model->index(row, 9); ui->checkBox_2_4->setChecked(model->data(index).toBool());
    index = model->index(row, 10); ui->checkBox_2_5->setChecked(model->data(index).toBool());
    index = model->index(row, 11); ui->checkBox_3_1->setChecked(model->data(index).toBool());
    index = model->index(row, 12); ui->checkBox_3_2->setChecked(model->data(index).toBool());
    index = model->index(row, 13); ui->checkBox_3_3->setChecked(model->data(index).toBool());
    index = model->index(row, 14); ui->checkBox_3_4->setChecked(model->data(index).toBool());
    index = model->index(row, 15); ui->checkBox_3_5->setChecked(model->data(index).toBool());
    index = model->index(row, 16); ui->checkBox_4_1->setChecked(model->data(index).toBool());
    index = model->index(row, 17); ui->checkBox_4_2->setChecked(model->data(index).toBool());
    index = model->index(row, 18); ui->checkBox_4_3->setChecked(model->data(index).toBool());
    index = model->index(row, 19); ui->checkBox_4_4->setChecked(model->data(index).toBool());
    index = model->index(row, 20); ui->checkBox_4_5->setChecked(model->data(index).toBool());
    index = model->index(row, 21); ui->checkBox_5_1->setChecked(model->data(index).toBool());
    index = model->index(row, 22); ui->checkBox_5_2->setChecked(model->data(index).toBool());
    index = model->index(row, 23); ui->checkBox_5_3->setChecked(model->data(index).toBool());
    index = model->index(row, 24); ui->checkBox_5_4->setChecked(model->data(index).toBool());
    index = model->index(row, 25); ui->checkBox_5_5->setChecked(model->data(index).toBool());
    index = model->index(row, 26); ui->checkBox_6_1->setChecked(model->data(index).toBool());
    index = model->index(row, 27); ui->checkBox_6_2->setChecked(model->data(index).toBool());
    index = model->index(row, 28); ui->checkBox_6_3->setChecked(model->data(index).toBool());
    index = model->index(row, 29); ui->checkBox_6_4->setChecked(model->data(index).toBool());
    index = model->index(row, 30); ui->checkBox_6_5->setChecked(model->data(index).toBool());
}
