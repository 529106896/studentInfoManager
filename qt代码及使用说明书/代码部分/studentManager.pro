#-------------------------------------------------
#
# Project created by QtCreator 2021-07-20T16:37:39
#
#-------------------------------------------------

QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = studentManager
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
CONFIG += qaxcontainer

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    global.cpp \
    manager.cpp \
    studentform.cpp \
    all_stu_info.cpp \
    myclass.cpp \
    myscore.cpp \
    mycourse.cpp \
    searchcourse.cpp \
    stuinfomanage.cpp \
    addstuinfo.cpp \
    myinfo.cpp \
    resetpwd.cpp \
    classinfomanage.cpp \
    allclassinfo.cpp \
    addclass.cpp \
    coursemanage.cpp \
    allcourseinfo.cpp \
    addnewcourse.cpp \
    selectcoursemanage.cpp \
    grademanage.cpp \
    addnewgrade.cpp \
    gradestaticsbystu.cpp \
    gradestaticsbycourse.cpp \
    exporttable.cpp

HEADERS += \
        mainwindow.h \
    global.h \
    manager.h \
    studentform.h \
    all_stu_info.h \
    myclass.h \
    myscore.h \
    mycourse.h \
    searchcourse.h \
    stuinfomanage.h \
    addstuinfo.h \
    myinfo.h \
    resetpwd.h \
    classinfomanage.h \
    allclassinfo.h \
    addclass.h \
    coursemanage.h \
    allcourseinfo.h \
    addnewcourse.h \
    selectcoursemanage.h \
    grademanage.h \
    addnewgrade.h \
    gradestaticsbystu.h \
    gradestaticsbycourse.h \
    exporttable.h

FORMS += \
        mainwindow.ui \
    manager.ui \
    studentform.ui \
    all_stu_info.ui \
    myclass.ui \
    myscore.ui \
    mycourse.ui \
    searchcourse.ui \
    stuinfomanage.ui \
    addstuinfo.ui \
    myinfo.ui \
    resetpwd.ui \
    classinfomanage.ui \
    allclassinfo.ui \
    addclass.ui \
    coursemanage.ui \
    allcourseinfo.ui \
    addnewcourse.ui \
    selectcoursemanage.ui \
    grademanage.ui \
    addnewgrade.ui \
    gradestaticsbystu.ui \
    gradestaticsbycourse.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
