#pragma once

#include <vector>

#define PERMUTATION_TABLE_SIZE 256
#define FREQUENCY 0.005
#define AMPLITUDE 1
#define NOISIFY(x) static_cast<uint8_t>(std::round(255 * (((x + 1.0) / 2.0))))

class Noise
{
	public:
		Noise(unsigned long seed, double frequency, double amplitude);

		double				getNoise(double x, double y, int octaveCount);
	private:
		std::vector<int>	_permutationTable;
		double				_frequency;
		double				_amplitude;

		double				_computeNoise(double x, double z);
};
