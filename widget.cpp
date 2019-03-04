#include "widget.h"
#include "ui_widget.h"
#include <QAxObject>
#include <QFileDialog>
#include <QVariant>
#include <QDebug>
#include <fstream>
#include <ExcelManager.h>
#include "Method.h"
#include "AutoCodeParam.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择文件:"),
                                                    "D:\\RollWare\\personal_by\\documents",
                                                    tr("*.xls *.xlsx"));

    {
        //not use
        //    QAxObject excel;
        //    excel.setControl("Excel.Application");
        //    excel.setProperty("Visible", false);
        //    QAxObject *workbooks = excel.querySubObject("WorkBooks");
        //    workbooks->dynamicCall("Open(const QString&)", fileName);
        //    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
        //    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)", 1);
        //    QAxObject *usedrange = worksheet->querySubObject("UsedRange");
    }

    if (QFile::exists(fileName) == false) return;
    ExcelManager excel;
    if (!excel.Open(fileName))  return;//打开文件
    QVariant vardata = excel.GetSheetData();//获取第一张sheet所有数据
    excel.Close();
    QVariantList rowsdata = vardata.toList();
    QVariantList rowdata = rowsdata[2].toList();

    for (int i = 0; i < rowdata.size(); ++i)
    {
        qDebug()<<rowdata[i].toString();
    }


    std::ofstream ofs("D:\\by_test.cpp");
    if (ofs)
    {
        int i = 2;
        QList<AutoCodeParam> paramList;
        while(i <= 3)
        {
            rowdata = rowsdata[i].toList();
            if (rowdata.size() < 9) break;
            AutoCodeParam param;
            param.SetClassName(rowdata[0].toString());
            param.SetName(rowdata[1].toString());
            param.SetType(rowdata[2].toString());
            param.SetPrefix(rowdata[3].toString());
            param.SetSuffix(rowdata[4].toString());
            param.SetNotes(rowdata[5].toString());
            param.SetAuthor(rowdata[6].toString());
            param.SetCreateDate(rowdata[7].toString());
            param.SetDefaultValue(rowdata[8].toString());
            Method method;
            method.WriteGetFuncCPP(ofs,param);
            method.WriteSetFuncCPP(ofs,param);
            method.WriteConstructorCPP(ofs,param);
            method.WriteDestructorCPP(ofs,param);
            method.WriteSetFuncHeader(ofs,param);
            method.WriteGetFuncHeader(ofs,param);
            method.WriteConstructorHeader(ofs,param);
            method.WriteDestructorHeader(ofs,param);
            method.WriteClassDefinitionHeader(ofs,param);

            paramList.append(param);
            if (i == 3)
            {
                method.WriteDefaultValue(ofs,paramList);
            }

            ++i;
        }

        ofs.close();
    }
    else
    {
        qDebug()<<"打开文件失败";
    }



}

void Widget::on_pushButton_2_clicked()
{
    ExcelManager excel;
    excel.PrintPDF();
}
