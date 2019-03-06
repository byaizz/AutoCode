#include "Method.h"
#include <QString>
#include <QList>
#include <QDebug>

Method::Method()
{

}

Method::~Method()
{

}

void Method::WriteGetFuncCPP(std::ostream &os, const AutoCodeParam &param)
{
    QString name = param.GetName();

    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());;//首字母转换为大写
    }
    QString arrayNote;//数组与普通变量写入方式不同
    if (param.GetElementCount().size() <= 0)
    {
        arrayNote = " ";
    }
    {
        arrayNote = " *";
    }
    //注释部分
    //os<<"//get "<<param.GetName().toStdString()<<"\n";
    //函数头部分
    if (param.GetElementCount().size() <= 0)
    {
        //函数头部分
        os<<param.GetType().toStdString()<<" "<<param.GetClassName().toStdString()
         <<"::Get"<<name.toStdString()
         <<"() const\n";
        //函数体部分
        os<<"{\n\treturn "<<param.GetFullNameForClass().toStdString()
        <<";\n}\n\n";
    }
    else
    {   //函数头部分
        os<<"void "<<param.GetClassName().toStdString()
         <<"::Get"<<name.toStdString()
        <<"("<<param.GetType().toStdString()<<" *"
       <<param.GetFullNameForStruct().toStdString()<<") const\n";
        //函数体部分
        os<<"{\n\tmemcpy("<<param.GetFullNameForStruct().toStdString()
         <<","<<param.GetFullNameForClass().toStdString()
        <<", sizeof("<<param.GetType().toStdString()
        <<")*"<<param.GetElementCount().mid(1,param.GetElementCount().size() - 2).toStdString()
        <<");\n}\n\n";
    }
}

void Method::WriteSetFuncCPP(std::ostream &os, const AutoCodeParam &param)
{
    QString name = param.GetName();
    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());//首字母转换为大写
    }
    QString arrayNote;//数组与普通变量写入方式不同
    if (param.GetElementCount().size() <= 0)
    {
        arrayNote = " &";
    }
    else
    {
        arrayNote = " *";
    }
    //注释部分
    //os<<"//set "<<param.GetName().toStdString()<<"\n";
    //函数头部分
    os<<"void "<<param.GetClassName().toStdString()
     <<"::Set"<<name.toStdString()<<"(const "<<param.GetType().toStdString()
    <<arrayNote.toStdString()<<param.GetFullNameForStruct().toStdString()<<")\n";
    //函数体部分
    if (param.GetElementCount().size() <= 0)
    {
        os<<"{\n\t"<<param.GetFullNameForClass().toStdString()<<" = "                     \
         <<param.GetFullNameForStruct().toStdString()<<";\n}\n\n";
    }
    else
    {
        os<<"{\n\tmemcpy("<<param.GetFullNameForClass().toStdString()<<", "                     \
         <<param.GetFullNameForStruct().toStdString()
        <<", sizeof("<<param.GetType().toStdString()
        <<")*"<<param.GetElementCount().mid(1,param.GetElementCount().size() - 2).toStdString()
        <<");\n}\n\n";
    }

}

void Method::WriteConstructorCPP(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    //函数头部分
    os<<paramList[0].GetClassName().toStdString()<<"::"
     <<paramList[0].GetClassName().toStdString()<<"()\n";
    //初始化部分
        //add your code here
    WriteDefaultValue(os,paramList);
    //函数体部分
    os<<"{\n";
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (paramList[i].GetElementCount().size() > 0 )
        {
            os<<"\tmemset("<<paramList[i].GetFullNameForClass().toStdString()
             <<", 0, sizeof("<<paramList[i].GetType().toStdString()<<")*"
            <<paramList[i].GetElementCount().mid(1,paramList[i].GetElementCount().size() - 2).toStdString();
            os<<");\n";
        }
    }
    os<<"\n}\n\n";
}

void Method::WriteDestructorCPP(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<param.GetClassName().toStdString()<<"::"<<"~"
     <<param.GetClassName().toStdString()<<"()\n";
    //函数体部分
    os<<"{\n\n}\n\n";
}

void Method::WriteClassDefinitionHeader(std::ostream &os, const AutoCodeParam &param)
{
    os<<"class "<<param.GetClassName().toStdString()<<"\n{\n";
    os<<"public:\n";
    WriteConstructorHeader(os,param);
    WriteDestructorHeader(os,param);
    os<<"private:\n\n};\n\n";
}

