#include "Container.h"

Container::Container(nlohmann::json containerInfo)
{
    index = containerInfo["index"];

    m_SizeX = containerInfo["size"]["x"];
    m_SizeY = containerInfo["size"]["y"];
    m_SizeZ = containerInfo["size"]["z"];
}
