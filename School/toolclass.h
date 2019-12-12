#ifndef TOOLCLASS_H
#define TOOLCLASS_H

#include <QMessageBox>
#include <QtSql>
#include <QFileDialog>
#include <QtCore>
#include "xlsxdocument.h"

class ToolClass
{
public:
    ToolClass();
    static QString QStringAdd___(QString str, QString ___);
    static QString QString___Add(QString str, QString ___);
    static QString QStringChangeNULL(QString str);
    static QString BoolToQString(bool flag);
    static QString SQLSearchWhereWhatLikeValue(QString str, QString ___, QString what, QString value);
    static void SQLQuery(QString str, QString success, QString fail);
    static void TableToXlsx(QAbstractItemModel *model);
};

#endif // TOOLCLASS_H
