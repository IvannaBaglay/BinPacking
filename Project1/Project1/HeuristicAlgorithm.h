#pragma once
#include <list>
#include <vector>

class Box;
class Container;
struct PlacementSelection;

class HeuristicAlgorithm
{
public:
	HeuristicAlgorithm() = default;
	HeuristicAlgorithm(const std::vector<int>& bps, const std::vector<int>& cls);
	~HeuristicAlgorithm() = default;

	void Start();



private:
	std::list<Box> CreateAllBoxOrientation(int boxIndex);
	bool CanBoxBePlacedInSpace(const Box& box, const Container& space, PlacementSelection& placement);
	const Container& GetContainer(int containerIndex);
	const std::vector<Container>& GetEMSContainer(int containerIndex);
	const Container& GetFirstContainerInList();

	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector);
	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, int containerIndex);
	std::vector<int> DifferentceVectors(const std::vector<int>& firstVector, int containerIndex);

	void UpdateEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void UpdateExistedEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement);
	void CreateNewEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void UpdateContainer(const std::vector<Container>& emptySpaces, int containerIndex);
	void SortEMS(std::vector<Container>& emptySpaces);

	void UpdateBPS(int boxIndex);

	PlacementSelection MakePlacementsIndicted(std::vector<PlacementSelection>& placementsSelection, const Container& emptySpace);

	void CopyEmptySpacesFromContainer(std::vector<Container>& emptySpaces, int containerIndex);

	std::vector<int> m_BPS;
	std::vector<int> m_CLS;
};