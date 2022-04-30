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
	HeuristicAlgorithm(const std::vector<int> bps, const std::vector<int> cls);
	~HeuristicAlgorithm() = default;

	void Start();
	void MakePlacementsIndicted();
	void UpdateEMS(std::vector<Container>& emptySpaces);

private:
	std::list<Box> CreateAllBoxOrientation(int boxIndex);
	bool CanBoxBePlacedInSpace(const Box& box, const Container& space, PlacementSelection& placement);
	const Container& GetContainer(int containerIndex);

	std::vector<int> m_BPS;
	std::vector<int> m_CLS;
};