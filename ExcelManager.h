#ifndef EXCELMANAGER_H
#define EXCELMANAGER_H

#include <QAxObject>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>

class ExcelManager
{
public:
    ExcelManager();
    ~ExcelManager();

    bool SetVisible(bool status);//设置文件可视性
    bool Open(const QString &filePath, int sheetNum = 1);//以不可视方式打开文件，定位到活动工作簿第一张sheet
    bool SwitchSheet(int sheetNum);//切换sheet
    void Close();//关闭工作薄，关闭excel程序
    int GetSheetsCount();//获取行数量
    QVariant GetSheetData();//获取sheet中所有行数据，返回值List中每个元素为一整行的数据

    void PrintPDF();

private:
    QAxObject       excel;
    QAxObject   *   workbooks;
    QAxObject   *   workbook;
    QAxObject   *   worksheets;
    QAxObject   *   worksheet;
    QPrinter        printer;
};

#endif // EXCELMANAGER_H
