#ifndef METHOD_H
#define METHOD_H

#include <iostream>
#include <AutoCodeParam.h>

class Method
{
public:
    Method();
    ~Method();
    void WriteSetFuncCPP(std::ostream &os, const AutoCodeParam &param);
    void WriteGetFuncCPP(std::ostream &os, const AutoCodeParam &param);
    void WriteConstructorCPP(std::ostream &os, const AutoCodeParam &param);
    void WriteDestructorCPP(std::ostream &os, const AutoCodeParam &param);
    void WriteSetFuncHeader(std::ostream &os, const AutoCodeParam &param);
    void WriteGetFuncHeader(std::ostream &os, const AutoCodeParam &param);
    void WriteConstructorHeader(std::ostream &os, const AutoCodeParam &param);
    void WriteDestructorHeader(std::ostream &os, const AutoCodeParam &param);
    void WriteClassDefinitionHeader(std::ostream &os, const AutoCodeParam &param);
};

#endif // METHOD_H
