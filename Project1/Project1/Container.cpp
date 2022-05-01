#include "Container.h"

//Container::Container(const Container& value)
//{
//    m_LenghtX = value.GetLenghtX();
//    m_WidthY = value.GetWidthY();
//    m_HeightZ = value.GetHeightZ();
//    m_X= value.GetX();
//    m_Y= value.GetY();
//    m_Z= value.GetZ();
//
//    m_Index = value.GetIndex();
//
//    const std::vector<Container> spaces(value.GetEMS());
//
//    m_EmptySpaces.clear();
//    std::copy(spaces.cbegin(), spaces.cend(), std::back_inserter(m_EmptySpaces));
//}

Container::Container(nlohmann::json containerInfo)
{
    m_Index = containerInfo["index"];

    m_LenghtX = containerInfo["size"]["x"];
    m_WidthY = containerInfo["size"]["y"];
    m_HeightZ = containerInfo["size"]["z"];

    //m_EmptySpaces.push_back(*this);
}

Container::Container(int sizeX, int sizeY, int sizeZ, int x, int y, int z)
    : m_LenghtX(sizeX), m_WidthY(sizeY), m_HeightZ(sizeZ), m_X(x), m_Y(y), m_Z(z)
{
    m_EmptySpaces.push_back(*this);
}

void Container::SetEMS(const std::vector<Container>& newEMS)
{
    m_EmptySpaces.clear();
    std::copy(newEMS.cbegin(), newEMS.cend(), std::back_inserter(m_EmptySpaces));
}
