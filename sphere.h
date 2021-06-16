#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
	sphere() {}
	sphere(point3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {}
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
	std::shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	// t ^ 2 * r.direction() * r.direction() + 2 * t * r.direction() * (r.origin - center) + (r.origin - center) * (r.origin - cent) - radius * radius = 0
	vec3 oc = r.origin() - center;
	double a = r.direction().length_squared();
	double half_b = dot(r.direction(), oc);
	double c = oc.length_squared() - radius * radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return false;
	}
	else
	{
		double sqrtd = std::sqrt(discriminant);
		double t = (-half_b - sqrtd) / a; // choose the smallest t, which is closest of the hit point 
		if (t < t_min || t_max < t)
		{
			t = (-half_b + sqrtd) / a; // choose the biggest t, which is farthest of the hit point 
			if (t < t_min || t_max < t)
			{
				return false;
			}
		}
		rec.t = t;
		rec.p = r.at(t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat_ptr = mat_ptr;
		return true;
	}
}