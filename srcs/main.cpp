#include "Noise.hpp"
#include "stb_image_write.h"
#include <cmath>
#include <cstdint>

int main(void)
{
	Noise noise(42, FREQUENCY, AMPLITUDE);

	std::vector<uint8_t> data;

	for (int x = 0; x < 1024; ++x)
		for (int y = 0; y < 1024; ++y)
			data.push_back(NOISIFY(noise.getNoise(x, y, 5)));
	
	stbi_write_png("noise.png", 1024, 1024, 1, data.data(), 1024);
}
