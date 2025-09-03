#pragma once

#include <vector>

#define PERMUTATION_TABLE_SIZE 256
#define FREQUENCY 0.01

class Noise
{
	public:
		Noise(unsigned long seed);

		double				getNoise(double x, double z);
	private:
		std::vector<int>	_permutationTable;
};
