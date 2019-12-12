#ifndef HOMESTUDENT_H
#define HOMESTUDENT_H

#include <QWidget>
#include "user.h"
#include "changepassword.h"
#include "studentsct.h"
extern User user;

namespace Ui {
class HomeStudent;
}

class HomeStudent : public QWidget
{
    Q_OBJECT

public:
    explicit HomeStudent(QWidget *parent = nullptr);
    ~HomeStudent();
    void initialize();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_changePassword_clicked();

    void on_pushButton_addSCT_clicked();

    void on_pushButton_searchSCT_clicked();

private:
    Ui::HomeStudent *ui;

    ChangePassword *changePassword;

    StudentSCT *studentSCT;
};

#endif // HOMESTUDENT_H
