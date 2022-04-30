#pragma once
#include<vector>

class Chromosome
{
public:
	Chromosome();

	// Add constructor with selection

	Chromosome(const Chromosome& rhv) = default;

	const std::vector<int>& GetS1() const { return m_S1; }
	const std::vector<int>& GetS2() const { return m_S2; }

	void PreInitialize();

private:

	std::vector<int> m_S1;
	std::vector<int> m_S2;

};