#-------------------------------------------------
#
# Project created by QtCreator 2019-10-15T10:03:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql

include(xlsx/qtxlsx.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = School
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        changepassword.cpp \
        homemanagement.cpp \
        homestudent.cpp \
        hometeacher.cpp \
        main.cpp \
        login.cpp \
        management.cpp \
        managementaccount.cpp \
        managementcourse.cpp \
        managementdepartment.cpp \
        managementsct.cpp \
        managementstudent.cpp \
        managementteacher.cpp \
        studentsct.cpp \
        teachercourse.cpp \
        teachersct.cpp \
        toolclass.cpp \
        user.cpp

HEADERS += \
        changepassword.h \
        homemanagement.h \
        homestudent.h \
        hometeacher.h \
        login.h \
        management.h \
        managementaccount.h \
        managementcourse.h \
        managementdepartment.h \
        managementsct.h \
        managementstudent.h \
        managementteacher.h \
        studentsct.h \
        teachercourse.h \
        teachersct.h \
        toolclass.h \
        user.h

FORMS += \
        changepassword.ui \
        homemanagement.ui \
        homestudent.ui \
        hometeacher.ui \
        login.ui \
        management.ui \
        managementaccount.ui \
        managementcourse.ui \
        managementdepartment.ui \
        managementsct.ui \
        managementstudent.ui \
        managementteacher.ui \
        studentsct.ui \
        teachercourse.ui \
        teachersct.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sql.ini
