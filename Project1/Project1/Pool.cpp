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

    InitializeDecreaseBoxIndexes();

    return result;
}

void PoolManager::InitializeDecreaseBoxIndexes()
{
    std::sort(m_Boxes.begin(), m_Boxes.end(), [](Box& box1, Box& box2)
    {
        return box1.GetSizeX() > box2.GetSizeX();
    });

    for (int i = 0; i < m_Boxes.size(); i++)
    {
        m_DescreaseBoxIndexes.push_back(m_Boxes.at(i).GetIndex());
    }
}

const Box& PoolManager::GetBoxByIndex(int boxIndex)
{
    const auto founded = std::find_if(m_Boxes.cbegin(), m_Boxes.cend(),
        [&boxIndex](const Box& box)
    {
        return box.GetIndex() == boxIndex;
    }
    );

    if (founded == m_Boxes.end())
    {
        assert("Don't found box");
    }

    return *founded;
}

const Container& PoolManager::GetContainerByIndex(int containerIndex)
{
    const auto founded = std::find_if(m_Containers.cbegin(), m_Containers.cend(),
        [&containerIndex](const Container& container)
    {
        return container.GetIndex() == containerIndex;
    }
    );

    if (founded == m_Containers.cend())
    {
        assert("Don't found box");
    }

    return *founded;
}

void PoolManager::UpdateContainerEMS(std::vector<Container>& emptySpaces, int containerIndex)
{
    auto founded = std::find_if(m_Containers.begin(), m_Containers.end(),
        [&containerIndex](const Container& container)
    {
        return container.GetIndex() == containerIndex;
    }
    );

    if (founded == m_Containers.end())
    {
        assert("Don't found box");
    }

    founded->SetEMS(emptySpaces);
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
