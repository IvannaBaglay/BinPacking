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

	int Start();



private:
	std::list<Box> CreateAllBoxOrientation(int boxIndex);
	bool CanBoxBePlacedInSpace(const Box& box, const Container& space, PlacementSelection& placement, int containerIndex);
	const Container& GetContainer(int containerIndex);
	const std::vector<Container>& GetEMSContainer(int containerIndex);
	const Container& GetFirstContainerInList();

	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector);
	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, int containerIndex);
	std::vector<int> DifferentceVectors(const std::vector<int>& firstVector, int containerIndex);

	void UpdateEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void UpdateExistedEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void CreateNewEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void UpdateContainer(const std::vector<Container>& emptySpaces, int containerIndex);
	void SortEMS(std::vector<Container>& emptySpaces);
	void DeleteEMS(std::vector<Container>& emptySpaces);

	void UpdateBPS(int boxIndex);

	PlacementSelection MakePlacementsIndicted(std::vector<PlacementSelection>& placementsSelection);

	void CopyEmptySpacesFromContainer(std::vector<Container>& emptySpaces, int containerIndex);

	int CalculateFitness(const std::vector<Container>& emptySpaces); // return accumulation of empty space volumes

	std::vector<int> m_BPS;
	std::vector<int> m_CLS;
};