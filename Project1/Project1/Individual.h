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

	Individual Mate(Individual parent2);

	const std::vector<int>& GetBPS() const { return m_Chromosome.GetS1(); }
	const std::vector<int>& GetCLS() const { return m_Chromosome.GetS2(); }

	int GetFitness() const { return m_Fitness; }
	void SetFitness(int fitness) { m_Fitness = fitness; }

private:

	Chromosome m_Chromosome;
	float m_Fitness;
	int m_Index;
};