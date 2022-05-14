#pragma once
#include <nlohmann/json.hpp>
#include <ExtremePoint.h>

class Container
{
public:
	Container() = default;
	Container(const Container& value);
	Container(nlohmann::json containerInfo);
	Container(int sizeX, int sizeY, int sizeZ, int x, int y, int z);
	~Container() = default;

	int GetLenghtX() const { return m_LenghtX; }
	int GetWidthY() const { return m_WidthY; }
	int GetHeightZ() const { return m_HeightZ; }

	int GetX() const { return m_X; }
	int GetY() const { return m_Y; }
	int GetZ() const { return m_Z; }

	void UpdateMembers(int sizeX, int sizeY, int sizeZ, int x, int y, int z);

	int GetIndex() const { return m_Index; }

	int GetVolume() const { return m_LenghtX * m_WidthY * m_HeightZ; }

	const std::vector<Container>& GetEMS() const {	return m_EmptySpaces; }
	void SetEMS(const std::vector<Container>& newEMS);

	const std::vector<ExtremePoint>& GetEP() const { return m_ExtremePoints; }
	void SetEP(const std::vector<ExtremePoint>& newEP);
private:
	void Initialize();

	std::vector<Container> m_EmptySpaces;

	std::vector<ExtremePoint> m_ExtremePoints;

	int m_LenghtX = 0;
	int m_WidthY = 0;
	int m_HeightZ = 0;

	int m_X = 0;
	int m_Y = 0;
	int m_Z = 0;

	int m_Index = 0;


};
