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
    void WriteConstructorCPP(std::ostream &os, const AutoCodeParam &param);
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
    //头文件的类定义
    void WriteClassDefinitionHeader(std::ostream &os, const AutoCodeParam &param);
    //初始化默认值，用于构造函数中
    void WriteDefaultValue(std::ostream &os, const QList<AutoCodeParam> &paramList);
};

#endif // METHOD_H
