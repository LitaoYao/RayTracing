#pragma once

#include <cmath>
#include <limits>
#include <cstdlib>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

inline double random_double()
{
	// [0,1) random
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	// [min, max) random
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
	if (x < min) { return min; }
	if (x > max) { return max; }
	return x;
}

// Common Headers

#include "ray.h"
#include "vec3.h"
