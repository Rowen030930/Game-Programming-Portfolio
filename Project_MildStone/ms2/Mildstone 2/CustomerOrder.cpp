// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: Mar 14, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "CustomerOrder.h"

using namespace std;

namespace seneca {
	size_t CustomerOrder::m_widthField;

	CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cnt(0), m_lstItem(nullptr){

	}

	CustomerOrder::CustomerOrder(const string& src) {
		Utilities u{};
		size_t pos = 0;
		bool more = true;

		m_name = u.extractToken(src, pos, more);
		m_product = u.extractToken(src, pos, more);

		// Count the occurrences of the delimiter
		size_t delimiterCount = 0;
		for (char c : src) {
			if (c == u.getDelimiter()) {
				delimiterCount++;
			}
		}
		m_cnt = delimiterCount - 1;

		if (m_cnt == 0)
			return;

		m_lstItem = new Item * [m_cnt];

		for (size_t i = 0; i < m_cnt; i++) {
			m_lstItem[i] = new Item(u.extractToken(src, pos, more));
		}

		m_widthField = (u.getFieldWidth() > m_widthField) ? u.getFieldWidth() : m_widthField;
	}


	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "deleted Copy Constructer";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept : m_cnt(0), m_lstItem(nullptr) {
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			m_name = src.m_name;
			m_product = src.m_product;

			for (size_t i = 0; i < m_cnt; i++) {
				delete m_lstItem[i];
			}

			delete[] m_lstItem;
			m_lstItem = nullptr;
			m_widthField = src.m_widthField;
			m_cnt = src.m_cnt;
			m_lstItem = src.m_lstItem;

			src.m_name = "";
			src.m_product = "";
			src.m_lstItem = nullptr;
			src.m_cnt = 0;

		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cnt; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool seneca::CustomerOrder::isOrderFilled() const {
		for (size_t i = 0; i < m_cnt; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;  
			}
		}
		return true; 
	}

	bool CustomerOrder::isItemFilled(const string& itemName) const {
		bool is_filled = true; 
		
		for (size_t i = 0u; i < m_cnt && is_filled; i++) { 
			is_filled = m_lstItem[i]->m_itemName == itemName ? m_lstItem[i]->m_isFilled : true; 
			
		}
		
		return is_filled;
	}

	void CustomerOrder::fillItem(Station& station, ostream& os) {
		bool itemHandled = false;
		bool itemUnfilled = false;

		for (size_t i = 0; i < m_cnt; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				itemHandled = true;

				if (!m_lstItem[i]->m_isFilled) {
					if (station.getQuantity() > 0) {
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						station.updateQuantity(); 
						os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
					}
					else {
			
						itemUnfilled = true;
					}
				}
				break; 
			}
		}

		if (!itemHandled) {
			return;
		}

		if (itemUnfilled) {
			os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
		}
	}


	
	void CustomerOrder::display(ostream& os) const {
		os << left << m_name << " - " << m_product << endl;

		for (size_t i = 0; i < m_cnt; i++) {

			os << "[";
			os.width(6);
			os.fill('0');
			os << right << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os.width(m_widthField);
			os.fill(' ');
			os << left << m_lstItem[i]->m_itemName;
			os << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << endl;
		}
	}


}


