#include "HeuristicAlgorithm.h"
#include <Container.h>
#include <Constants.h>
#include <Box.h>
#include <Pool.h>
#include <PlacementSelection.h>
#include <ExtremePoint.h>
#include <ResultWritter.h>

#include <queue>
#include <iterator>



HeuristicAlgorithm::HeuristicAlgorithm(const std::vector<int>& bps, const std::vector<int>& cls)
	: m_BPS(bps), m_CLS(cls)
{
}

int HeuristicAlgorithm::Start()
{
	int fitness = 0;
	//Let OC be the list of Opened Containers 
	//int OC = 0;
	std::vector<int> openedContainers; // is empty on the first iteration
	//std::vector<Container> emptyMaximalSpace; // free space be like as a small containers in one large// Maybe Box and Containers can be one class or inharitanced from one // Before start algorithm it is an empty
	while (!m_BPS.empty())
	{
		// Let P be a be a priority queue of candidate placements with the priority defined in section (Placement selection)
		std::vector<PlacementSelection> placementSelection;
		bool boxplaced = false;
		//for each opened container c in OC
		for (auto& container : openedContainers)
		{
			//Let EMS by empty maximal spaces in c

			std::vector<Container> emptyMaximalSpace;
			CopyEmptySpacesFromContainer(emptyMaximalSpace, container);

			//Copy EP from container to temp vector
			std::vector<ExtremePoint> extremePoints;
			CopyExtremePointsFromContainer(extremePoints, container);

			int j = 0; // мабуть краще починати з 0 // in orifinal j = 1
			while (j < emptyMaximalSpace.size() && boxplaced == false)
			{
				int k = j + K_E; // ???? For what I need K_E
				while (j < k && j < emptyMaximalSpace.size()) // мабуть для С++ j < EMS.size()
				{
					for (int i = 0; i < K_B && i < m_BPS.size(); i++) // мабуть i = 0 and i < BPS.size()
					{
						// Need create list with 6 orientation for box
						std::list<Box> boxOrientations = CreateAllBoxOrientation(m_BPS.at(i));
						for (auto& boxOrientation : boxOrientations)
						{
							PlacementSelection placement;
							if (CanBoxBePlacedInSpace(boxOrientation, emptyMaximalSpace.at(j), placement, container)) // box BPSi can be placed in EMS with orientation b0 then 
							{
								//Add this placement combination to P
								placementSelection.push_back(placement);
							}


							//if (CanBoxBePlacedInEP(boxOrientation, extremePoint, placement, container)) //if (Box BPSi can be placed in EMS with orientation b0)
							//{
							//	//Add this placement combination to P
							//	placementSelection.push_back(placement);
							//}
						}

					}
					j++;
				}
				if (!placementSelection.empty()) // P.size() = 0
				{
					// Make the placement indicted by P1
					PlacementSelection placement =  MakePlacementsIndicted(placementSelection);
					//Update EMSs
					UpdateEMS(emptyMaximalSpace, placement, container);
					UpdateBPS(placement.index);



					fitness = CalculateFitness(emptyMaximalSpace);
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
			// Let EMS be the initial emplty space in CLS1 (first container in list)
			int firstContainerIndex = GetFirstContainerInList().GetIndex();

			// TODO: Can be optimize 
			//OC = OC && CLS1(взяти спільне)
			openedContainers = ConcatenateVectors(openedContainers, firstContainerIndex);
			//CLS = CLS \ CLS1(викинути з CLS те що є у CLS1)

			m_CLS = DifferentceVectors(m_CLS, firstContainerIndex);
			for (int i = 1; i < K_B && i < m_BPS.size(); i++) // i = 1 to kb and i < = BPS.size() ???????????  Why I need here K_b
			{
			std::list<Box> boxOrientations = CreateAllBoxOrientation(m_BPS.at(i));
				for (auto& boxOrientation : boxOrientations) // for all 6 orientation bo
				{
					PlacementSelection placement;
					if (CanBoxBePlacedInSpace(boxOrientation, GetContainer(firstContainerIndex), placement, firstContainerIndex)) //if (Box BPSi can be placed in EMS with orientation b0)
					{
						//Add this placement combination to P
						placementSelection.push_back(placement);
					}


					//if (CanBoxBePlacedInEP(boxOrientation, GetContainer(firstContainerIndex), placement, firstContainerIndex)) //if (Box BPSi can be placed in EMS with orientation b0)
					//{
					//	//Add this placement combination to P
					//	placementSelection.push_back(placement);
					//}



				}
			}
			if (!placementSelection.empty()) // P.size() = 0
			{
				// Make the placement indicted by P1
				PlacementSelection placement = MakePlacementsIndicted(placementSelection);
				//Update EMS // One container that was empty

				std::vector<Container> emptyMaximalSpace;
				UpdateEMS(emptyMaximalSpace, placement, firstContainerIndex);
				UpdateBPS(placement.index);

				fitness = CalculateFitness(emptyMaximalSpace);
				boxplaced = true;
			}
		}
		if (boxplaced == false)
		{
			return INVALID_FITNESS;
		}

	}

	return fitness;
}

PlacementSelection HeuristicAlgorithm::MakePlacementsIndicted(std::vector<PlacementSelection>& placementsSelecion)
{
	// Sort by size of EMS that is placementsSelectionSize

	std::sort(placementsSelecion.begin(), placementsSelecion.end(), [](const PlacementSelection& placementSelecion1, const PlacementSelection& placementSelecion2)
	{
		return placementSelecion1.coordination.x < placementSelecion2.coordination.x;
	});

	return *placementsSelecion.begin();
}

void HeuristicAlgorithm::CopyEmptySpacesFromContainer(std::vector<Container>& emptySpaces, int containerIndex)
{
	const std::vector<Container>& EMSContainer = GetEMSContainer(containerIndex);

	emptySpaces.clear();
	emptySpaces.reserve(EMSContainer.size());
	std::copy(EMSContainer.begin(), EMSContainer.end(), std::back_inserter(emptySpaces));
}

void HeuristicAlgorithm::CopyExtremePointsFromContainer(std::vector<ExtremePoint>& emptySpaces, int containerIndex)
{
	const std::vector<ExtremePoint>& EPContainer = GetEPContainer(containerIndex);

	emptySpaces.clear();
	emptySpaces.reserve(EPContainer.size());
	std::copy(EPContainer.begin(), EPContainer.end(), std::back_inserter(emptySpaces));
}

int HeuristicAlgorithm::CalculateFitness(const std::vector<Container>& emptySpaces)
{
	int result = 0;
	for (const auto& space : emptySpaces)
	{
		result = space.GetVolume();
	}
	return result;
}

std::list<Box> HeuristicAlgorithm::CreateAllBoxOrientation(int boxIndex)
{
	const Box& box = PoolManager::GetInstance()->GetBoxByIndex(boxIndex);
	const int index = box.GetIndex();
	const int x = box.GetSizeX();
	const int y = box.GetSizeY();
	const int z = box.GetSizeZ();

	return std::list<Box>
	{
		Box(x, y, z, index),
		Box(x, z, y, index),
		Box(y, z, x, index),
		Box(y, x, z, index),
		Box(z, x, y, index),
		Box(z, y, x, index),
	};
}

bool HeuristicAlgorithm::CanBoxBePlacedInSpace(const Box& box, const Container& space, PlacementSelection& placement, int containerIndex)
{
	bool result = true;

	// Check placement
	result &= box.GetSizeX() <= space.GetLenghtX();
	result &= box.GetSizeY() <= space.GetWidthY();
	result &= box.GetSizeZ() <= space.GetHeightZ();

	if (result) // save if OK
	{
		placement.size.lenght_x = box.GetSizeX();
		placement.size.width_y = box.GetSizeY();
		placement.size.height_z = box.GetSizeZ();

		placement.coordination.x = space.GetX();
		placement.coordination.y = space.GetY();
		placement.coordination.z = space.GetZ();

		placement.index = box.GetIndex();
		placement.containerIndex = containerIndex;
	}

	return result;
}

bool HeuristicAlgorithm::CanBoxBePlacedInEP(const Box& box, const ExtremePoint& point, PlacementSelection& placement, int containerIndex)
{
	bool result = true;

	const Container& openedContainer = GetContainer(containerIndex);

	int containerSizeX = openedContainer.GetLenghtX();
	int containerSizeY = openedContainer.GetWidthY();
	int containerSizeZ = openedContainer.GetHeightZ();


	// Check placement
	result &= point.X_Coord + box.GetSizeX() <= containerSizeX;
	result &= point.Y_Coord + box.GetSizeY() <= containerSizeY;
	result &= point.Z_Coord + box.GetSizeZ() <= containerSizeZ;

	if (result) // save if OK
	{
		placement.size.lenght_x = box.GetSizeX();
		placement.size.width_y = box.GetSizeY();
		placement.size.height_z = box.GetSizeZ();

		placement.coordination.x = point.X_Coord;
		placement.coordination.y = point.Y_Coord;
		placement.coordination.z = point.Z_Coord;

		placement.index = box.GetIndex();
		placement.containerIndex = containerIndex;
	}

	return result;
}

const Container& HeuristicAlgorithm::GetContainer(int containerIndex)
{
	assert(containerIndex > 0, "Error Unknown index");
	return PoolManager::GetInstance()->GetContainerByIndex(containerIndex);
}

const std::vector<Container>& HeuristicAlgorithm::GetEMSContainer(int containerIndex)
{
	assert(containerIndex > 0, "Error Unknown index");
	return PoolManager::GetInstance()->GetContainerEMS(containerIndex);
}

const std::vector<ExtremePoint>& HeuristicAlgorithm::GetEPContainer(int containerIndex)
{
	assert(containerIndex > 0, "Error Unknown index");
	return PoolManager::GetInstance()->GetContainerEP(containerIndex);
}

const Container& HeuristicAlgorithm::GetFirstContainerInList()
{
	int index = m_CLS.at(0);
	return index <= 0 ? Container() : PoolManager::GetInstance()->GetContainerByIndex(index);
}

std::vector<int> HeuristicAlgorithm::ConcatenateVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector)
{
	std::vector<int>  resultVector;
	std::merge(firstVector.begin(), firstVector.end(),
		secondVector.begin(), secondVector.end(),
		std::back_inserter(resultVector));

	std::vector<int>::iterator pte = std::unique(resultVector.begin(), resultVector.end());
	// dups now in [pte, resultVector.end()), so optionally erase:
	resultVector.erase(pte, resultVector.end());

	return resultVector;
}

std::vector<int> HeuristicAlgorithm::ConcatenateVectors(const std::vector<int>& firstVector, int containerIndex)
{
	std::vector<int>  resultVector(firstVector);

	const auto iter = std::find_if(resultVector.cbegin(), resultVector.cend(), [&containerIndex](int openedIndex) { return openedIndex == containerIndex; });

	if (iter == resultVector.cend())
	{
		resultVector.push_back(containerIndex);
	}

	return resultVector;
}
std::vector<int> HeuristicAlgorithm::DifferentceVectors(const std::vector<int>& firstVector, int containerIndex)
{
	std::vector<int>  resultVector(firstVector);

	const auto iter = std::find_if(resultVector.cbegin(), resultVector.cend(), [&containerIndex](int openedIndex) { return openedIndex == containerIndex; });

	if (iter != resultVector.cend())
	{
		resultVector.erase(iter);
	}

	return resultVector;
}

void HeuristicAlgorithm::UpdateEP(std::vector<ExtremePoint>& extremePoints, const PlacementSelection& placement, int containerIndex)
{
	ResultWritter::GetInstanse()->SaveNewValue(placement);


	UpdateExistedEP(extremePoints, placement, containerIndex);
	CreateNewEP(extremePoints, placement, containerIndex);

	DeleteEP(extremePoints);

	UpdateContainer(extremePoints, containerIndex);
}

void HeuristicAlgorithm::UpdateExistedEP(std::vector<ExtremePoint>& emptySpaces, const PlacementSelection& placement, int containerIndex)
{
}

void HeuristicAlgorithm::CreateNewEP(std::vector<ExtremePoint>& emptySpaces, const PlacementSelection& placement, int containerIndex)
{
}

void HeuristicAlgorithm::DeleteEP(std::vector<ExtremePoint>& emptySpaces)
{
}

void HeuristicAlgorithm::UpdateEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex)
{
	ResultWritter::GetInstanse()->SaveNewValue(placement);



	UpdateExistedEMS(emptySpaces, placement, containerIndex);
	CreateNewEMS(emptySpaces, placement, containerIndex);

	DeleteEMS(emptySpaces);

	UpdateContainer(emptySpaces, containerIndex);
}

