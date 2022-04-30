#include "Box.h"

Box::Box(int x, int y, int z, int index)
    : m_SizeX(x), m_SizeY(y), m_SizeZ(z), m_Index(index)
{
}

Box::Box(const nlohmann::json& boxInfo)
{
    m_Index = boxInfo["index"];

    m_SizeX = boxInfo["size"]["x"];
    m_SizeY = boxInfo["size"]["y"];
    m_SizeZ = boxInfo["size"]["z"];
}
