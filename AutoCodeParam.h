#ifndef AUTOCODEPARAM_H
#define AUTOCODEPARAM_H

#include <QString>

class AutoCodeParam
{
public:
    AutoCodeParam();
    ~AutoCodeParam();
    //set parameter
    void SetName(const QString &name);
    void SetClassName(const QString &className);
    void SetType(const QString &type);
    void SetPrefix(const QString &prefix);
    void SetSuffix(const QString &suffix);
    void SetNotes(const QString &notes);
    void SetAuthor(const QString &author);
    void SetCreateDate(const QString &createDate);
    void SetDefaultValue(const QString &defaultValue);
    //get parameter
    QString GetName() const;
    QString GetClassName() const;
    QString GetType() const;
    QString GetPrefix() const;
    QString GetSuffix() const;
    QString GetNotes() const;
    QString GetAuthor() const;
    QString GetCreateDate() const;
    QString GetDefaultValue() const;
    QString GetFullName() const;
private:
    QString m_className;        //参数类名称
    QString m_name;             //参数名称
    QString m_type;             //参数类型
    QString m_prefix;           //前缀
    QString m_suffix;           //后缀
    QString m_notes;            //注释内容
    QString m_author;           //作者
    QString m_createDate;       //创建日期
    QString m_defaultValue;     //默认值
};

#endif // AUTOCODEPARAM_H
