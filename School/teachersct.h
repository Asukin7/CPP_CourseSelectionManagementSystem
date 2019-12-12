#ifndef TEACHERSCT_H
#define TEACHERSCT_H

#include <QDialog>
#include "user.h"
extern User user;

namespace Ui {
class TeacherSCT;
}

class TeacherSCT : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherSCT(QWidget *parent = nullptr);
    ~TeacherSCT();
    void initialize();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_yes_clicked();

    void on_tableView_clicked();

private:
    Ui::TeacherSCT *ui;
};

#endif // TEACHERSCT_H
