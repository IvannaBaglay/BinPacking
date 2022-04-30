#include <GeneticAlgorithm.h>
#include <Constants.h>
#include <Pool.h>
#include <iterator>

GeneticAlgorithm::GeneticAlgorithm()
{
    std::list<Individual> tempList (POPULATION, Individual());

    std::copy(tempList.begin(), tempList.end(), std::back_inserter(m_Individuals));
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

inline void GeneticAlgorithm::PreInitialization()
{

}

inline void GeneticAlgorithm::Start()
{
}

inline void GeneticAlgorithm::Initialization()
{
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
