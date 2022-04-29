#pragma once
#include <Chromosome.h>
#include <memory>

class Individual
{
public:
	Individual();
	~Individual();

	Individual Mate(Individual parent2);


private:
	float CalculateFitness();

	std::unique_ptr<Chromosome> m_Chromosome;
	float m_Fitness;

};