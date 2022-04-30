#pragma once
#include <Chromosome.h>
#include <memory>
#include <vector>

class PoolManager;

class Individual
{
public:
	Individual() = default;
	~Individual() = default;

	void PreInitialization();

	Individual Mate(Individual parent2);

	const std::vector<int>& GetBPS() const { return m_Chromosome.GetS1(); }
	const std::vector<int>& GetCLS() const { return m_Chromosome.GetS2(); }

private:
	//float CalculateFitness(); ??

	Chromosome m_Chromosome;
	float m_Fitness;

};