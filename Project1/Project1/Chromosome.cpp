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

void Chromosome::PreInitialize()
{
    // S1 initialize box in decrease order
    
    const std::vector<int>& decreasedBoxesIndex = PoolManager::GetInstance()->GetIndexesSortDecreaseBoxes();

    std::copy(decreasedBoxesIndex.begin(), decreasedBoxesIndex.end(), std::back_inserter(m_S1));

    // S2 initialize containers in random order
    int containerNumber = PoolManager::GetInstance()->GetContainerNumber();
    for (int i = 0; i < containerNumber; i++)
    {
        m_S2.push_back(i + 1);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_S2.begin(), m_S2.end(), std::default_random_engine(seed));
}
