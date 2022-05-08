#pragma once
#include <list>
#include <vector>
#include <Box.h>
#include <Container.h>

class PoolManager
{
public:
	PoolManager(PoolManager& other) = delete;
	void operator=(const PoolManager&) = delete;

	static PoolManager* GetInstance();


	bool Initialize();
	int GetBoxNumber() const { return m_Boxes.size(); }
	int GetContainerNumber() const { return m_Containers.size(); }

	const std::vector<int>& GetIndexesSortDecreaseBoxes() { return m_DescreaseBoxIndexes; };
	std::vector<int> GetIndexesContainers();
	void InitializeDecreaseBoxIndexes();

	const Box& GetBoxByIndex(int boxIndex);
	const Container& GetContainerByIndex(int containerIndex);

	void UpdateContainerEMS(const std::vector<Container>& emptySpaces, int containerIndex);
	const std::vector<Container>& GetContainerEMS(int containerIndex);
private:
	static PoolManager* m_PoolManager;

	PoolManager() = default;
	~PoolManager() = default;


	bool ParseBoxes();
	bool ParseContainers();

	std::vector<int> m_DescreaseBoxIndexes;
	std::vector<Box> m_Boxes;
	std::vector<Container> m_Containers;
};