#include "Method.h"
#include <QString>
#include <QList>

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
    //注释部分
    os<<"//get "<<param.GetName().toStdString()<<"\n";
    //函数头部分
    os<<param.GetType().toStdString()<<" "<<param.GetClassName().toStdString()  \
     <<"::Get"<<name.toStdString()<<"() const\n";
    //函数体部分
    os<<"{\n\treturn m_"<<param.GetFullName().toStdString()           \
    <<";\n}\n\n";
}

void Method::WriteSetFuncCPP(std::ostream &os, const AutoCodeParam &param)
{
    QString name = param.GetName();
    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());//首字母转换为大写
    }
    //注释部分
    os<<"//set "<<param.GetName().toStdString()<<"\n";
    //函数头部分
    os<<param.GetType().toStdString()<<" "<<param.GetClassName().toStdString()  \
     <<"::Set"<<name.toStdString()<<"(const "<<param.GetType().toStdString()    \
    <<" &"<<param.GetName().toStdString()<<")\n";
    //函数体部分
    os<<"{\n\tm_"<<param.GetFullName().toStdString()<<" = "                     \
     <<param.GetName().toStdString()<<";\n}\n\n";
}

void Method::WriteConstructorCPP(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<param.GetClassName().toStdString()<<"::"            \
     <<param.GetClassName().toStdString()<<"()\n";
    //初始化部分
        //add your code here
    //函数体部分
    os<<"{\n\n}\n\n";
}

void Method::WriteDestructorCPP(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<param.GetClassName().toStdString()<<"::"<<"~"       \
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
    //注释部分
    os<<"\t/**\n\t * Brief \t\tget "<<param.GetName().toStdString()<<"\n";
    os<<"\t * Author\t\t"<<param.GetAuthor().toStdString()<<"\n";
    os<<"\t * CreateDate\t"<<param.GetCreateDate().toStdString()<<"\n";
    os<<"\t */\n";
    //函数头部分
    os<<"\t"<<param.GetType().toStdString()<<" Get"<<name.toStdString()     \
     <<"() const;\n\n";

}

void Method::WriteSetFuncHeader(std::ostream &os, const AutoCodeParam &param)
{
    QString name = param.GetName();
    if (name.size() > 0)
    {
        name.replace(0,1,name[0].toUpper());//首字母转换为大写
    }
    //注释部分
    os<<"\t/**\n\t * Brief \t\tset "<<param.GetName().toStdString()<<"\n";
    os<<"\t * Author\t\t"<<param.GetAuthor().toStdString()<<"\n";
    os<<"\t * CreateDate\t"<<param.GetCreateDate().toStdString()<<"\n";
    os<<"\t */\n";
    //函数头部分
    os<<"\t"<<param.GetType().toStdString()<<" Set"<<name.toStdString()     \
     <<"(const "<<param.GetType().toStdString()                             \
    <<" &"<<param.GetName().toStdString()<<");\n\n";

}

void Method::WriteConstructorHeader(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<"\t"<<param.GetClassName().toStdString()<<"();\n";
}

void Method::WriteDestructorHeader(std::ostream &os, const AutoCodeParam &param)
{
    //函数头部分
    os<<"\t~"<<param.GetClassName().toStdString()<<"();\n";
}

void Method::WriteDefaultValue(std::ostream &os, const QList<AutoCodeParam> &paramList)
{
    int size = paramList.size();
    bool first = true;
    if (size <= 0)  return;
    for (int i = 0; i < size; ++i)
    {
        if (paramList[i].GetDefaultValue() != "")
        {
            if (first)
            {
                //第一次以“:”开始
                os<<"\t:m_"<<paramList[i].GetFullName().toStdString()<<"("    \
                 <<paramList[i].GetDefaultValue().toStdString()<<")\n";
                first = false;
            }
            else
            {
                //非第一次以","开始
                os<<"\t,m_"<<paramList[i].GetFullName().toStdString()<<"("    \
                 <<paramList[i].GetDefaultValue().toStdString()<<")\n";
            }
        }
    }
}