void Method::WriteGetFuncHeader(std::ostream &os, const AutoCodeParam &param)
{
    QString name = param.GetName();

    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());;//首字母转换为大写
    }
    QString arrayNote;//数组与普通变量写入方式不同
    if (param.GetElementCount().size() <= 0)
    {
        arrayNote = "";
    }
    {
        arrayNote = "*";
    }
    //注释部分
    //os<<"\t/**\n\t * Brief \t\tget "<<param.GetName().toStdString()<<"\n";
    //os<<"\t * Author\t\t"<<param.GetAuthor().toStdString()<<"\n";
    //os<<"\t * CreateDate\t"<<param.GetCreateDate().toStdString()<<"\n";
    //os<<"\t */\n";
    //函数头部分
    if (param.GetElementCount().size() <= 0)
    {
        os<<"\t"<<param.GetType().toStdString()<<" Get"<<name.toStdString()
         <<"() const;\n\n";
    }
    else
    {
        os<<"\tvoid"<<" Get"<<name.toStdString()
         <<"("<<param.GetType().toStdString()<<" *"
        <<param.GetFullNameForStruct().toStdString()<<") const;\n\n";
    }


}

void Method::WriteSetFuncHeader(std::ostream &os, const AutoCodeParam &param)
{
    QString name = param.GetName();
    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());//首字母转换为大写
    }
    QString arrayNote;//数组与普通变量写入方式不同
    if (param.GetElementCount().size() <= 0)
    {
        arrayNote = " &";
    }
    else
    {
        arrayNote = " *";
    }
    //注释部分
    //os<<"\t/**\n\t * Brief \t\tset "<<param.GetName().toStdString()<<"\n";
    //os<<"\t * Author\t\t"<<param.GetAuthor().toStdString()<<"\n";
    //os<<"\t * CreateDate\t"<<param.GetCreateDate().toStdString()<<"\n";
    //os<<"\t */\n";
    //函数头部分
    os<<"\tvoid Set"<<name.toStdString()
     <<"(const "<<param.GetType().toStdString()
    <<arrayNote.toStdString()<<param.GetFullNameForStruct().toStdString()<<");\n\n";
}

void Method::WriteConstructorHeader(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<"\t"<<param.GetClassName().toStdString()<<"();\t\t//构造函数\n";
}

void Method::WriteDestructorHeader(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<"\t~"<<param.GetClassName().toStdString()<<"();\t\t//析构函数\n";
}

void Method::WriteDefaultValue(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    int size = paramList.size();
    bool first = true;
    if (size <= 0)  return;
    for (int i = 0; i < size; ++i)
    {
        if (paramList[i].GetDefaultValue() != "" && paramList[i].GetElementCount().size() == 0)
        {
            if (first)
            {
                //第一次以“:”开始
                os<<"\t:"<<paramList[i].GetFullNameForClass().toStdString()<<"("    \
                 <<paramList[i].GetDefaultValue().toStdString()<<")\n";
                first = false;
            }
            else
            {
                //非第一次以","开始
                os<<"\t,"<<paramList[i].GetFullNameForClass().toStdString()<<"("    \
                 <<paramList[i].GetDefaultValue().toStdString()<<")\n";
            }
        }
    }
}

void Method::WriteStructHeader(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    //因为所有参数都是在同一个结构体中，所以结构体名都是一样，选第一个参数即可设置结构体名
    //输出struct头部部分
    os<<"typedef struct "<<paramList[0].GetStructName().toStdString()<<"_st\n";
    os<<"{\n";

    int maxSizeOfName = GetMaxSizeOfFullNameForStruct(paramList);
    int maxSizeOfType = GetMaxSizeOfType(paramList);
    //输出struct函数声明部分
    for (int i = 0; i < paramList.size(); ++i)
    {
        int typeSize = paramList[i].GetType().size();
        int tableCount = GetTableCount(maxSizeOfType) - GetTableCount(typeSize);//需要插入的table键的个数
        QString tableString(tableCount,'\t');//需要插入的table
        os<<"\t"<<paramList[i].GetType().toStdString()<<tableString.toStdString()<<"\t"
         <<paramList[i].GetFullNameForStruct().toStdString()
        <<paramList[i].GetElementCount().toStdString()<<";";

        int nameSize = paramList[i].GetFullNameForStruct().size() + paramList[i].GetElementCount().size();
        tableCount = GetTableCount(maxSizeOfName + 1) - GetTableCount(nameSize + 1);
        tableString = QString(tableCount,'\t');//需要插入的table
        os<<tableString.toStdString()<<"\t//"<<paramList[i].GetNotes().toStdString()<<"\n";
    }
    //输出struct尾部部分
    os<<"}"<<paramList[0].GetStructAliasName().toStdString()<<";\n\n";
}

