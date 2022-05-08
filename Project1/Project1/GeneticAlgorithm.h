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
	void Selection(std::vector<Individual>& parents);
	void CrossoverAndMutation(const std::vector<Individual>& parents);

	// list of Individuals
	std::vector<Individual> m_Individuals;

};

