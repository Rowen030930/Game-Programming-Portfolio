// Name: Gyeongroj Oh
// Seneca Student ID: 119140226
// Seneca email: Goh3@myseneca.ca
// Date of completion: April 6, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"

using namespace std;

namespace seneca{

	LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
	{
		Utilities ut;

		ifstream input(file);

		if (!input.is_open())
		{
			throw string("Unable to open file.");
		}

		string data;

		while (!input.eof())
		{
			getline(input, data);
			size_t pos = 0;
			bool more = true;
			string currentStation, nextStation;
			currentStation = ut.extractToken(data, pos, more);

			if (more) {
				nextStation = ut.extractToken(data, pos, more);
			}

			Workstation* currentWorkStation = nullptr;
			Workstation* nextWorkstation = nullptr;

			for_each(stations.begin(), stations.end(), [&currentWorkStation, &nextWorkstation, currentStation, nextStation](Workstation* ws)
				{
					if (ws->getItemName() == currentStation) {
						currentWorkStation = ws;
					}

					else if (ws->getItemName() == nextStation)
					{
						nextWorkstation = ws;
					}
				});

			if (m_activeLine.size() == 0)
			{
				m_firstStation = currentWorkStation;
			}

			currentWorkStation->setNextStation(nextWorkstation);
			m_activeLine.push_back(currentWorkStation);
		}

		input.close();

	}

	void LineManager::reorderStations()
	{
		vector<Workstation*> new_Stations;

		Workstation* last_Station = nullptr;

		unsigned int count = 0;

		while (count < m_activeLine.size())
		{
			for (unsigned int i = 0; i < m_activeLine.size(); i++)
			{
				if (m_activeLine[i]->getNextStation() == last_Station)
				{
					new_Stations.push_back(m_activeLine[i]);
					last_Station = m_activeLine[i];

					count++;
					break;
				}
			}
		}

		reverse(new_Stations.begin(), new_Stations.end());

		m_firstStation = new_Stations[0];
		m_activeLine = new_Stations;
	}

	bool LineManager::run(std::ostream& os)
	{
		static int count = 0;
		count++;

		os << "Line Manager Iteration: " << count << std::endl;

		if (!g_pending.empty())
		{
			(*m_firstStation) += std::move(g_pending.front());
			g_pending.pop_front();
		}

		// Perform fill operation on all stations in the active line
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
			station->fill(os);
			});

		// Attempt to move orders down the line for all stations in the active line
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station) {
			station->attemptToMoveOrder();
			});

		// Check if all stations are empty
		bool isEmpty = std::all_of(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station) {
			return station->isEmpty();
			});

		return isEmpty;
	}

    void LineManager::display(std::ostream& os) const { 
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto station) { 
			station->display(os); 
			}); 
	}
}
