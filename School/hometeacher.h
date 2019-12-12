#ifndef HOMETEACHER_H
#define HOMETEACHER_H

#include <QWidget>
#include "user.h"
#include "changepassword.h"
#include "teachercourse.h"
#include "teachersct.h"
extern User user;

namespace Ui {
class HomeTeacher;
}

class HomeTeacher : public QWidget
{
    Q_OBJECT

public:
    explicit HomeTeacher(QWidget *parent = nullptr);
    ~HomeTeacher();
    void initialize();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_changePassword_clicked();

    void on_pushButton_cno1_addChange_clicked();

    void on_pushButton_cno2_addChange_clicked();

    void on_pushButton_cno3_addChange_clicked();

    void on_pushButton_cno1_delete_clicked();

    void on_pushButton_cno2_delete_clicked();

    void on_pushButton_cno3_delete_clicked();

    void on_pushButton_cno1_clicked();

    void on_pushButton_cno2_clicked();

    void on_pushButton_cno3_clicked();

private:
    Ui::HomeTeacher *ui;

    ChangePassword *changePassword;

    TeacherCourse *teacherCourse;

    TeacherSCT *teacherSCT;
};

#endif // HOMETEACHER_H
