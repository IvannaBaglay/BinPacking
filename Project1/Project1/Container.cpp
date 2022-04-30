#include "Container.h"

Container::Container(nlohmann::json containerInfo)
{
    m_Index = containerInfo["index"];

    m_LenghtX = containerInfo["size"]["x"];
    m_WidthY = containerInfo["size"]["y"];
    m_HeightZ = containerInfo["size"]["z"];
}
