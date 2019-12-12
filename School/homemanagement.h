#ifndef HOMEMANAGEMENT_H
#define HOMEMANAGEMENT_H

#include <QWidget>
#include "user.h"
#include "changepassword.h"
extern User user;

namespace Ui {
class HomeManagement;
}

class HomeManagement : public QWidget
{
    Q_OBJECT

public:
    explicit HomeManagement(QWidget *parent = nullptr);
    ~HomeManagement();
    void initialize();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_changePassword_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::HomeManagement *ui;

    ChangePassword *changePassword;
};

#endif // HOMEMANAGEMENT_H
