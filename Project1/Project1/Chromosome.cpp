#include "Chromosome.h"


#include <Pool.h>

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


Chromosome::Chromosome()
{
    m_S1.reserve(PoolManager::GetInstance()->GetBoxNumber());
    m_S2.reserve(PoolManager::GetInstance()->GetContainerNumber());

    PreInitialize();
}

Chromosome::Chromosome(const std::vector<int> s1, std::vector<int> s2)
    : m_S1(std::move(s1)), m_S2(std::move(s2))
{
}

void Chromosome::PreInitialize()
{
    // S1 initialize box in decrease order
    
    const std::vector<int>& decreasedBoxesIndex = PoolManager::GetInstance()->GetIndexesSortDecreaseBoxes();
    std::copy(decreasedBoxesIndex.begin(), decreasedBoxesIndex.end(), std::back_inserter(m_S1));

    const std::vector<int>& containersIndex = PoolManager::GetInstance()->GetIndexesContainers();
    std::copy(containersIndex.begin(), containersIndex.end(), std::back_inserter(m_S2));

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_S2.begin(), m_S2.end(), std::default_random_engine(seed));
}
