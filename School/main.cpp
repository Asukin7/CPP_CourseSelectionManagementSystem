#include "management.h"
#include <QApplication>
#include <QMessageBox>
#include <QtSql>
#include "user.h"
User user;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ExitCode = 0;
    do
    {
        /*获取配置文件sql.ini*/
        QString configFileName = QCoreApplication::applicationDirPath() + "/sql.ini";
        QSettings *configIni = new QSettings(configFileName, QSettings::IniFormat);
        QFileInfo fileInfo(configFileName);
        if(!fileInfo.exists())
        {
            QMessageBox::critical(NULL, "错误", "获取配置文件sql.ini失败");
            ExitCode = 1;
            break;
        }
        QString sqlConfig[5];
        sqlConfig[0] = configIni->value("sqlConfig/SERVER").toString();
        sqlConfig[1] = configIni->value("sqlConfig/PORT").toString();
        sqlConfig[2] = configIni->value("sqlConfig/DATABASE").toString();
        sqlConfig[3] = configIni->value("sqlConfig/UID").toString();
        sqlConfig[4] = configIni->value("sqlConfig/PWD").toString();
        /*END*/
        /*连接数据库*/
        QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");
        myDB.setDatabaseName(QString("Driver={sql server};SERVER=%1;PORT=%2;DATABASE=%3;UID=%4;PWD=%5;")
                             .arg(sqlConfig[0], sqlConfig[1], sqlConfig[2], sqlConfig[3], sqlConfig[4]));
        if(!myDB.open())
        {
            QMessageBox::critical(NULL, "错误", "连接数据库失败");
            ExitCode = 1;
            break;
        }
        /*END*/
        /*启动用户界面*/
        do
        {
            Management *m = new Management();
            m->initialize();
            if(!user.getOnline()) break;
            ExitCode = a.exec();
            m->deleteLater();
        }while(ExitCode == 666);
        /*END*/
    }while(ExitCode == 888);

    return ExitCode;
}
