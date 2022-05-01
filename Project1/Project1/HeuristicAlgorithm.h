#pragma once
#include <list>
#include <vector>
#include <queue>

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
	const Container& GetFirstContainerInList();

	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector);
	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, const Container& container);

	std::vector<int> DifferentceVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector);
	std::vector<int> DifferentceVectors(const std::vector<int>& firstVector, const Container& container);

	void UpdateEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void UpdateExistedEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement);
	void CreateNewEMS(std::vector<Container>& emptySpaces, const PlacementSelection& placement, int containerIndex);
	void UpdateContainer(std::vector<Container>& emptySpaces, int containerIndex);

	PlacementSelection MakePlacementsIndicted(std::queue<PlacementSelection>& placementsSelection);

	std::vector<int> m_BPS;
	std::vector<int> m_CLS;
};