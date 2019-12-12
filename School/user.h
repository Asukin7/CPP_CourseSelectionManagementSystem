#ifndef USER_H
#define USER_H

#include "toolclass.h"

class User
{
public:
    User();
    bool login(QString id, QString password);
    bool getPermission(QString str);
    void setOnline(bool online);
    bool getOnline();
    void setID(QString id);
    QString getID();
    void setType(QString type);
    QString getType();
    void setIdType(QString idType);
    QString getIdType();

private:
    bool online;
    QString id;
    QString type;
    QString idType;
};

#endif // USER_H
