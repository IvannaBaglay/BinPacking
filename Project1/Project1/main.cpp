#include <HeuristicAlgorithm.h>
#include <GeneticAlgorithm.h>
#include <Pool.h>

#include <time.h>

int main()
{
    srand(time(nullptr));

    // read json file
    PoolManager* pool = PoolManager::GetInstance(); 
    pool->Initialize();
    
    //HeuristicAlgorithm hAlgorithm; 
    //hAlgorithm.Initialize();
    // preinitialize genetic algorithm
    GeneticAlgorithm gAlgorithm;




    return 0;
}