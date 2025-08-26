#include "Noise.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include "Noise.hpp"
#include <cstdint>
#include <vector>
#include <ctime>

static std::pair<double, double> getGradientVector()
{
	switch (rand() % 8)
	{
		case 0: return {1.0, 0.0};
		case 1: return {-1.0, 0.0};
		case 2: return {0.0, 1.0};
		case 3: return {0.0, -1.0};
		case 4: return {1.0, 1.0};
		case 5: return {-1.0, -1.0};
		case 6: return {1.0, -1.0};
		default: return {-1.0, 1.0};
	};
}

Noise::Noise(unsigned long long seed, double amplitude, double frequency):
	_amplitude(amplitude), _frequency(frequency)
{
	const int blockX = GRID_WIDTH / BLOCK_SIZE;
	const int blockY = GRID_HEIGHT / BLOCK_SIZE;
	std::pair<double, double> gradientVectors [blockX][blockY];
	std::vector<uint8_t> data;

	srand(seed);
	for (int x = 0; x < blockX; ++x)
	{
		for (int y = 0; y < blockY; ++y)
			gradientVectors[x][y] = normalize(getGradientVector());
	}
	for (size_t x = 0; x < GRID_WIDTH; ++x)
	{
		for (size_t y = 0; y < GRID_HEIGHT; ++y)
		{
			int gridX = x / BLOCK_SIZE;
			int gridY = y / BLOCK_SIZE;

			double dx = (x - gridX * BLOCK_SIZE) / static_cast<double>(BLOCK_SIZE);
			double dy = (y - gridY * BLOCK_SIZE) / static_cast<double>(BLOCK_SIZE);

			int x1 = std::min(gridX + 1, blockX - 1);
			int y1 = std::min(gridY + 1, blockY - 1);

			std::pair<double, double> topLeft = gradientVectors[gridX][gridY];
			double topLeftDot = dot(topLeft, {dx, dy});
			std::pair<double, double> topRight = gradientVectors[x1][gridY];
			double topRightDot = dot(topRight, {dx - 1, dy});
			std::pair<double, double> bottomLeft = gradientVectors[gridX][y1];
			double bottomLeftDot = dot(bottomLeft, {dx, dy - 1});
			std::pair<double, double> bottomRight = gradientVectors[x1][y1];
			double bottomRightDot = dot(bottomRight, {dx - 1, dy - 1});

			double tX = fade((x % BLOCK_SIZE) / static_cast<double>(BLOCK_SIZE));
			double tY = fade((y % BLOCK_SIZE) / static_cast<double>(BLOCK_SIZE));

			double topValue = lerp(topLeftDot, topRightDot, tX);
			double bottomValue = lerp(bottomLeftDot, bottomRightDot, tX);
			data.push_back(((lerp(topValue, bottomValue, tY) * _amplitude + 1) / 2 * 255));
		}
	}
	stbi_write_png("noise.png", GRID_WIDTH, GRID_HEIGHT, 1, data.data(), GRID_WIDTH);
}
