#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QVariantList>
#include <QStringList>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

extern QString sqlUser;
extern QString sqlPwd;
extern QString sqlLocalHost;

extern QString username_Current;
extern QString sName_Current;
extern QString pwd_Current;

extern QVariantList list_all_student;

extern void connect_to_database(QSqlDatabase db);

#endif // GLOBAL_H
