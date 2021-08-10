#include "exporttable.h"

void Table2Excel(QTableWidget *table, QString title)
{
    QString fileName = QFileDialog::getSaveFileName(table, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx)");
    if(fileName != "")
    {
        QAxObject *excel = new QAxObject;
        if(excel->setControl("Excel.Application"))
        {
            excel->dynamicCall("SetVisible (bool Visible)","false");
            excel->setProperty("DisplayAlerts", false);
            QAxObject *workbooks = excel->querySubObject("WorkBooks");
            workbooks->dynamicCall("Add");
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

            int i,j;
            int colcount = table->columnCount();
            int rowcount = table->rowCount();

            QAxObject *cell,*col;
            cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
            cell->dynamicCall("SetValue(const QString&)", title);
            cell->querySubObject("Font")->setProperty("Size", 18);
            //调整行高
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //合并标题行
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);

            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108);//xlCenter
            range->setProperty("VerticalAlignment", -4108);//xlCenter
            for(i=0;i<colcount;i++)
            {
                QString columnName;
                columnName.append(QChar(i + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                cell = worksheet->querySubObject("Cells(int,int)", 2, i+1);

                columnName = table->horizontalHeaderItem(i)->text();

                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                cell->setProperty("VerticalAlignment", -4108);//xlCenter
            }




            for(i=0;i<rowcount;i++)
            {
                for (j=0;j<colcount;j++)
                {
                    worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
                    //worksheet->querySubObject("Cells(int,int)", i+3, j+1)->setProperty("VerticalAlignment", -4108);
                    cell = worksheet->querySubObject("Cells(int,int)", i+3, j+1);
                    cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                    cell->setProperty("VerticalAlignment", -4108);//xlCenter
                }
            }


            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));

            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 20);
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));
            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");
            delete excel;

            excel = NULL;

            if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                 QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        }
    }
    else
    {
        QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
    }
}
