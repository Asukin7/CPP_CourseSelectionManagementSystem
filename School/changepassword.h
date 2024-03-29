#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include "user.h"
extern User user;

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = nullptr);
    ~ChangePassword();

private slots:
    void on_pushButton_changePassword_clicked();

private:
    Ui::ChangePassword *ui;
};

#endif // CHANGEPASSWORD_H
