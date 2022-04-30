#pragma once
#include<vector>

class Chromosome
{
public:
	Chromosome();
	Chromosome(const Chromosome& rhv) = default;

	void PreInitialize();

private:

	std::vector<int> m_S1;
	std::vector<int> m_S2;

};