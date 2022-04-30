#pragma once
#include <list>
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

	std::vector<int> GetIndexesSortDecreaseBoxes();

private:
	static PoolManager* m_PoolManager;

	PoolManager() = default;
	~PoolManager() = default;


	bool ParseBoxes();
	bool ParseContainers();

	std::list<Box> m_Boxes;
	std::list<Container> m_Containers;
};