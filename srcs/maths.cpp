#include <cmath>
#include <utility>

double fade(double t)
{
	return (6 * std::pow(t, 5) - 15 * std::pow(t, 4) + 10 * std::pow(t, 3));
}

double lerp(double a, double b, double t)
{
	return a + t * (b - a);
}

double dot(std::pair<double, double> v1, std::pair<double, double> v2)
{
	return v1.first * v2.first + v1.second * v2.second;
}

std::pair<double, double> normalize(std::pair<double, double> v)
{
	std::pair<double, double> normalized;
	double length = sqrt(v.first * v.first + v.second * v.second);

	normalized.first = v.first / length;
	normalized.second = v.second / length;
	return normalized;
}
