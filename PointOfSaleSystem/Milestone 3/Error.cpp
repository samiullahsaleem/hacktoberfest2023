#include "Error.h"

using namespace std;

namespace sdds
{
    Error& Error::clear()
    {
        if(m_error!= NULL)
            delete[] m_error;
        m_error = nullptr;
        return *this;
    }

    Error::Error()
    {
        m_error = NULL;
        //clear();
    }

    Error::Error(const char* t_error)
    {
        bool checkError = t_error && strlen(t_error);
        if (checkError)
        {
            m_error = new char[strlen(t_error) + 1];
            strcpy(m_error, t_error);
        }
    }


    Error::Error(const Error& right)
    {
        bool checkError = right.m_error && strlen(right.m_error);
        if (checkError)
        {
            m_error = new char[strlen(right.m_error) + 1];
            strcpy(m_error, right.m_error);
        }
    }

    const char* Error::GetError(){
        return m_error;
    }

    Error::~Error()
    {
        clear();
    }

    Error::operator bool() const
    {
        bool checkError = m_error && strlen(m_error);
        if (checkError)
            return true;
        return false;
    }

    Error& Error::operator=(const Error& right)
    {
        clear();
        bool checkError = right.m_error && strlen(right.m_error);
        if (checkError)
        {
            m_error = new char[strlen(right.m_error) + 1];
            strcpy(m_error, right.m_error);
        }
        return *this;
    }

    void Error::setError(const char* t_error){
        m_error = new char[strlen(t_error) + 1];
        strcpy(m_error, t_error);
    }

    std::ostream& Error::display(std::ostream& ostr) const
    {
        if (m_error)
            ostr << m_error;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const Error& right)
    {
        return right.display(ostr);
    }
}