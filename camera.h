#pragma once

#include "rtweekend.h"

class camera
{
public:
	camera(
		point3 lookfrom,
		point3 lookat,
		vec3 vup,
		double vfov, // vertical field-of-view in degree
		double aspect_ratio,
		double aperture,
		double focus_dist
	)
	{
		double theta = degrees_to_radians(vfov);
		double h = tan(theta * 0.5);
		double viewport_height = 2.0 * h;
		double viewport_width = aspect_ratio * viewport_height;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal * 0.5 - vertical * 0.5 - focus_dist * w;

		lens_radius = aperture * 0.5;
	}

	ray get_ray(double s, double t) const
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		point3 new_origin = origin + offset;
		return ray(new_origin, lower_left_corner + s * horizontal + t * vertical - new_origin);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};
