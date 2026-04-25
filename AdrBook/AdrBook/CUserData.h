#pragma once
#include <afx.h>
class CUserData :
    public CObject
{
public:
    CUserData(CString name, CString phone)
    {
        m_strName = name;
        m_strPhone = phone;
    }

    const CString* GetName()
    {
        return &m_strName;
    }

    const CString* GetPhone()
    {
        return &m_strPhone;
    }


private:
    CString m_strName;
    CString m_strPhone;
};

