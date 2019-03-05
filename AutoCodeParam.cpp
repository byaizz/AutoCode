#include "AutoCodeParam.h"

AutoCodeParam::AutoCodeParam()
{

}

AutoCodeParam::~AutoCodeParam()
{

}
//set parameter
void AutoCodeParam::SetName(const QString &name)
{
    int indexStart = name.indexOf('[');
    int indexEnd = name.indexOf(']');
    if (indexStart > 0 && indexEnd > 0)
    {
        m_name = name.left(indexStart);
        m_elementCount = name.mid(indexStart,indexEnd - indexStart + 1);
    }
    else
    {
        m_name = name;
        m_elementCount = "";
    }

}

void AutoCodeParam::SetClassName(const QString &className)
{
    m_className = className;
}

void AutoCodeParam::SetType(const QString &type)
{
    m_type = type;
}

void AutoCodeParam::SetElementCount(const QString &elementCount)
{
    m_elementCount = elementCount;
}

void AutoCodeParam::SetPrefix(const QString &prefix)
{
    m_prefix = prefix;
}

void AutoCodeParam::SetSuffix(const QString &suffix)
{
    m_suffix = suffix;
}

void AutoCodeParam::SetNotes(const QString &notes)
{
    m_notes = notes;
}

void AutoCodeParam::SetAuthor(const QString &author)
{
    m_author = author;
}

void AutoCodeParam::SetCreateDate(const QString &createDate)
{
    m_createDate = createDate;
}

void AutoCodeParam::SetDefaultValue(const QString &defaultValue)
{
    m_defaultValue = defaultValue;
}

void AutoCodeParam::SetStructName(const QString &structName)
{
    m_structName = structName;
}

void AutoCodeParam::SetStructAliasName(const QString &structAliasName)
{
    m_structAliasName = structAliasName;
}

void AutoCodeParam::SetStructVariableName(const QString &structVariableName)
{
    m_structVariableName = structVariableName;
}

//get parameter
QString AutoCodeParam::GetName() const
{
    return m_name;
}

QString AutoCodeParam::GetClassName() const
{
    return m_className;
}

QString AutoCodeParam::GetType() const
{
    return m_type;
}

QString AutoCodeParam::GetElementCount() const
{
    return m_elementCount;
}

QString AutoCodeParam::GetPrefix() const
{
    return m_prefix;
}

QString AutoCodeParam::GetSuffix() const
{
    return m_suffix;
}

QString AutoCodeParam::GetNotes() const
{
    return m_notes;
}

QString AutoCodeParam::GetAuthor() const
{
    return m_author;
}

QString AutoCodeParam::GetCreateDate() const
{
    return m_createDate;
}

QString AutoCodeParam::GetDefaultValue() const
{
    return m_defaultValue;
}

QString AutoCodeParam::GetFullNameForStruct() const
{
    //根据变量类型设置类型前缀
    //double-d  float-f int-i INT16-i
    QString flag;
    if (m_type == "INT16" || m_type == "int")
    {
        flag = "i";
    }
    else if (m_type == "double")
    {
        flag = "d";
    }
    else if (m_type == "float")
    {
        flag = "f";
    }
    else
    {
        //do nothing
    }
    QString fullNameForStruct =flag + m_prefix;
    QString tmpName = m_name;
    if (fullNameForStruct.size() > 0)
    {
        if (tmpName.size() > 0)
        {
            tmpName.replace(0,1,tmpName[0].toUpper());;
        }
    }
    fullNameForStruct += tmpName;
    fullNameForStruct += m_suffix;
    return fullNameForStruct;
}

QString AutoCodeParam::GetFullNameForClass() const
{
    QString fullNameForClass = "m_";
    fullNameForClass += GetFullNameForStruct();
    return fullNameForClass;
}

QString AutoCodeParam::GetStructName() const
{
    return m_structName;
}

QString AutoCodeParam::GetStructAliasName() const
{
    return m_structAliasName;
}

QString AutoCodeParam::GetStructVariableName() const
{
    return m_structVariableName;
}

