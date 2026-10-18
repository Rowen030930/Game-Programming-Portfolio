// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: Mar 7, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <iostream>
#include <string>

namespace seneca {
	class Utilities {
		size_t m_widthField{ 1 };
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		void trim(std::string& str);
	};
}
#endif
