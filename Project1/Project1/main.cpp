#include <HeuristicAlgorithm.h>
#include <GeneticAlgorithm.h>
#include <Pool.h>

#include <time.h>

#include <ResultWritter.h>

int main()
{
    srand(time(nullptr));

    ResultWritter::GetInstanse()->SaveDataTime();

    // read json file
    PoolManager* pool = PoolManager::GetInstance(); 
    pool->Initialize();
    
    //HeuristicAlgorithm hAlgorithm; 
    //hAlgorithm.Initialize();
    // preinitialize genetic algorithm
    GeneticAlgorithm gAlgorithm;

    gAlgorithm.Start();


    return 0;
}