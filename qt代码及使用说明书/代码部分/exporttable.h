#ifndef EXPORTTABLE_H
#define EXPORTTABLE_H

#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>

extern void Table2Excel(QTableWidget *table, QString title);

#endif // EXPORTTABLE_H
