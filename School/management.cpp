#include "management.h"
#include "ui_management.h"

Management::Management(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Management)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

Management::~Management()
{
    delete ui;
}

void Management::initialize()
{
    this->hide();
    Login l;
    l.exec();
    if(user.getOnline())
    {
        if(user.getType() == "student")
        {
            this->setWindowTitle("学生信息管理");
            homeStudent = new HomeStudent(this);
            ui->tabWidget->insertTab(0,homeStudent,"");
            ui->tabWidget->setStyleSheet("QTabBar::tab {width: 0px; height: 0px;}");
        }
        else if(user.getType() == "teacher")
        {
            this->setWindowTitle("教师信息管理");
            homeTeacher = new HomeTeacher(this);
            ui->tabWidget->insertTab(0,homeTeacher,"");
            ui->tabWidget->setStyleSheet("QTabBar::tab {width: 0px; height: 0px;}");
        }
        else if(user.getType() == "management")
        {
            this->setWindowTitle("选课信息管理系统");
            homeManagement = new HomeManagement(this);
            managementStudent = new ManagementStudent(this);
            managementTeacher = new ManagementTeacher(this);
            managementCourse = new ManagementCourse(this);
            managementDepartment = new ManagementDepartment(this);
            managementSCT = new ManagementSCT(this);
            managementAccount = new ManagementAccount(this);
            ui->tabWidget->insertTab(0,homeManagement,"首页");
            ui->tabWidget->insertTab(1,managementStudent,"学生信息管理");
            ui->tabWidget->insertTab(2,managementTeacher,"教师信息管理");
            ui->tabWidget->insertTab(3,managementCourse,"课程信息管理");
            ui->tabWidget->insertTab(4,managementDepartment,"院系信息管理");
            ui->tabWidget->insertTab(5,managementSCT,"选课信息管理");
            ui->tabWidget->insertTab(6,managementAccount,"管理员账号管理");
        }
        this->show();
    }
    else
    {
        this->show();
        this->close();
    }
}
