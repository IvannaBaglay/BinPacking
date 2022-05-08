#include <GeneticAlgorithm.h>
#include <Constants.h>
#include <Pool.h>
#include <HeuristicAlgorithm.h>
#include <ResultWritter.h>

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
    for (int generationIndex = 0; generationIndex < GENERATIONS; generationIndex++)
    {
        int individualIndex = 0;
        for (auto& individual : m_Individuals)
        {
            HeuristicAlgorithm hAlgorith(individual.GetBPS(), individual.GetCLS());

            int fitness = hAlgorith.Start();

            individual.SetFitness(fitness);


            ResultWritter::GetInstanse()->WriteResult(generationIndex, individualIndex, fitness, fitness != INVALID_FITNESS?true:false);

            individualIndex++;
        }
        Selection();
        Evaluation();
        CrossoverAndMutation();

        ResultWritter::GetInstanse()->CleanResult();
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
