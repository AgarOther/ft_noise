#pragma once

#define GRID_WIDTH	256
#define GRID_HEIGHT	256
#define BLOCK_SIZE	32
#define AMPLITUDE	1
#define FREQUENCY	1.1

#include <cstddef>
#include <utility>

class Noise
{
	public:
		Noise(unsigned long long seed, double amplitude = 1, double frequency = 1);
	private:
		double			_amplitude;
		double			_frequency;
};

void						generatePNG(size_t seed);
double						lerp(double a, double b, double t);
double						dot(std::pair<double, double> v1, std::pair<double, double> v2);
double						fade(double t);
std::pair<double, double>	normalize(std::pair<double, double> v);
