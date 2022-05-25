#include <HeuristicAlgorithm.h>
#include <GeneticAlgorithm.h>
#include <Pool.h>

#include <time.h>
#include <iostream>

#include <ResultWritter.h>

int main()
{
    srand(time(nullptr));

    ResultWritter::GetInstanse()->SaveDataTime();

    ResultWritter::GetInstanse()->SaveStartTime();

    // read json file
    PoolManager* pool = PoolManager::GetInstance(); 
    pool->Initialize();
    
    //HeuristicAlgorithm hAlgorithm; 
    //hAlgorithm.Initialize();
    // preinitialize genetic algorithm
    GeneticAlgorithm gAlgorithm;

    gAlgorithm.Start();

    ResultWritter::GetInstanse()->SaveEndTime();

    std::cout << ResultWritter::GetInstanse()->GeneralTime(); 

    return 0;
}