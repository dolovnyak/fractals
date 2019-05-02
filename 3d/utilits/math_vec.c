#include "math_vec.h"
#include <math.h>

t_vector3d	mv_minus(const t_vector3d A, const t_vector3d B)
{
	t_vector3d	C;

	C.x = A.x - B.x;
	C.y = A.y - B.y;
	C.z = A.z - B.z;
	return (C);
}

t_vector3d	mv_plus(const t_vector3d A, const t_vector3d B)
{
	t_vector3d	C;

	C.x = A.x + B.x;
	C.y = A.y + B.y;
	C.z = A.z + B.z;
	return (C);
}

t_vector3d	mv_mult_num(const t_vector3d A, float num)
{
	t_vector3d	C;

	C.x = A.x * num;
	C.y = A.y * num;
	C.z = A.z * num;
	return (C);
}

t_vector3d	mv_dev_num(const t_vector3d A, float num)
{
	t_vector3d	C;

	C.x = A.x / num;
	C.y = A.y / num;
	C.z = A.z / num;
	return (C);
}

float		mv_scalar_mult(const t_vector3d A, const t_vector3d B)
{
	float	scalar_mult;

	scalar_mult = A.x * B.x + A.y * B.y + A.z * B.z;
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

float		mv_length(const t_vector3d A)
{
	float	length;

	length = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
	return (length);
}
