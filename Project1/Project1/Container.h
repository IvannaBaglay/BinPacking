#pragma once
#include <nlohmann/json.hpp>

class Container
{
public:
	Container() = default;
	Container(nlohmann::json containerInfo);
	~Container() = default;

private:
	void Initialize();
	int m_SizeX;
	int m_SizeY;
	int m_SizeZ;

	int index;
};
