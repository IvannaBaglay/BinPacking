#include "Container.h"

Container::Container(nlohmann::json containerInfo)
{
    m_Index = containerInfo["index"];

    m_LenghtX = containerInfo["size"]["x"];
    m_WidthY = containerInfo["size"]["y"];
    m_HeightZ = containerInfo["size"]["z"];
}

Container::Container(int sizeX, int sizeY, int sizeZ, int x, int y, int z)
    : m_LenghtX(sizeX), m_WidthY(sizeY), m_HeightZ(sizeZ), m_X(x), m_Y(y), m_Z(z)
{
}

void Container::SetEMS(const std::vector<Container>& newEMS)
{
    m_EmptySpaces.clear();
    std::copy(newEMS.cbegin(), newEMS.cend(), std::back_inserter(m_EmptySpaces));
}
