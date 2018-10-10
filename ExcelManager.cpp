#include "ExcelManager.h"
#include <QDebug>

ExcelManager::ExcelManager()
    :workbooks(NULL),
      workbook(NULL),
      worksheets(NULL),
      worksheet(NULL)
{

}

ExcelManager::~ExcelManager()
{

}

bool ExcelManager::Open(const QString &filePath, int sheetNum)
{
    excel.setControl("Excel.Application");
    excel.setProperty("Visible", false);//默认设置窗体不可视
    workbooks = excel.querySubObject("WorkBooks");
    if (workbooks == NULL)
    {
        excel.dynamicCall("Quit()");
        return false;
    }
    workbooks->dynamicCall("Open(const QString&)", filePath);
    workbook = excel.querySubObject("ActiveWorkBook");
    if (workbook == NULL)
    {
        workbooks->dynamicCall("Close()");
        excel.dynamicCall("Quit()");
        return false;
    }
    worksheets = workbook->querySubObject("WorkSheets");
    if (worksheets == NULL)
    {
        workbooks->dynamicCall("Close()");
        excel.dynamicCall("Quit()");
        return false;
    }
    worksheet = workbook->querySubObject("WorkSheets(int)", sheetNum);
    if (worksheet == NULL)
    {
        workbooks->dynamicCall("Close()");
        excel.dynamicCall("Quit()");
        return false;
    }
    return true;
}

bool ExcelManager::SetVisible(bool status)
{
    return excel.setProperty("Visible", status);
}

bool ExcelManager::SwitchSheet(int sheetNum)
{
    worksheet = workbook->querySubObject("WorkSheets(int)", sheetNum);//默认打开第一张sheet
    if (worksheet == NULL)
    {
        return false;
    }
    return true;
}

void ExcelManager::Close()
{
    workbooks->dynamicCall("Close()");
    excel.dynamicCall("Quit()");

    workbooks = NULL;
    workbook = NULL;
    worksheets = NULL;
    worksheet = NULL;
}

int ExcelManager::GetSheetCount()
{
    return worksheets->property("Count").toInt();
}

QVariant ExcelManager::GetSheetData()
{
    QAxObject *usedrange = worksheet->querySubObject("UsedRange");
    QVariant vardata = usedrange->dynamicCall("Value2()");
    return vardata;
}