void HeuristicAlgorithm::DeleteEMS(std::vector<Container>& emptySpaces)
{
	auto noSpaceEnd = std::remove_if(emptySpaces.begin(), emptySpaces.end(), [](const Container& container) { return container.GetHeightZ() <= 0 || container.GetWidthY() <= 0 || container.GetLenghtX() <= 0; });
	emptySpaces.erase(noSpaceEnd, emptySpaces.end());
}

void HeuristicAlgorithm::UpdateExistedEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex)
{
	int updatedSizeX = 0;
	int updatedSizeY = 0;
	int updatedSizeZ = 0;
	int updatedCoordinationX = 0;
	int updatedCoordinationY = 0;
	int updatedCoordinationZ = 0;

	bool updatedSpace = false;

	for (auto& emptySpace : emptySpaces)
	{
		// Initialize values
		updatedSizeX = emptySpace.GetLenghtX();
		updatedSizeY = emptySpace.GetWidthY();
		updatedSizeZ = emptySpace.GetHeightZ();
		updatedCoordinationX = emptySpace.GetX();
		updatedCoordinationY = emptySpace.GetY();
		updatedCoordinationZ = emptySpace.GetZ();

		if (emptySpace.GetX() < placement.size.lenght_x + placement.coordination.x)
		{
			updatedSizeX = emptySpace.GetLenghtX() - (placement.size.lenght_x + placement.coordination.x);
			updatedCoordinationX = placement.size.lenght_x + placement.coordination.x;
			updatedSpace = true;
		}
		if (emptySpace.GetY() < placement.size.width_y + placement.coordination.y)
		{
			updatedSizeY = emptySpace.GetWidthY() - (placement.size.width_y + placement.coordination.y);
			updatedCoordinationY = placement.size.width_y + placement.coordination.y;
			updatedSpace = true;
		}
		if (emptySpace.GetZ() < placement.size.height_z + placement.coordination.z)
		{
			updatedSizeY = emptySpace.GetHeightZ() - (placement.size.height_z + placement.coordination.z);
			updatedCoordinationZ = placement.size.height_z + placement.coordination.z;
			updatedSpace = true;
		}

		if (updatedSpace)
		{
			emptySpace.UpdateMembers
			(updatedSizeX, updatedSizeY, updatedSizeZ,
				updatedCoordinationX, updatedCoordinationY, updatedCoordinationZ);
		}
	}
	//Delete spaces that have one coordination <=0
}

