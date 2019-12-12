#ifndef STUDENTSCT_H
#define STUDENTSCT_H

#include <QDialog>
#include "user.h"
extern User user;

namespace Ui {
class StudentSCT;
}

class StudentSCT : public QDialog
{
    Q_OBJECT

public:
    explicit StudentSCT(QWidget *parent = nullptr);
    ~StudentSCT();
    void initialize();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked();

private:
    Ui::StudentSCT *ui;
};

#endif // STUDENTSCT_H