void Method::WriteClassHeader(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;

    //因为所有参数都是在同一个类中，所以类名都是一样，选第一个参数即可设置类名
    //输出class头部部分
    os<<"class "<<paramList[0].GetClassName().toStdString()<<"\n";
    os<<"{\n";

    //输出class构造函数和析构函数
    os<<"public:\n";
    WriteConstructorHeader(os,paramList[0]);
    WriteDestructorHeader(os,paramList[0]);

    //输出set、get函数
    os<<"public:\n";
    for (int i = 0; i < paramList.size(); ++i)
    {
        WriteSetFuncHeader(os,paramList[i]);
    }
    for (int i = 0; i < paramList.size(); ++i)
    {
        WriteGetFuncHeader(os,paramList[i]);
    }

    //输出struct-class转换函数的get、set声明
    WriteConvertFuncHeader(os,paramList);

    //输出变量声明
    WriteVariableDefinitionHeader(os,paramList);

    //输出class尾部部分
    os<<"};";
}

void Method::WriteClassCPP(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;

    //输出构造函数析构函数
    WriteConstructorCPP(os,paramList);
    WriteDestructorCPP(os,paramList[0]);

    //输出set、get函数
    for (int i = 0; i < paramList.size(); ++i)
    {
        WriteSetFuncCPP(os,paramList[i]);
    }
    for (int i = 0; i < paramList.size(); ++i)
    {
        WriteGetFuncCPP(os,paramList[i]);
    }

    //输出输出struct-class转换函数的get、set声明
    WriteConvertFuncCPP(os,paramList);

}

void Method::WriteHeader(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    //输出ifndef
    os<<"#ifndef "<<paramList[0].GetClassName().toUpper().toStdString()<<"_H\n";
    os<<"#define "<<paramList[0].GetClassName().toUpper().toStdString()<<"_H\n";
    os<<"\n";

    WriteStructHeader(os,paramList);
    WriteClassHeader(os,paramList);

    //输出endif
    os<<"\n\n"<<"#endif";
}

void Method::WriteCPP(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    //输出include
    os<<"#include \""<<paramList[0].GetClassName().toStdString()<<".h\"\n";
    os<<"\n";
    WriteClassCPP(os,paramList);
}

void Method::WriteVariableDefinitionHeader(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    os<<"private:\n";
    //输出变量声明
    int maxSizeOfName = GetMaxSizeOfFullNameForClass(paramList);
    int maxSizeOfType = GetMaxSizeOfType(paramList);

    for (int i = 0; i < paramList.size(); ++i)
    {
        int typeSize = paramList[i].GetType().size();
        int tableCount = GetTableCount(maxSizeOfType) - GetTableCount(typeSize);
        QString tableString = QString(tableCount,'\t');//需要插入的table

        os<<"\t"<<paramList[i].GetType().toStdString()<<tableString.toStdString()
         <<"\t"<<paramList[i].GetFullNameForClass().toStdString()
        <<paramList[i].GetElementCount().toStdString()<<";";

        int nameSize = paramList[i].GetFullNameForClass().size() + paramList[i].GetElementCount().size();
        tableCount = GetTableCount(maxSizeOfName + 1) - GetTableCount(nameSize + 1);
        tableString = QString(tableCount,'\t');//需要插入的table

        os<<tableString.toStdString()<<"\t//"<<paramList[i].GetNotes().toStdString()<<"\n";


    }
}

void Method::WriteConvertFuncHeader(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    QString name = paramList[0].GetStructAliasName().toLower();
    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());//首字母转换为大写
    }
    os<<"public:\n";
    os<<"\tvoid Set"<<name.toStdString()<<"(const "
     <<paramList[0].GetStructAliasName().toStdString()<<" &"
    <<paramList[0].GetStructAliasName().toLower().toStdString()<<");\n";
    os<<"\tvoid Get"<<name.toStdString()<<"("
     <<paramList[0].GetStructAliasName().toStdString()<<" &"
    <<paramList[0].GetStructAliasName().toLower().toStdString()<<") const;\n";
}

