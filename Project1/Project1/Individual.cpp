#include "Individual.h"
#include <Constants.h>

#include <Pool.h>

Individual::Individual(const Chromosome& choromo)
    : m_Chromosome(choromo)
{
}

Individual Individual::Mate(const Individual& parent2) const
{
    const std::vector<int>& parentS2_1 = m_Chromosome.GetS2();
    const std::vector<int>& parentS2_2 = parent2.GetCLS();

    std::vector<int> child_S2;

    child_S2.resize(parentS2_1.size());

    for (int i = CROX_FROM; i <= CROX_TO; i++)
    {
        child_S2[i] = parentS2_1[i];
    }

    int indexChild = CROX_TO + 1;

    for (int i = 0; i < parentS2_2.size(); i++)
    {
        if (indexChild < child_S2.size() || indexChild < CROX_FROM)
        {
            const auto it = std::find(child_S2.begin(), child_S2.end(), parentS2_2[i]);
            if (it == child_S2.end())
            {
                child_S2[indexChild] = parentS2_2[i];
                indexChild++;
            }
        }
        else
        {
            indexChild = 0;
            const auto it = std::find(child_S2.begin(), child_S2.end(), parentS2_2[i]);
            if (it == child_S2.end())
            {
                child_S2[indexChild] = parentS2_2[i];
                indexChild++;
            }
        }
    }

    return Individual(Chromosome(m_Chromosome.GetS1(), child_S2));
}
