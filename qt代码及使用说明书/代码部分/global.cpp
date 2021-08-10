#include "global.h"

QString sqlUser = "root";
QString sqlPwd = "qq6666774";
QString sqlLocalHost = "localhost";
QString username_Current = "";
QString pwd_Current = "";
QString sName_Current = "";
QVariantList list_all_student;

void connect_to_database(QSqlDatabase db)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(sqlLocalHost);
    db.setUserName(sqlUser);
    db.setPassword(sqlPwd);
    db.setDatabaseName("student_manager");

    if(!db.open())
        qDebug() << "connect fail";
    else
    {
        qDebug() << "success";
    }
}
