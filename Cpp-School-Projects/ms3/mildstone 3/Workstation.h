// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: April 6, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"


namespace seneca {
	extern std::deque<CustomerOrder> g_pending; 
	extern std::deque<CustomerOrder> g_completed; 
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{ nullptr };
	public:
		Workstation() = default;
		Workstation(std::string str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		bool isEmpty();
	};
}
#endif