#pragma once
#include <nlohmann/json.hpp>

class Container
{
public:
	Container() = default;
	Container(nlohmann::json containerInfo);
	~Container() = default;

	int GetLenghtX() const { return m_LenghtX; }
	int GetWidthY() const { return m_WidthY; }
	int GetHeightZ() const { return m_HeightZ; }

	int GetX() const { return m_X; }
	int GetY() const { return m_Y; }
	int GetZ() const { return m_Z; }

	int GetIndex() const { return m_Index; }
private:
	void Initialize();

	int m_LenghtX = 0;
	int m_WidthY = 0;
	int m_HeightZ = 0;

	int m_X = 0;
	int m_Y = 0;
	int m_Z = 0;

	int m_Index = 0;
};