void Method::WriteConvertFuncCPP(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return;
    QString variableName = paramList[0].GetStructAliasName().toLower();//局部变量的名称

    //set
    //函数头部分
    os<<"void "<<" "<<paramList[0].GetClassName().toStdString()<<"::Set"
     <<paramList[0].GetStructAliasName().toLower().toStdString()<<"(const "
     <<paramList[0].GetStructAliasName().toStdString()<<" &"
    <<variableName.toStdString()<<")\n";

    int maxSizeOfName = GetMaxSizeOfFullNameForClass(paramList);
    //函数体部分
    os<<"{\n";
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (paramList[i].GetElementCount() == 0)
        {
            int nameSize = paramList[i].GetFullNameForClass().size();
            int tableCount = GetTableCount(maxSizeOfName) - GetTableCount(nameSize);//需要插入的table键的个数
            QString tableString(tableCount,'\t');//需要插入的table

            os<<"\t"<<paramList[i].GetFullNameForClass().toStdString()
             <<tableString.toStdString()<<"\t=\t"<<variableName.toStdString()
            <<"."<<paramList[i].GetFullNameForStruct().toStdString()<<";\n";
        }
        else
        {
            os<<"\tmemcpy("<<paramList[i].GetFullNameForClass().toStdString()
             <<", "<<variableName.toStdString()<<"."
            <<paramList[i].GetFullNameForStruct().toStdString()
            <<", sizeof("<<paramList[i].GetType().toStdString()
            <<")*"<<paramList[i].GetElementCount().mid(1,paramList[i].GetElementCount().size() - 2).toStdString()
            <<");\n";
        }

    }
    os<<"}\n";

    //get
    //函数头部分
    os<<"void "<<" "<<paramList[0].GetClassName().toStdString()<<"::Get"
     <<paramList[0].GetStructAliasName().toLower().toStdString()<<"("
     <<paramList[0].GetStructAliasName().toStdString()<<" &"
    <<variableName.toStdString()<<") const\n";

    maxSizeOfName = GetMaxSizeOfFullNameForStruct(paramList) + variableName.size() + 1;
    //函数体部分
    os<<"{\n";
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (paramList[i].GetElementCount().size() == 0)
        {
            int nameSize = paramList[i].GetFullNameForStruct().size() + variableName.size() + 1;
            int tableCount = GetTableCount(maxSizeOfName) - GetTableCount(nameSize);//需要插入的table键的个数
            QString tableString(tableCount,'\t');//需要插入的table

            os<<"\t"<<variableName.toStdString()<<"."<<paramList[i].GetFullNameForStruct().toStdString()
             <<tableString.toStdString()<<"\t=\t"
             <<paramList[i].GetFullNameForClass().toStdString()<<";\n";
        }
        else
        {
            os<<"\tmemcpy("<<variableName.toStdString()<<"."
            <<paramList[i].GetFullNameForStruct().toStdString()
            <<", "<<paramList[i].GetFullNameForClass().toStdString()
            <<", sizeof("<<paramList[i].GetType().toStdString()<<")*"
            <<paramList[i].GetElementCount().mid(1,paramList[i].GetElementCount().size() - 2).toStdString()
            <<");\n";
        }

    }
    os<<"}\n";
}

int Method::GetMaxSizeOfFullNameForClass(const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return 0;
    int maxSize = 0;
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (paramList[i].GetFullNameForClass().size() + paramList[i].GetElementCount().size() > maxSize)
        {
            maxSize = paramList[i].GetFullNameForClass().size() + paramList[i].GetElementCount().size();
        }
    }
    return maxSize;
}

int Method::GetMaxSizeOfFullNameForStruct(const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return 0;
    int maxSize = 0;
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (paramList[i].GetFullNameForStruct().size()  + paramList[i].GetElementCount().size() > maxSize)
        {
            maxSize = paramList[i].GetFullNameForStruct().size() + paramList[i].GetElementCount().size();
        }
    }
    return maxSize;
}

int Method::GetMaxSizeOfType(const QList<AutoCodeParam> &paramList)
{
    if (paramList.size() <= 0) return 0;
    int maxSize = 0;
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (paramList[i].GetType().size() > maxSize)
        {
            maxSize = paramList[i].GetType().size();
        }
    }
    return maxSize;
}

int Method::GetTableCount(int characterCount)
{
    return characterCount/4;
}
