#pragma once
#include <Chromosome.h>
#include <memory>

class PoolManager;

class Individual
{
public:
	Individual() = default;
	~Individual() = default;

	void PreInitialization();

	Individual Mate(Individual parent2);


private:
	float CalculateFitness();

	Chromosome m_Chromosome;
	float m_Fitness;

};