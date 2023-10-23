#ifndef SDDS_ERROR_H 
#define SDDS_ERROR_H  

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

namespace sdds
{
	class Error
	{
		char* m_error{};

	public:
		Error& clear();

		Error();
		Error(const char* t_error);
		Error(const Error& t_error);
		~Error();

		explicit operator bool() const;

		Error& operator=(const Error& right);

		std::ostream& display(std::ostream& ostr) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Error& right);
}

#endif