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

            individual.SetFitness(rand() % 100 + 1);


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
   // separate on k group
    // 
    const int countInOneGroup = POPULATION / K_GROUP;

    std::vector<Individual> parents; 

    //for (int i = 0; i < POPULATION; i = i + countInOneGroup)
    //{
    //    std::vector<Individual> subVec = slice(m_Individuals, i, countInOneGroup);

    //    parents.push_back(FindBetterIndividual(subVec));
    //    // Find Better
    //}

    
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

Individual GeneticAlgorithm::FindBetterIndividual(const std::vector<Individual>& individuals)
{
    auto maxIndivid = std::max_element(individuals.begin(), individuals.end(), [](const Individual& ind1, const Individual& ind2) { return ind1.GetFitness() > ind2.GetFitness(); });

    if (maxIndivid == individuals.end())
    {
        assert("Error iterator");
    }
    return *maxIndivid;

}
inline void GeneticAlgorithm::CrossoverAndMutation()
{
}
