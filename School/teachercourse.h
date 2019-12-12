#ifndef TEACHERCOURSE_H
#define TEACHERCOURSE_H

#include <QDialog>
#include "user.h"
extern User user;

namespace Ui {
class TeacherCourse;
}

class TeacherCourse : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherCourse(QWidget *parent = nullptr);
    ~TeacherCourse();
    void initialize();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked();

private:
    Ui::TeacherCourse *ui;
};

#endif // TEACHERCOURSE_H
