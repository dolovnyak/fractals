#include "math_vec.h"

t_vector3d	mv_minus(const t_vector3d a, const t_vector3d b)
{
	t_vector3d	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vector3d	mv_plus(const t_vector3d a, const t_vector3d b)
{
	t_vector3d	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector3d	mv_mult_num(const t_vector3d a, float num)
{
	t_vector3d	c;

	c.x = a.x * num;
	c.y = a.y * num;
	c.z = a.z * num;
	return (c);
}

t_vector3d	mv_dev_num(const t_vector3d a, float num)
{
	t_vector3d	c;

	c.x = a.x / num;
	c.y = a.y / num;
	c.z = a.z / num;
	return (c);
}

float		mv_scalar_mult(const t_vector3d a, const t_vector3d b)
{
	float	scalar_mult;

	scalar_mult = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scalar_mult);
}

t_vector3d  mv_get_vector3d(float x, float y, float z)
{
	t_vector3d  vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float		mv_length(const t_vector3d a)
{
	float	length;

	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}
