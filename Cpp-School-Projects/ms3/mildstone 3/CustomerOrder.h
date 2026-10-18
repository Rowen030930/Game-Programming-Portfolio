// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: Mar 14, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H 
#define SENECA_CUSTOMERORDER_H


#include "Station.h" 

namespace seneca {

	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name;
		std::string m_product;
		unsigned int m_cntItem;
		Item** m_lstItem;
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& src);
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif