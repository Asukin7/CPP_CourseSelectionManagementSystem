#include "toolclass.h"

ToolClass::ToolClass()
{

}

QString ToolClass::QStringAdd___(QString str, QString ___)
{
    if(str != "")
    {
        str = str + QString(" %1 ").arg(___);
    }
    return str;
}

QString ToolClass::QString___Add(QString str, QString ___)
{
    if(str != "")
    {
        str = QString(" %1 ").arg(___) + str;
    }
    return str;
}

QString ToolClass::QStringChangeNULL(QString str)
{
    if(str == "")
    {
        return "null";
    }
    return  QString("'%1'").arg(str);
}

QString ToolClass::BoolToQString(bool flag)
{
    if(flag)
    {
        return "1";
    }
    else
    {
        return "0";
    }
}

QString ToolClass::SQLSearchWhereWhatLikeValue(QString str, QString ___, QString what, QString value)
{
    if(!value.isEmpty())
    {
        str = QStringAdd___(str, ___);
        str += QString("%1 like '%%2%'").arg(what, value);
    }
    return str;
}

void ToolClass::SQLQuery(QString str, QString success, QString fail)
{
    QSqlQuery query;
    if(query.exec(str))
    {
        QMessageBox::information(NULL, "成功", success);
    }
    else
    {
        QMessageBox::critical(NULL, "错误", QString("%1\n错误:\n%2").arg(fail, query.lastError().text()));
    }
}

void ToolClass::TableToXlsx(QAbstractItemModel *model)
{
    QXlsx::Document xlsx;

    int row = model->rowCount();
    int column = model->columnCount();
    for (int j = 0; j < column; j++)
    {
        xlsx.write(1, j + 1, model->headerData(j, Qt::Horizontal).toString());
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            xlsx.write(i + 2, j + 1, model->data(model->index(i, j)).toString());
        }
    }

    QFileDialog QFD;
    QString FileName = QFD.getSaveFileName(NULL,"文件保存","C:\\","*.xlsx");//选择保存路径
    if(FileName.length() == 0)//判断是否取消
    {
        return;
    }

    if(xlsx.saveAs(FileName))
    {
        QMessageBox::information(NULL, "成功", "保存xlsx文件成功");
    }
}
