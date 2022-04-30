#include <GeneticAlgorithm.h>
#include <Constants.h>
#include <Pool.h>
#include <HeuristicAlgorithm.h>

#include <iterator>

GeneticAlgorithm::GeneticAlgorithm()
{
    std::list<Individual> tempList (POPULATION, Individual());

    std::copy(tempList.begin(), tempList.end(), std::back_inserter(m_Individuals));
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::Start()
{
    for (const auto& individual : m_Individuals)
    {
        HeuristicAlgorithm hAlgorith(individual.GetBPS(), individual.GetCLS());

        hAlgorith.Start();
    }
}

inline void GeneticAlgorithm::Evaluation()
{

}

inline void GeneticAlgorithm::Selection()
{

}

inline void GeneticAlgorithm::CrossoverAndMutation()
{
}
