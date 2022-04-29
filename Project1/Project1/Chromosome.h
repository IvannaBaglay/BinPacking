#pragma once
#include<vector>

class Chromosome
{
public:
	Chromosome();
	~Chromosome();

private:
	std::vector<int> m_S1;
	std::vector<int> m_S2;

};