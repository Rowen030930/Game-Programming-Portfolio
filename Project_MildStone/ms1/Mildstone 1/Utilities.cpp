// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: Mar 7, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"

using namespace std;

namespace seneca {

    char Utilities::m_delimiter{' '};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		if (next_pos >= str.length() || str[next_pos] == m_delimiter) {
			more = false;
			throw "Delimiter Not Found.";
		}

		size_t delimiterPos = str.find(m_delimiter, next_pos);
		std::string temp = (delimiterPos == std::string::npos) ? str.substr(next_pos) : str.substr(next_pos, delimiterPos - next_pos);

		more = (delimiterPos != std::string::npos);
		next_pos = more ? delimiterPos + 1 : 0;

		setFieldWidth(std::max(getFieldWidth(), temp.length()));

		return temp;
	}

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }


}
