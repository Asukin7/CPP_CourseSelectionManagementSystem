#ifndef MANAGEMENTACCOUNT_H
#define MANAGEMENTACCOUNT_H

#include <QWidget>
#include "user.h"
extern User user;

namespace Ui {
class ManagementAccount;
}

class ManagementAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ManagementAccount(QWidget *parent = nullptr);
    ~ManagementAccount();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_change_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_yes_clicked();

    void on_pushButton_back_clicked();

    void on_tableView_clicked();

private:
    Ui::ManagementAccount *ui;
};

#endif // MANAGEMENTACCOUNT_H
