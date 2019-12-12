#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QMainWindow>
#include "user.h"
#include "login.h"
#include "homestudent.h"
#include "hometeacher.h"
#include "homemanagement.h"
#include "managementstudent.h"
#include "managementteacher.h"
#include "managementcourse.h"
#include "managementdepartment.h"
#include "managementsct.h"
#include "managementaccount.h"
extern User user;

namespace Ui {
class Management;
}

class Management : public QMainWindow
{
    Q_OBJECT

public:
    explicit Management(QWidget *parent = nullptr);
    ~Management();
    void initialize();

private:
    Ui::Management *ui;
    HomeTeacher *homeTeacher;
    HomeStudent *homeStudent;
    HomeManagement *homeManagement;
    ManagementStudent *managementStudent;
    ManagementTeacher *managementTeacher;
    ManagementCourse *managementCourse;
    ManagementDepartment *managementDepartment;
    ManagementSCT *managementSCT;
    ManagementAccount *managementAccount;
};

#endif // MANAGEMENT_H
