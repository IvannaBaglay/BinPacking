#include <GeneticAlgorithm.h>
#include <Constants.h>
#include <Pool.h>
#include <HeuristicAlgorithm.h>
#include <ResultWritter.h>

#include <iterator>

template<typename T>
std::vector<T> slice(std::vector<T>& v, int m, int n)
{
    std::vector<T> vec;
    std::copy(v.begin() + m, v.begin() + n + 1, std::back_inserter(vec));
    return vec;
}


GeneticAlgorithm::GeneticAlgorithm()
{
    /*std::list<Individual> tempList (POPULATION, Individual());
    std::copy(tempList.begin(), tempList.end(), std::back_inserter(m_Individuals));*/

    for (int i = 0; i < POPULATION; i++)
    {
        m_Individuals.push_back(Individual());
    }

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

            int fitness = 0;//hAlgorith.Start();

            individual.SetFitness(rand() % 100 + 1);


            ResultWritter::GetInstanse()->WriteResult(generationIndex, individualIndex, fitness, fitness != INVALID_FITNESS?true:false);

            individualIndex++;
        }

        std::vector<Individual> parents;
        Selection(parents);
        CrossoverAndMutation(parents);

        ResultWritter::GetInstanse()->CleanResult();
    }
}

inline void GeneticAlgorithm::Evaluation()
{

}

inline void GeneticAlgorithm::Selection(std::vector<Individual>& parents)
{
    const int countInOneGroup = POPULATION / K_GROUP;


    for (int i = 0; i < K_TOURNAMENT; i++)
    {
        Individual& individualBetter = m_Individuals[i];
        for (int j = 0; j < POPULATION/ K_TOURNAMENT; j += K_TOURNAMENT)
        {
            const Individual& individual1 = m_Individuals[j];
            for (int m = 1; m < K_TOURNAMENT; m++)
            {
                const Individual& individual2 = m_Individuals[m];
                if (individual1.GetFitness() < individual2.GetFitness())
                {
                    individualBetter = individual2;
                }
            }
            parents.push_back(individualBetter);
        }
    }


    //Tested averange value
    //int value1 = std::accumulate(m_Individuals.begin(), m_Individuals.end(), 0, [](int i, const Individual& ind) { return ind.GetFitness() + i; }) / m_Individuals.size();
    //int value2 = std::accumulate(parents.begin(), parents.end(), 0, [](int i, const Individual& ind) { return ind.GetFitness() + i; }) / parents.size();

}

inline void GeneticAlgorithm::CrossoverAndMutation(const std::vector<Individual>& parents)
{
    std::vector<Individual> children;
    for (const auto& individ1 : parents)
    {
        for (const auto& individ2 : parents)
        {
            children.push_back(individ1.Mate(individ2));
        }
    }
    m_Individuals.clear();

    std::copy(children.begin(), children.end(), std::back_inserter(m_Individuals));
    
}
