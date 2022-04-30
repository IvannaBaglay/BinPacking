#include "Box.h"

Box::Box(const nlohmann::json& boxInfo)
{
    index = boxInfo["index"];

    m_SizeX = boxInfo["size"]["x"];
    m_SizeY = boxInfo["size"]["y"];
    m_SizeZ = boxInfo["size"]["z"];
}
