#pragma once
#include <list>
#include <Individual.h>

class PoolManager;

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	void PreInitialization();

	void Start();

private:
	void Initialization();
	void Evaluation();
	void Selection();
	void CrossoverAndMutation();

	// list of Individuals
	std::list<Individual> m_Individuals;

};

