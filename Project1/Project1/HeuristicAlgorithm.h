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
	void MakePlacementsIndicted();
	void UpdateEMS(std::vector<Container>& emptySpaces);

private:
	std::list<Box> CreateAllBoxOrientation(int boxIndex);
	bool CanBoxBePlacedInSpace(const Box& box, const Container& space, PlacementSelection& placement);
	const Container& GetContainer(int containerIndex);
	const Container& GetFirstContainerInList();

	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector);
	std::vector<int> ConcatenateVectors(const std::vector<int>& firstVector, const Container& container);

	std::vector<int> DifferentceVectors(const std::vector<int>& firstVector, const std::vector<int>& secondVector);
	std::vector<int> DifferentceVectors(const std::vector<int>& firstVector, const Container& container);

	std::vector<int> m_BPS;
	std::vector<int> m_CLS;
};