void HeuristicAlgorithm::UpdateContainer(const std::vector<Container>& emptySpaces, int containerIndex)
{
	PoolManager::GetInstance()->UpdateContainerEMS(emptySpaces, containerIndex);
}

void HeuristicAlgorithm::UpdateContainer(const std::vector<ExtremePoint>& extremePoint, int containerIndex)
{
	PoolManager::GetInstance()->UpdateContainerEP(extremePoint, containerIndex);
}

void HeuristicAlgorithm::SortEMS(std::vector<Container>& emptySpaces)
{
	std::sort(emptySpaces.begin(), emptySpaces.end(), [](const Container& container1, const Container& container2) 
	{
		return container1.GetX() < container2.GetX();
	});
}

void HeuristicAlgorithm::UpdateBPS(int boxIndex)
{
	const auto iter = std::find_if(m_BPS.begin(), m_BPS.end(), [&boxIndex](int index) { return index == boxIndex; });

	if (iter != m_BPS.end())
	{
		m_BPS.erase(iter);
	}
}

void HeuristicAlgorithm::CreateNewEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex)
{
	const Container& openedContainer = GetContainer(containerIndex);

	int coordX = openedContainer.GetX();
	int coordY = openedContainer.GetY();
	int coordZ = openedContainer.GetZ();

	Container EMS_X
	(openedContainer.GetLenghtX() - (placement.coordination.x + placement.size.lenght_x), openedContainer.GetWidthY(), openedContainer.GetHeightZ(),
		placement.coordination.x + placement.size.lenght_x, coordY, coordZ
		);

	Container EMS_Y
	(openedContainer.GetLenghtX(), openedContainer.GetWidthY() - (placement.coordination.y + placement.size.width_y), openedContainer.GetHeightZ(),
		coordX, placement.coordination.y + placement.size.width_y, coordZ
		);

	Container EMS_Z
	(openedContainer.GetLenghtX(), openedContainer.GetWidthY(), openedContainer.GetHeightZ() - (placement.coordination.z + placement.size.height_z),
		coordX, coordY, placement.coordination.z + placement.size.height_z );

	emptySpaces.push_back(EMS_X);
	emptySpaces.push_back(EMS_Y);
	emptySpaces.push_back(EMS_Z);
}


