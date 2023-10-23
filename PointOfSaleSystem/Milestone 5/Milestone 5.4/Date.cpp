#include "Date.h"
#include "POS.h"
#include "Error.h"

using namespace std;

namespace sdds
{
	// SECTION: privately member function s
	// function saving date into the current object
	void Date::saveDate(int t_year, int t_month, int t_day, int t_hour, int t_min)
	{
		m_year = t_year;
		m_month = t_month;
		m_day = t_day;
		m_hour = t_hour;
		m_min = t_min;
	}

	// return the number of days in the provide month and year
	int Date::daysOfMonth(int year, int month) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = month >= 1 && month <= 12 ? month : 13;
		mon--;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	// function validiating the date
	void Date::validiation()
	{
		bool ok = true;
		if (ok && (m_year < MIN_YEAR || m_year > MAX_YEAR))
		{
			Error temp("Invalid Year");
			m_state = temp;
			ok = false;
		}
		if (ok && (m_month < 1 || m_month > 12))
		{
			Error temp("Invalid Month");
			m_state = temp;
			ok = false;
		}
		if (ok && (m_day < 1 || m_day > daysOfMonth(m_year, m_month)))
		{
			Error temp("Invalid Day");
			m_state = temp;
			ok = false;
		}
		if (ok && (m_hour < 0 || m_hour > 23))
		{
			Error temp("Invalid Hour");
			m_state = temp;
			ok = false;
		}
		if (ok && (m_min < 0 || m_min > 59))
		{
			Error temp("Invlid Minute");
			m_state = temp;
		}
	}

	// return the number of digits of a integer
	int Date::countDigit(int n)  const
	{
		int count = 0;
		if (n < 0) count = 1;
		while (n)
		{
			n /= 10;
			count++;
		}
		return count;
	}

	// SECTION: constructors
	// default constructor
	Date::Date()
	{
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		saveDate(lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min);
	}

	// constructor initialize the current system date
	Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_min)
	{
		if (!t_hour && !t_min)
			this->m_dateOnly = true;
		else
			this->m_dateOnly = false;
		saveDate(t_year, t_month, t_day, t_hour, t_min);
		validiation();
	}

	// constructor copying the state of another object
	Date::Date(const Date& right)
	{
		this->m_dateOnly = right.m_dateOnly;
		saveDate(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_min);
		validiation();
	}

	// SECTION: publicly member functions
	// set the date of object to date only
	Date& Date::dateOnly(bool t_dateonly)
	{
		m_dateOnly = t_dateonly;
		if (t_dateonly)
		{
			m_hour = 0;
			m_min = 0;
		}
		return *this;
	}

	// return the reference of an error object
	Error Date::error() const
	{
		return m_state;
	}

	// SECTION operator overloading 
	// operator ==, comparing 2 dates
	bool Date::operator==(const Date& right) const
	{
		ostringstream Astr, Bstr;
		Astr << *this;
		Bstr << right;
		return (Astr.str() == Bstr.str());
	}

	// operator >=, comparing 2 dates
	bool Date::operator>=(const Date& right) const
	{
		ostringstream Astr, Bstr;
		Astr << *this;
		Bstr << right;
		return (Astr.str() >= Bstr.str());
	}

	// operator <=, comparing 2 dates
	bool Date::operator<=(const Date& right) const
	{
		ostringstream Astr, Bstr;
		Astr << *this;
		Bstr << right;
		return (Astr.str() <= Bstr.str());
	}

	// operator !=, comparing 2 dates
	bool Date::operator!=(const Date& right) const
	{
		ostringstream Astr, Bstr;
		Astr << *this;
		Bstr << right;
		return (Astr.str() != Bstr.str());
	}

	// operator <, comparing 2 dates
	bool Date::operator<(const Date& right) const
	{
		ostringstream Astr, Bstr;
		Astr << *this;
		Bstr << right;
		return (Astr.str() < Bstr.str());
	}

	// operator >, comparing 2 dates
	bool Date::operator>(const Date& right) const
	{
		ostringstream Astr, Bstr;
		Astr << *this;
		Bstr << right;
		return (Astr.str() > Bstr.str());
	}

	// SECTION: conversion bool operator
	Date::operator bool() const
	{
		if (m_state)
			return false;
		return true;
	}

	// SECTION: display and read function 
	// function extracting from instance variables to ostream
	std::ostream& Date::display(std::ostream& ostr) const
	{
		if (!*this)
		{
			m_state.display(std::cout);
			ostr << "(";
		}
		ostr << m_year << "/";
		if (countDigit(m_month) == 1 || m_month == 0)
			ostr << 0;
		ostr << m_month << "/";
		if (countDigit(m_day) == 1 || m_day == 0)
			ostr << 0;
		ostr << m_day;
		if (!m_dateOnly)
		{
			ostr << ", ";
			if (countDigit(m_hour) == 1 || m_hour == 0)
				ostr << 0;
			ostr << m_hour << ":";
			if (countDigit(m_min) == 1 || m_min == 0)
				ostr << 0;
			ostr << m_min;
		}
		if (!*this)
		{
			ostr << ")";
		}
		return ostr;
	}

	// function inserting from istream into instance variables
	std::istream& Date::read(std::istream& istr)
	{
		m_state.clear();
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_hour = 0;
		m_min = 0;

		bool ok = true;
		istr >> m_year;
		if (istr.fail())
		{
			Error temp("Cannot read year entry");
			m_state = temp;
			ok = false;
		}

		if (ok)
		{
			istr.ignore();
			istr >> m_month;
			if (istr.fail())
			{
				Error temp("Cannot read month entry");
				m_state = temp;
				ok = false;
			}
		}

		if (ok)
		{
			istr.ignore();
			istr >> m_day;
			if (istr.fail())
			{
				Error temp("Cannot read day entry");
				m_state = temp;
				ok = false;
			}
		}

		if (!m_dateOnly)
		{
			if (ok)
			{
				istr.ignore();
				istr >> m_hour;
				if (istr.fail())
				{
					Error temp("Cannot read hour entry");
					m_state = temp;
					ok = false;
				}
			}

			if (ok)
			{
				istr.ignore();
				istr >> m_min;
				if (istr.fail())
				{
					Error temp("Cannot read minute entry");
					m_state = temp;
					ok = false;
				}
			}
		}
		if (!m_state)
			validiation();
		return istr;
	}

	// SECTION: helper function 
	// << operator overloading
	std::ostream& operator<<(std::ostream& ostr, const Date& right)
	{
		return right.display(ostr);
	}

	// >> operator overloading
	std::istream& operator>>(std::istream& istr, Date& right)
	{
		return right.read(istr);
	}
}