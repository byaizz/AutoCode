#ifndef METHOD_H
#define METHOD_H

#include <iostream>
#include <AutoCodeParam.h>

class Method
{
public:
    Method();
    ~Method();
    //cpp文件的set 函数
    void WriteSetFuncCPP(std::ostream &os, const AutoCodeParam &param);
    //cpp文件的get 函数
    void WriteGetFuncCPP(std::ostream &os, const AutoCodeParam &param);
    //cpp文件的无参构造函数
    void WriteConstructorCPP(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //cpp文件的析构函数
    void WriteDestructorCPP(std::ostream &os, const AutoCodeParam &param);
    //头文件的set 函数
    void WriteSetFuncHeader(std::ostream &os, const AutoCodeParam &param);
    //头文件的get函数
    void WriteGetFuncHeader(std::ostream &os, const AutoCodeParam &param);
    //头文件的构造函数
    void WriteConstructorHeader(std::ostream &os, const AutoCodeParam &param);
    //头文件的析构函数
    void WriteDestructorHeader(std::ostream &os, const AutoCodeParam &param);
    //头文件的类定义--已废弃
    void WriteClassDefinitionHeader(std::ostream &os, const AutoCodeParam &param);
    //初始化默认值，用于构造函数中
    void WriteDefaultValue(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //头文件的struct结构体声明 paramList-当前类的所有参数
    void WriteStructHeader(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //头文件的class声明 paramList-当前类的所有参数
    void WriteClassHeader(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //cpp文件写入class定义 paramList-当前类的所有参数
    void WriteClassCPP(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //头文件写入操作 paramList-当前类的所有参数
    void WriteHeader(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //cpp文件写入操作  paramList-当前类的所有参数
    void WriteCPP(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //头文件写入变量声明
    void WriteVariableDefinitionHeader(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //头文件的class-struct转换函数的声明
    void WriteConvertFuncHeader(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //cpp文件的class-struct转换函数的定义
    void WriteConvertFuncCPP(std::ostream &os, const QList<AutoCodeParam> &paramList);
    //获取class内参数名的最大字节长度
    int GetMaxSizeOfFullNameForClass(const QList<AutoCodeParam> &paramList);
    //获取struct内参数名的最大字节长度
    int GetMaxSizeOfFullNameForStruct(const QList<AutoCodeParam> &paramList);
    //获取参数类型的最大字节长度
    int GetMaxSizeOfType(const QList<AutoCodeParam> &paramList);
    //获取当前字节数所占用的table数量，如1-4个字节占1个"\t"
    int GetTableCount(int characterCount);
};

#endif // METHOD_H
