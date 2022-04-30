#pragma once
#include <nlohmann/json.hpp>

class Box
{
public:
	Box() = default;
	Box(const nlohmann::json& boxInfo);
	~Box() = default;

private:
	void Initialize();
	int m_SizeX;
	int m_SizeY;
	int m_SizeZ;

	int index;

};