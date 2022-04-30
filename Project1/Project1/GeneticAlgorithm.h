#pragma once
#include <list>
#include <Individual.h>

class PoolManager;

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	void Start();

private:
	void Evaluation();
	void Selection();
	void CrossoverAndMutation();

	// list of Individuals
	std::list<Individual> m_Individuals;

};

