#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <iostream> 
#include <string>
#include <fstream>
// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: April 6, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <vector> 
#include <queue>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <iterator> 
#include "Workstation.h" 
#include "CustomerOrder.h" 
#include "Station.h"

namespace seneca {
	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder;
		Workstation* m_firstStation{nullptr};
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif