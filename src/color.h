#pragma once

#include "vec3.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	// Divide the color by the number of samples and gamma-correct for gamma = 2.0
	double scale = 1.0 / samples_per_pixel;
	r = std::sqrt(r * scale);
	g = std::sqrt(g * scale);
	b = std::sqrt(b * scale);

	// Write the translated [0, 255] value of each color component.
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}
