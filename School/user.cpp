#include "user.h"

User::User()
{
    setOnline(false);
}

bool User::login(QString id, QString password)
{
    setID(id);
    switch (id.length())
    {
    case 8://teacher
        setType("teacher");
        setIdType("tno");
        break;
    case 9://student
        setType("student");
        setIdType("sno");
        break;
    case 10://management
        setType("management");
        setIdType("mno");
        break;
    default:
        setType("");
        setIdType("");
        break;
    }
    QSqlQuery query;
    query.exec(QString("select * from %1 where %2 = '%3' and password = '%4'").arg(getType(), getIdType(), getID(), password));
    if(!query.next())
    {
        QMessageBox::critical(NULL, "错误", "登录失败");
        return getOnline();
    }
    setOnline(true);
    return getOnline();
}

bool User::getPermission(QString str)
{
    QSqlQuery query;
    query.exec(QString("select %1 from %2 where %3 = '%4'").arg(str, getType(), getIdType(), getID()));
    if(!query.next())
    {
        QMessageBox::critical(NULL, "错误", "发生未知错误");
        return false;
    }
    query.seek(0);
    if(query.value(0).toBool())
    {
        return true;
    }
    else
    {
        QMessageBox::critical(NULL, "错误", "权限不足");
        return false;
    }
}

void User::setOnline(bool online)
{
    this->online = online;
}

bool User::getOnline()
{
    return this->online;
}

void User::setID(QString id)
{
    this->id = id;
}

QString User::getID()
{
    return this->id;
}

void User::setType(QString type)
{
    this->type = type;
}

QString User::getType()
{
    return this->type;
}

void User::setIdType(QString idType)
{
    this->idType = idType;
}

QString User::getIdType()
{
    return this->idType;
}
