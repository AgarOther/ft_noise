#include "Noise.hpp"
#include "stb_image_write.h"
#include <cmath>
#include <cstdint>

int main(void)
{
	Noise noise(42);

	std::vector<uint8_t> data;

	for (int x = 0; x < 256; ++x)
		for (int y = 0; y < 256; ++y)
			data.push_back(std::round(255 * (((noise.getNoise(x * FREQUENCY, y * FREQUENCY) + 1.0) / 2.0))));
	
	stbi_write_png("noise.png", 256, 256, 1, data.data(), 256);
}
