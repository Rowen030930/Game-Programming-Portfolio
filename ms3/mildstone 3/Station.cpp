// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: Mar 7, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"

using namespace std;

namespace seneca {
    size_t Station::m_widthField{ 0 };
    size_t Station::id_generator{ 0 };

    Station::Station(const std::string& str) {
        Utilities utility;
        m_id = ++Station::id_generator;
        size_t next_pos = 0; bool more = true;
        m_itemName = more ? utility.extractToken(str, next_pos, more) : "";
        m_serialNumber = more ? std::stoi(utility.extractToken(str, next_pos, more)) : 0;
        m_quantity = more ? std::stoi(utility.extractToken(str, next_pos, more)) : 0;
        m_widthField = (utility.getFieldWidth() > m_widthField) ? utility.getFieldWidth() : m_widthField;
        m_description = more ? utility.extractToken(str, next_pos, more) : "";

        m_description.erase(0, m_description.find_first_not_of(" \t\r\n"));
        m_description.erase(m_description.find_last_not_of(" \t\r\n") + 1);

    }


    const std::string& Station::getItemName() const
    {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const
    {
        return m_quantity;
    }

    void Station::updateQuantity()
    {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os.width(3);
        os.setf(ios::right);
        os.fill('0');
        os << m_id;
        os << " | ";
        os.unsetf(ios::right);
        os.setf(ios::left);
        os.width(m_widthField);
        os.fill(' ');
        os << m_itemName;
        os << " | ";
        os.width(6);
        os.setf(ios::right);
        os.fill('0');
        os << m_serialNumber;
        os << " | ";

        if (full == false) {
            os << endl;
        }
        else {
            os.width(4);
            os.setf(ios::right);
            os.fill(' ');
            os << m_quantity;
            os << " | ";
            os << m_description;
            os << endl;

        }

    }
}
