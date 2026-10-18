// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: April 6, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

using namespace std;

namespace seneca {
    deque<CustomerOrder> g_pending;
    deque<CustomerOrder> g_completed;
    deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(string str) : Station(str){}

	void Workstation::fill(ostream& os) {
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		if (isEmpty())
		{
			return true;
		}
		else
		{
			if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0)
			{
				if (m_pNextStation == nullptr) {

					if (m_orders.front().isOrderFilled())
					{
						g_completed.emplace_back(move(m_orders.front()));
					}
					else
					{
						g_incomplete.emplace_back(move(m_orders.front()));
					}
				}
				else
				{
					(*m_pNextStation) += move(m_orders.front());
				}

				m_orders.pop_front();
				return true;
			}
			return false;
		}
	}


    void Workstation::setNextStation(Workstation* station)
    {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(ostream& os) const {
        os << getItemName(); os << " --> "; 
        
        if (m_pNextStation == nullptr) {
            os << "End of Line";
        }
        else { 
            os << m_pNextStation->getItemName(); 
        }
        
        os << endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.emplace_back(move(newOrder));
        return *this;
    }

	bool Workstation::isEmpty()
	{
		return m_orders.empty();
	}


}