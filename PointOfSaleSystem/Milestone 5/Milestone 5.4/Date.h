#ifndef SDDS_DATA_H 
#define SDDS_DATA_H  

#include "Error.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

namespace sdds
{
	class Date
	{
		int m_year{};
		int m_month{};
		int m_day{};
		int m_hour{};
		int m_min{};
		bool m_dateOnly{}; // flag 
		Error m_state{};

		void saveDate(int t_year, int t_mon, int t_day, int t_hour = 0, int t_min = 0);
		int daysOfMonth(int year, int month) const;
		void validiation();
		int countDigit(int n) const;
	public:
		Date();
		Date(int t_year, int t_month, int t_day, int t_hour = 0, int t_min = 0);
		Date(const Date& right);

		Date& dateOnly(bool t_dateonly);
		Error error() const;

		bool operator==(const Date& right) const;
		bool operator>=(const Date& right) const;
		bool operator<=(const Date& right) const;
		bool operator!=(const Date& right) const;
		bool operator<(const Date& right) const;
		bool operator>(const Date& right) const;

		explicit operator bool() const;

		std::ostream& display(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
	std::ostream& operator<<(std::ostream& ostr, const Date& right);
	std::istream& operator>>(std::istream& istr, Date& right);
}

#endif