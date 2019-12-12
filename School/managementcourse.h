#ifndef MANAGEMENTCOURSE_H
#define MANAGEMENTCOURSE_H

#include <QWidget>
#include "user.h"
extern User user;

namespace Ui {
class ManagementCourse;
}

class ManagementCourse : public QWidget
{
    Q_OBJECT

public:
    explicit ManagementCourse(QWidget *parent = nullptr);
    ~ManagementCourse();

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
    Ui::ManagementCourse *ui;
};

#endif // MANAGEMENTCOURSE_H
