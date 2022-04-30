#include <fstream>
#include <nlohmann/json.hpp>
#include <Pool.h>

namespace
{
    std::string CONTAINERS_FILE = "containers.json";
    std::string BOXES_FILE = "boxes.json";
}

using json = nlohmann::json;


PoolManager* PoolManager::m_PoolManager = nullptr;

PoolManager* PoolManager::GetInstance()
{
    if (m_PoolManager == nullptr)
    {
        m_PoolManager = new PoolManager();
    }

    return m_PoolManager;
}

bool PoolManager::Initialize()
{
    bool result = false;

    result = ParseBoxes();
    result = ParseContainers();

    return result;
}

std::vector<int> PoolManager::GetIndexesSortDecreaseBoxes()
{


    return std::vector<int>();
}

bool PoolManager::ParseBoxes()
{
    bool result = false;
    std::ifstream file(BOXES_FILE);
    json boxesInfo;
    file >> boxesInfo;

    result = !boxesInfo.empty();

    for (auto box : boxesInfo["boxes"])
    {
        m_Boxes.push_back(Box(box));
    }

    return result;
}

bool PoolManager::ParseContainers()
{
    bool result = false;
    std::ifstream file(CONTAINERS_FILE);
    json containersInfo;
    file >> containersInfo;

    result = !containersInfo.empty();

    for (auto container : containersInfo["containers"])
    {
        m_Containers.push_back(Container(container));
    }

    return result;
}
