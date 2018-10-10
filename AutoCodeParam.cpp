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
    m_name = name;
}

void AutoCodeParam::SetClassName(const QString &className)
{
    m_className = className;
}

void AutoCodeParam::SetType(const QString &type)
{
    m_type = type;
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

QString AutoCodeParam::GetFullName() const
{
    QString fullName = m_prefix;
    QString tmpName = m_name;
    if (fullName.size() > 0)
    {
        if (tmpName.size() > 0)
        {
            tmpName.replace(0,1,tmpName[0].toUpper());;
        }
    }
    fullName += tmpName;
    fullName += m_suffix;
    return fullName;
}

