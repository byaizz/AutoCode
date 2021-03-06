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
    //选择文件
    QString fileName = QFileDialog::getOpenFileName(this,"选择文件:",
                                                    "..\\",
                                                    "*.xls *.xlsx");

    if (QFile::exists(fileName) == false) return;
    ExcelManager excel;
    if (!excel.Open(fileName))  return;//打开文件

    int count = excel.GetSheetsCount();
    for (int i = 1; i <= count; ++i)
    {
        excel.SwitchSheet(i);
        QVariant vardata = excel.GetSheetData();//获取第一张sheet所有数据
        QVariantList rowsdata = vardata.toList();//获取行数据
        QVariantList rowdata = rowsdata[0].toList();//获取第一行的数据

        //输出各列名    for test
        for (int i = 0; i < rowdata.size(); ++i)
        {
            qDebug()<<rowdata[i].toString();
        }

        //保存每个sheet上的所有参数
        //第一行为列名，参数从第二行开始
        QList<AutoCodeParam> paramList;
        for (int i = 1; i < rowsdata.size(); ++i)
        {
            rowdata = rowsdata[i].toList();
            if (rowdata.size() < 11) break;
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
            param.SetStructName(rowdata[9].toString());
            param.SetStructAliasName(rowdata[10].toString());
            paramList.append(param);
        }

        //无参情况下继续下张表单
        if (paramList.size() < 0)
        {
            continue;
        }

        //创建目录
        QDir dir;
        QString dirName = "..\\target";//目标文件目录
        if (!dir.exists(dirName))
        {
            //dir.mkdir(dirName);//这个函数将会创建一个名为dirName的子目录
            dir.mkpath(dirName);//这个函数将会创建所有必需的父类目录
        }

        //获取文件名，以类名作为文件名
        QString targetFileName = dirName + "\\"+ paramList[0].GetClassName();
        QString HeaderName = targetFileName;
        HeaderName += ".h";

        //输出到文件
        Method method;
        std::ofstream ofs(HeaderName.toStdString());
        if (ofs)
        {
            method.WriteHeader(ofs,paramList);
            ofs.close();
        }
        else
        {
            qDebug()<<"打开header文件失败";
        }

        QString CPPName = targetFileName;
        CPPName += ".cpp";
        ofs.open(CPPName.toStdString());
        if (ofs)
        {
            method.WriteCPP(ofs,paramList);
            ofs.close();
        }
        else
        {
            qDebug()<<"打开cpp文件失败";
        }
    }
    excel.Close();
}

void Widget::on_pushButton_2_clicked()
{
    ExcelManager excel;
    excel.PrintPDF();
}
