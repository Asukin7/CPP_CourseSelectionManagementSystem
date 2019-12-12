#ifndef MANAGEMENTTEACHER_H
#define MANAGEMENTTEACHER_H

#include <QWidget>
#include "user.h"
extern User user;

namespace Ui {
class ManagementTeacher;
}

class ManagementTeacher : public QWidget
{
    Q_OBJECT

public:
    explicit ManagementTeacher(QWidget *parent = nullptr);
    ~ManagementTeacher();

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
    Ui::ManagementTeacher *ui;
};

#endif // MANAGEMENTTEACHER_H
