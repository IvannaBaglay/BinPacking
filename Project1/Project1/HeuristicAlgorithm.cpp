#include "HeuristicAlgorithm.h"
#include <Container.h>
#include <Constants.h>
#include <Box.h>

#include <queue>

struct PlacementSelection
{
	struct Size
	{
		int lenght_x;
		int width_y;
		int height_z;
	};
	struct Coordination
	{
		int x;
		int y;
		int z;
	};
};

HeuristicAlgorithm::HeuristicAlgorithm(const std::vector<int> bps, const std::vector<int> cls)
	: m_BPS(bps), m_CLS(cls)
{
}

void HeuristicAlgorithm::Start()
{

	//Let OC be the list of Opened Containers 
	//int OC = 0;
	std::vector<int> openedContainers; // is empty on the first iteration
	std::vector<Container> emptyMaximalSpace; // free space be like as a small containers in one large// Maybe Box and Containers can be one class or inharitanced from one // Before start algorithm it is an empty
	while (!m_BPS.empty())
	{
		// Let P be a be a priority queue of candidate placements with the priority defined in section (Placement selection)
		std::queue<PlacementSelection> placementSelection;
		bool boxplaced = false;
		//for each opened container c in OC
		for (auto& container : openedContainers)
		{
			//Let EMS by empty maximal spaces in c
			int j = 0; // мабуть краще починати з 0 // in orifinal j = 1
			while (j <= emptyMaximalSpace.size() and boxplaced == false)
			{
				int k = j + K_E; // ???? For what I need K_E
				while (j < k and j < emptyMaximalSpace.size()) // мабуть для С++ j < EMS.size()
				{
					for (int i = 0; i < K_B && i < m_BPS.size(); i++) // мабуть i = 0 and i < BPS.size()
					{
						// Need create list with 6 orientation for box
						std::list<Box> boxOrientations = CreateAllBoxOrientation(m_BPS.at(i));
						for (auto& boxOrientation : boxOrientations)
						{
							PlacementSelection placement;
							if (CanBoxBePlacedInSpace(boxOrientation, emptyMaximalSpace.at(j), placement)) // box BPSi can be placed in EMS with orientation b0 then 
							{
								//Add this placement combination to P
								placementSelection.push(placement);
							}
						}

					}
					j++;
				}
				if (!placementSelection.empty()) // P.size() = 0
				{
					// Make the placement indicted by P1
					MakePlacementsIndicted();
					//Update EMSs
					UpdateEMS(emptyMaximalSpace);
					boxplaced = true;
				}
			}
			if (boxplaced == true)
			{
				break;
			}
		}

		while (boxplaced == false && !m_CLS.empty()) // CLS != 0 and boxplaced = false
		{
			// Let EMS be the initial emplty space in CLS1
			Container emptyMaxSpace = GetContainer(0);
			//OC = OC && CLS1(взяти спільне)
			//CLS = CLS \ CLS1(викинути з CLS те що є у CLS1)
			for (int i = 1; i < K_B && i < m_BPS.size(); i++) // i = 1 to kb and i < = BPS.size()
			{
			std::list<Box> boxOrientations = CreateAllBoxOrientation(m_BPS.at(i));
				for (auto& boxOrientation : boxOrientations) // for all 6 orientation bo
				{
					PlacementSelection placement;
					if (CanBoxBePlacedInSpace(boxOrientation, emptyMaxSpace, placement)) //if (Box BPSi can be placed in EMS with orientation b0)
					{
						//Add this placement combination to P
						placementSelection.push(placement);
					}
				}
			}
			if (!placementSelection.empty()) // P.size() = 0
			{
				// Make the placement indicted by P1
				MakePlacementsIndicted();
				//Update EMSs
				UpdateEMS(emptyMaximalSpace);
				boxplaced = true;
			}
		}
		if (boxplaced = false)
		{
			return; // return nullptr;
		}

	}

	//return Packing Solution; ?????
}

void HeuristicAlgorithm::MakePlacementsIndicted()
{
}

std::list<Box> HeuristicAlgorithm::CreateAllBoxOrientation(int boxIndex)
{
	return std::list<Box>();
}

bool HeuristicAlgorithm::CanBoxBePlacedInSpace(const Box& box, const Container& space, PlacementSelection& placement)
{
	return false;
}

const Container& HeuristicAlgorithm::GetContainer(int containerIndex)
{
	m_CLS.at(containerIndex);
	return Container();
}

void HeuristicAlgorithm::UpdateEMS(std::vector<Container>& emptySpaces)
{

}
