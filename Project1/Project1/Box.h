#pragma once
#include <nlohmann/json.hpp>

class Box
{
public:
	Box() = default;
	Box(int x, int y, int z, int index);

	Box(const nlohmann::json& boxInfo);
	~Box() = default;

	int GetSizeX() const { return m_SizeX; }
	int GetSizeY() const { return m_SizeY; }
	int GetSizeZ() const { return m_SizeZ; }

	int GetIndex() const { return m_Index; }

private:
	void Initialize();
	int m_SizeX;
	int m_SizeY;
	int m_SizeZ;

	int m_Index;

};